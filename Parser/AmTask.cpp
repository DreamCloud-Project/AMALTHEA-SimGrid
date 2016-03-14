#include "AmTask.h"

namespace DCApplication
{
	AmTask::AmTask(string NameIn): Name(NameIn), Priority(10), PriorityValid(false), Size(0), tag(NULL) /*activation(NULL), next(NULL)*/ {
	}

	AmTask::~AmTask() {}


	void AmTask::SetName(string NameIn) {
		Name=NameIn;
	}

	string AmTask::GetName() {
		return Name;
	}

	int AmTask::GetPriority() {
		return Priority;
	}

	void AmTask::SetPriority(int PriorityIn) {
		Priority=PriorityIn;
	}

	bool AmTask::GetPriorityValid() {
		return PriorityValid;
	}

	int AmTask::GetMultipleTaskActivationLimit() {
		return MultipleTaskActivationLimit;
	}

	void AmTask::SetMultipleTaskActivationLimit(int MultipleTaskActivationLimitIn) {
		MultipleTaskActivationLimit=MultipleTaskActivationLimitIn;
	}

	bool AmTask::GetMultipleTaskActivationLimitValid() {
		return MultipleTaskActivationLimitValid;
	}

	void AmTask::SetPreemption(string PreemptionIn) {
		Preemption=PreemptionIn;
	}

	string AmTask::GetPreemption() {
		return Preemption;
	}

	void AmTask::SetDeadline(pair<int,string> DeadlineIn) {
		Deadline=DeadlineIn;
	}

	int AmTask::GetDeadlineValue() {
		return Deadline.first;
	}

	string AmTask::GetDeadlineUnit(){
		return Deadline.second;
	}

	void AmTask::SetSize(int SizeIn) {
		Size=SizeIn;
	}

	int AmTask::GetSize() {
		return Size;
	}

	void AmTask::AddRunnable(AmRunnable* RunnableIn) {
		Runnables.push_back(RunnableIn);
	}

	void AmTask::Print() {
		cout << "Name: " << Name;
		cout << " period - ";
		ActEvent_->Print();
		cout << endl;
		vector<AmRunnable*>::iterator it;
		int i;
		for(i=0,it=Runnables.begin();it!=Runnables.end();++it,i++) {
			cout << "Runnable no:" << i << endl;
			(*it)->Print();
		}
	}


	void AmTask::SetActEvent(dcActEvent* StimulusIn) {
		ActEvent_=StimulusIn;
	}

	dcActEvent*  AmTask::GetActEvent() {
		return ActEvent_;
	}

	void AmTask::SetResource(string ResourceIn){
		Resource.push_back(ResourceIn);
	}
	vector<string> AmTask::GetResource(){
		return Resource;
	}

	AmRunnable*  AmTask::GetRunnable(int Index) {
		return Runnables[Index];
	}

	int AmTask::GetNoOfRunnables() {
		return Runnables.size();
	}

	//get runnables
	vector<AmRunnable*> AmTask::GetRunnables(){
		return Runnables;
	}

	void AmTask::SetTag(dcTag* tagIn){
		tag= tagIn;
	}

	dcTag* AmTask::GetTag(){
		return tag;
	}

	string AmTask::GetID(){
		return ID;
	}
	void AmTask::SetID(string IDIn){
		ID = IDIn;
	}
	
	int AmTask::GetTaskID(){
		return TaskID;
	}
	void AmTask::SetTaskID(int TaskIDIn){
		TaskID = TaskIDIn;
	}

}