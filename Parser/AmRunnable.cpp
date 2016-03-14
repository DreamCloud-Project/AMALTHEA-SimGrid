#include "AmRunnable.h"
#include "dcExecutionCyclesDeviationInstruction.h"
#include "dcExecutionCyclesConstantInstruction.h"

namespace DCApplication
{
	AmRunnable::AmRunnable(string NameIn): Name(NameIn), Size(0), Tags(NULL), Preemption(""), Priority(0) {
	}

	AmRunnable::~AmRunnable() {
		vector<dcInstruction*>::iterator itInstructions;
		for(itInstructions=Instructions.begin();itInstructions!=Instructions.end();++itInstructions) {
			delete *itInstructions;
		}
	}


	void AmRunnable::SetName(string NameIn) {
		Name=NameIn;
	}

	string AmRunnable::GetName() {
		return Name;
	}

	void AmRunnable::SetTags(dcTag* TagsIn) {
		Tags=TagsIn;
	}

	dcTag* AmRunnable::GetTags() {
		return Tags;
	}

	void AmRunnable::AddInstruction(dcInstruction *InstructionIn) {
		Instructions.push_back(InstructionIn);
	}

	void AmRunnable::SetSize(int SizeIn) {
		Size=SizeIn;
	}

	int AmRunnable::GetSize() {
		return Size;
	}

	void AmRunnable::SetID(string IDIn) {
		ID=IDIn;
	}

	string AmRunnable::GetID() {
		return ID;
	}

	int AmRunnable::GetPriority() {
		return Priority;
	}

	void AmRunnable::SetPriority(int PriorityIn) {
		Priority=PriorityIn;
	}

	void AmRunnable::SetPreemption(string PreemptionIn) {
		Preemption=PreemptionIn;
	}

	string AmRunnable::GetPreemption() {
		return Preemption;
	}

	void AmRunnable::Print() { 
		vector<dcInstruction*>::iterator it;
		int i;
		cout << "Name: " << Name << endl;
		for(i=0,it=Instructions.begin();it!=Instructions.end();++it,i++) {
			cout << "	Instruction no. " << i << ": ";
			(*it)->Print();
			cout << endl;
		}

	}

	bool AmRunnable::CheckIfIncludesExecutionCyclesDeviationInstruction() {
		bool result=false;
		vector<dcInstruction*>::iterator it;
		for(it=Instructions.begin();it!=Instructions.end();++it) {
			if(dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it)!=NULL) {
				result=true;
				break;
			}
		}
		return result;
	}

	double AmRunnable::GetWCETInTick() {
		vector<dcInstruction*>::iterator it;
		double nWCET=0.0;
		for(it=Instructions.begin();it!=Instructions.end();++it) {
			if((dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))!=NULL) {
				nWCET+=(dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))->GetUpperBound();
			}
			else if((dynamic_cast<dcExecutionCyclesConstantInstruction*>(*it))!=NULL) {
				nWCET+=(dynamic_cast<dcExecutionCyclesConstantInstruction*>(*it))->GetValue();
			}
		}
		return nWCET;
	}

	string AmRunnable::GetTheFirstDeviationType() {
		vector<dcInstruction*>::iterator it;
		for(it=Instructions.begin();it!=Instructions.end();++it) {
			if((dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))!=NULL) {
				return (dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))->GetType();
			}
		}
		return "";
	}

	double AmRunnable::GetTheFirstDeviationRemainPromille() {
		vector<dcInstruction*>::iterator it;
		for(it=Instructions.begin();it!=Instructions.end();++it) {
			if((dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))!=NULL) {
				if((dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))->GetRemainPromilleValid()) {
					return (dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))->GetRemainPromille();
				}
				else {
					return 0.0;
				}
			}
		}
		return 0.0;
	}

	double AmRunnable::GetTheFirstDeviationLowerBound() {
		vector<dcInstruction*>::iterator it;
		for(it=Instructions.begin();it!=Instructions.end();++it) {
			if((dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))!=NULL) {
				if((dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))->GetLowerBoundValid()) {
					return (dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))->GetLowerBound();
				}
				else {
					return 0;
				}
			}
		}
		return 0;
	}

	double AmRunnable::GetTheFirstDeviationUpperBound() {
		vector<dcInstruction*>::iterator it;
		for(it=Instructions.begin();it!=Instructions.end();++it) {
			if((dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))!=NULL) {
				if((dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))->GetUpperBoundValid()) {
					return (dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))->GetUpperBound();
				}
				else {
					return 0;
				}
			}
		}
		return 0;
	}

	double AmRunnable::GetTheFirstDeviationMean() {
		vector<dcInstruction*>::iterator it;
		for(it=Instructions.begin();it!=Instructions.end();++it) {
			if((dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))!=NULL) {
				if((dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))->GetMeanValid()) {
					return (dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))->GetMean();
				}
				else {
					return 0;
				}
			}
		}
		return 0;
	}

	double AmRunnable::GetTheFirstDeviationStandardDeviation() {
		vector<dcInstruction*>::iterator it;
		for(it=Instructions.begin();it!=Instructions.end();++it) {
			if((dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))!=NULL) {
				if((dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))->GetSDValid()) {
					return (dynamic_cast<dcExecutionCyclesDeviationInstruction*>(*it))->GetSD();
				}
				else {
					return 0.0;
				}
			}
		}
		return 0.0;
	}

	vector<dcInstruction*> AmRunnable::GetAllInstructions(){
		return Instructions;
	}

	vector<string> AmRunnable::GetReleasedTasks(){
		return ReleasedTasks;
	}

	void AmRunnable::AddReleasedTask(string ReleasedTaskIn){
		ReleasedTasks.push_back(ReleasedTaskIn);
	}

	string AmRunnable::GetRunSource(){
		return RunSource;
	}

	void AmRunnable::SetRunSource(string RunSourceIn){
		RunSource = RunSourceIn;
	}

	vector<string> AmRunnable::GetRunDestination(){
		return RunDestination;
	}

	void AmRunnable::AddRunDestination(string RunDestinationIn){
		RunDestination.push_back(RunDestinationIn);
	}

	vector<string> AmRunnable::GetRunnableDestination(){
		return RunDestination;
	}

	void AmRunnable::SetOrderedTaskReleased(bool OrderedTaskReleasedIn){
		OrderedTaskReleased = OrderedTaskReleasedIn;
	}

	bool AmRunnable::GetOrderedTaskReleased(){
		return OrderedTaskReleased;
	}

	void AmRunnable::SetRunnableExecutionTime(dcRunnableExecutionTime* MyExecutionTimeIn){
		ExecutionTime = MyExecutionTimeIn;
	}

	dcRunnableExecutionTime* AmRunnable::GetRunnableExecutionTime(){
		return ExecutionTime;
	}

	void AmRunnable::SetDeadline(pair<int,string> DeadlineIn) {
		Deadline=DeadlineIn;
	}

	int AmRunnable::GetDeadlineValue() {
		return Deadline.first;
	}

	string AmRunnable::GetDeadlineUnit(){
		return Deadline.second;
	}
	
	void AmRunnable::SetRunnableID(int IDIn) {
		RunnableID=IDIn;
	}

	int AmRunnable::GetRunnableID() {
		return RunnableID;
	}


}