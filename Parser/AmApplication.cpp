#include <iostream>
#include <string>

#include "AmApplication.h"

namespace DCApplication{

	using namespace std;
	AmApplication* AmApplication::pInstance = 0;
	AmApplication* AmApplication::instance(){
		if(pInstance==0){
			pInstance=new AmApplication;
		}
		return pInstance;
	}

	AmApplication::AmApplication() : NoOfPreemptive (0), NoOfNonPreemptive(0) {}

	AmApplication::~AmApplication(){
		vector<dcLabel*>::iterator itLabels;
		for(itLabels=Labels.begin();itLabels!=Labels.end();++itLabels) {
			delete *itLabels;
		}

		vector<AmRunnable*>::iterator itRunnables;
		for(itRunnables=Runnables.begin();itRunnables!=Runnables.end();++itRunnables) {
			delete *itRunnables;
		}

		vector<dcActEvent*>::iterator itActEvent;
		for(itActEvent=ActEvents.begin();itActEvent!=ActEvents.end();++itActEvent) {
			delete *itActEvent;
		}

		vector<AmTask*>::iterator itTasks;
		for(itTasks=Tasks.begin();itTasks!=Tasks.end();++itTasks) {
			delete *itTasks;
		}

		vector<dcCore*>::iterator itCores;
		for(itCores=Cores.begin();itCores!=Cores.end();++itCores) {
			delete *itCores;
		}
		map<string,dcCoreType*>::iterator itCoreTypesMap;
		for(itCoreTypesMap=CoreTypesMap.begin();itCoreTypesMap!=CoreTypesMap.end();++itCoreTypesMap) {
			delete (*itCoreTypesMap).second;
		}

		map<string,dcQuartz*>::iterator itQuartzesMap;
		for(itQuartzesMap=QuartzsMap.begin();itQuartzesMap!=QuartzsMap.end();++itQuartzesMap) {
			delete (*itQuartzesMap).second;
		}
	}

	//labels
	void AmApplication::AddLabel(dcLabel* LabelIn){
		Labels.push_back(LabelIn);
	}

	void AmApplication::AddLabel(dcLabel* LabelIn, string IDIn){
		Labels.push_back(LabelIn);
		LabelsMap[IDIn]=LabelIn;
	}

	dcLabel* AmApplication::GetLabel(int Index) {
		return Labels.at(Index);
	}

	int AmApplication::GetNoOfLabels() {
		return Labels.size();
	}


	void AmApplication::PrintAllLabels() {
		vector<dcLabel*>::iterator it;
		size_t i;
		for(i=0,it=Labels.begin(); it!=Labels.end() ; ++it,i++) {
			cout << i << " Name: " << (*it)->GetName() << " Size: " << (*it)->GetSize() << endl;
		}
	}

	dcLabel* AmApplication::GetLabel(string IDIn) {
		return LabelsMap.at(IDIn);
	}

	vector<dcLabel*> AmApplication::GetAllLabels(){
		return Labels;
	}

	vector<dcLabel*> AmApplication::GetLabelsForRunnable(AmRunnable* dcRunnableIn){
		vector<dcLabel*> Labels;

		int instructionSize = dcRunnableIn->GetAllInstructions().size();
		int i = 0;
		for(i=0; i < instructionSize; i++){
			string instrName = dcRunnableIn->GetAllInstructions().at(i)->GetName();
			if(instrName == "sw:LabelAccess"){
				dcInstruction* inst = dcRunnableIn->GetAllInstructions().at(i);
				dcRemoteAccessInstruction *rinst = dynamic_cast<dcRemoteAccessInstruction*>(inst);
				if(rinst){
					Labels.push_back(rinst->GetLabel());
				}
			}
		}
		return Labels;
	}

	//Given a label return the runnable that has read access to the label
	AmRunnable* AmApplication::GetRunnableWithReadAcess(dcLabel* LabelIn){
		vector<AmTask*> tasks = GetAllTask();
		AmRunnable* MyRunnable = NULL;
		size_t t, r, i = 0;
		for(t = 0; t < tasks.size(); t++){
			size_t runnableSize = tasks.at(t)->GetRunnables().size();
			for(r = 0; r < runnableSize; r++){
				size_t instructionSize = tasks.at(t)->GetRunnables().at(r)->GetAllInstructions().size();
				for(i=0; i < instructionSize; i++){
					string instrName = tasks.at(t)->GetRunnables().at(r)->GetAllInstructions().at(i)->GetName();
					if(instrName == "sw:LabelAccess"){
						dcInstruction* inst = tasks.at(t)->GetRunnables().at(r)->GetAllInstructions().at(i);
						dcRemoteAccessInstruction *rinst = dynamic_cast<dcRemoteAccessInstruction*>(inst);
						if(rinst){
							dcLabel* MyLabel = rinst->GetLabel();
							if(MyLabel == LabelIn){
								bool type = rinst->GetWrite();
								if (type != 1){
									MyRunnable = tasks.at(t)->GetRunnables().at(r);

								}
							}
						}
					}
				}
			}
		}
		return MyRunnable;
	}

	//Given a label return the runnable that has write access to the label
	AmRunnable* AmApplication::GetRunnableWithWriteAccess(dcLabel* LabelIn){
		vector<AmTask*> tasks = GetAllTask();
		AmRunnable* MyRunnable = NULL;
		size_t t, r, i = 0;
		for(t = 0; t < tasks.size(); t++){
			size_t runnableSize = tasks.at(t)->GetRunnables().size();
			for(r = 0; r < runnableSize; r++){
				size_t instructionSize = tasks.at(t)->GetRunnables().at(r)->GetAllInstructions().size();
				for(i=0; i < instructionSize; i++){
					string instrName = tasks.at(t)->GetRunnables().at(r)->GetAllInstructions().at(i)->GetName();
					if(instrName == "sw:LabelAccess"){
						dcInstruction* inst = tasks.at(t)->GetRunnables().at(r)->GetAllInstructions().at(i);
						dcRemoteAccessInstruction *rinst = dynamic_cast<dcRemoteAccessInstruction*>(inst);
						if(rinst){
							dcLabel* MyLabel = rinst->GetLabel();
							if(MyLabel == LabelIn){
								bool type = rinst->GetWrite();
								if (type == 1){
									MyRunnable = tasks.at(t)->GetRunnables().at(r);

								}
							}
						}
					}
				}
			}
		}
		return MyRunnable;
	}
	//runnables

	void AmApplication::AddRunnable(AmRunnable* RunnableIn){
		Runnables.push_back(RunnableIn);
	}

	void AmApplication::AddRunnable(AmRunnable* RunnableIn,string IDIn){
		Runnables.push_back(RunnableIn);
		RunnablesMap[IDIn]=RunnableIn;
	}

	AmRunnable* AmApplication::GetRunnable(int Index) {
		return Runnables.at(Index);
	}

	AmRunnable* AmApplication::GetRunnable(string IDIn) {
		return RunnablesMap.at(IDIn);
	}

	int AmApplication::GetNoOfRunnables() {
		return Runnables.size();
	}

	//Get the tasks released at the end of a runnable execution.
	vector<AmTask*> AmApplication::GetRunnableReleasedTasks(AmRunnable* MyRunnable){
		vector<AmTask*> releasedTasks;
		vector<string> ids = MyRunnable->GetReleasedTasks();

		size_t i = 0;
		for(i = 0; i <ids.size(); i++){
			AmTask * t = GetTaskFromID(ids.at(i));
			releasedTasks.push_back(t);
		}
		
		return releasedTasks;
	}

	//Get destination runnable given source
	vector<AmRunnable*> AmApplication::GetDestinationRunnables(AmRunnable* dcRunnableIn){
		vector<AmRunnable*> MyRunnables;
		vector<string> strRunnables;
		strRunnables = dcRunnableIn->GetRunDestination();
		size_t i = 0;
		for(i = 0; i < strRunnables.size(); i++){
			MyRunnables.push_back(GetRunnable(strRunnables.at(i)));
		}
		return MyRunnables;
	}
	vector<AmRunnable*> AmApplication::GetAllRunnable(){
		return Runnables;
	}

	//ActEvent

	void AmApplication::AddActEvent(dcActEvent* ActEventIn){
		ActEvents.push_back(ActEventIn);
	}

	void AmApplication::AddActEvent(dcActEvent* ActEventIn,string IDIn){
		ActEvents.push_back(ActEventIn);
		ActEventMap[IDIn]=ActEventIn;
	}

	dcActEvent* AmApplication::GetActEvent(int Index) {
		return ActEvents.at(Index);
	}


	dcActEvent* AmApplication::GetActEvent(string IDIn) {
		return ActEventMap.at(IDIn);
	}

	int AmApplication::GetNoOfActEvent() {
		return ActEvents.size();
	}

	//method for spliting combined stimuli IDs
	vector<std::string> AmApplication::GetStimuliIDs(std::string strStimulus){
		vector<std::string> ids;
		string temp = " ";
		string strStimulusNew = temp+""+strStimulus;
		string search=" ";
		string newStim = "";
		for(std::string::size_type pos=0; pos<strStimulusNew.size(); pos+=search.size())
		{
			pos=strStimulusNew.find(search, pos);
			if(pos==std::string::npos){
				break;
			}else{
				newStim = strStimulusNew.substr(pos, 24);
				newStim.erase(remove(newStim.begin(), newStim.end(), ' '), newStim.end());
				ids.push_back(newStim);
			}
		}
		return ids;
	}

	vector<dcActEvent*> AmApplication::GetAllActEvent(){
		vector<dcActEvent*> act = ActEvents;
		return act;
	}

	//Task
	void AmApplication::AddTask(AmTask* TaskIn){
		Tasks.push_back(TaskIn);
	}

	AmTask* AmApplication::GetTask(int Index) {
		return Tasks.at(Index);
	}

	int AmApplication::GetNoOfTasks() {
		return Tasks.size();
	}

	AmTask* AmApplication::GetTaskFromID(string IDIn){
		AmTask* temp = NULL;
		size_t i = 0;
		for(i = 0; i < Tasks.size(); i++){
			if(Tasks.at(i)->GetID() == IDIn){
				temp = Tasks.at(i);
			}
		}
		return temp;
	}

	vector<AmTask*> AmApplication::GetAllTask(){
		vector<AmTask*> v = Tasks;
		return v;
	}
	//hardwares (cores, coretype, quartz)

	void AmApplication::AddCoreType(dcCoreType* CoreTypeIn, string IDIn) {
		CoreTypesMap[IDIn]=CoreTypeIn;
	}

	dcCoreType* AmApplication::GetCoreType(string IDIn) {
		return CoreTypesMap.at(IDIn);
	}

	void AmApplication::AddQuartz(dcQuartz* QuartzIn, string IDIn) {
		QuartzsMap[IDIn]=QuartzIn;
	}

	dcQuartz* AmApplication::GetQuartz(string IDIn) {
		return QuartzsMap.at(IDIn);
	}

	void AmApplication::AddCore(dcCore* CoreIn, string IDIn) {
		CoresMap[IDIn]=CoreIn;
		Cores.push_back(CoreIn);
	}

	dcCore* AmApplication::GetCore(string IDIn) {
		return CoresMap.at(IDIn);
	}

	dcCore* AmApplication::GetCore(int Index) {
		return Cores[Index];
	}

	int AmApplication::GetNoOfCores() {
		return Cores.size();
	}

	vector<dcCore*> AmApplication::GetCores(){
		return Cores;
	}

	//tags
	void AmApplication::AddTag(dcTag* TagIn) {
		tags.push_back(TagIn);
	}

	vector<dcTag*> AmApplication::GetTagVec(){
		return tags;
	}

	dcTag* AmApplication::GetTag(string IDIn){
		dcTag* temp = NULL;
		size_t i = 0;
		for(i = 0; i < tags.size(); i++){
			if(tags.at(i)->GetID() == IDIn){
				temp = tags.at(i);
			}
		}
		return temp;
	}

	//get destination tasks given source tasks. 
	vector<AmTask*> AmApplication::GetDestinationTask(AmTask* TaskIn){
		vector<AmTask*> TaskOut;
		for(size_t i = 0; i < ActEvents.size(); i++){
			dcActEvent* ActEvent = ActEvents.at(i);
			string Type = ActEvent->GetType();
			if(Type=="stimuli:InterProcess"){
				size_t idx = 0;
				for(idx = 0; idx < ActEvent->GetAllSource().size(); idx++){
					if(ActEvent->GetSource(idx) == TaskIn){
						TaskOut.push_back(ActEvent->GetDestination(idx));
					}
				}
			}

		}
		return TaskOut;
	}

	//
	void AmApplication::AddPeriodicEvent(dcActEvent* ActionEventIn){
		PeriodicEvents.push_back(ActionEventIn);
	}
	void AmApplication::AddSporadicEvent(dcActEvent* ActionEventIn){
		SporadicEvents.push_back(ActionEventIn);
	}
	void AmApplication::AddAperiodicEVent(dcActEvent* ActionEventIn){
		AperiodicEvent.push_back(ActionEventIn);
	}	
	void AmApplication::AddDeterministicIrregularEvent(dcActEvent* ActionEventIn){
		DeterministicIrregular.push_back(ActionEventIn);
	}
	void AmApplication::AddInterprocessEvent(dcActEvent* ActionEventIn){
		InterprocessEvent.push_back(ActionEventIn);
	}

	vector<dcActEvent*> AmApplication::GetPeriodicEvents(){
		return PeriodicEvents;
	}
	vector<dcActEvent*> AmApplication::GetSporadicEvents(){
		return SporadicEvents;
	}
	vector<dcActEvent*> AmApplication::GetAperiodicEvent(){
		return AperiodicEvent;
	}
	vector<dcActEvent*> AmApplication::GetDeterministicIrregular(){
		return DeterministicIrregular;
	}
	vector<dcActEvent*> AmApplication::GetInterprocessEvent(){
		return InterprocessEvent;
	}

	void AmApplication::SetNoOfPreemptive(int  PreemptiveIn){
		NoOfPreemptive = PreemptiveIn;
	}

	void AmApplication::SetNoOfNonPreemptive(int  PreemptiveIn){
		NoOfNonPreemptive = PreemptiveIn;
	}

	int AmApplication::GetNoOfPreemptive(){
		return NoOfPreemptive;
	}

	int AmApplication::GetNoOfNonPreemptive(){
		return NoOfNonPreemptive;
	}

	vector<int> AmApplication::GetDeadlines(){
		return Deadlines;
	}

	void AmApplication::AddDeadlines(int DeadlineIn){
		Deadlines.push_back(DeadlineIn);
	}

	vector<int> AmApplication::GetPriorities(){
		return Priorities;
	}

	void AmApplication::AddProirity(int PriorityIn){
		Priorities.push_back(PriorityIn);
	}

}