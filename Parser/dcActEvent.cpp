#include "dcActEvent.h"

namespace DCApplication
{
	dcActEvent::dcActEvent(string NameIn): Name(NameIn) /*next(NULL), connectsTo(NULL)*/ {
	}

	void dcActEvent::SetName(string NameIn) {
		Name=NameIn;
	}

	string dcActEvent::GetName() {
		return Name;
	}

	void dcActEvent::SetID(string IDIn) {
		ID=IDIn;
	}

	string dcActEvent::GetID() {
		return ID;
	}

	void dcActEvent::AddSource(AmTask* TaskIn){
		Sources.push_back(TaskIn);
	}

	void dcActEvent::AddDestination(AmTask* TaskIn){
		Destinations.push_back(TaskIn);
	}

	int dcActEvent::GetNoOfSources(){
		return Sources.size();
	}

	int dcActEvent::GetNoOfDestinations(){
		return Destinations.size();
	}

	AmTask* dcActEvent::GetSource(int Index){
		return Sources.at(Index);
	}

	AmTask* dcActEvent::GetDestination(int Index){
		return Destinations.at(Index);
	}

	bool dcActEvent::IsTaskInSources(AmTask *TaskIn) {
		vector<AmTask*>::iterator p;
		if((p = find(Sources.begin(),Sources.end(),TaskIn))!=Sources.end()) {
			return true;
		}
		return false;
	}

	bool dcActEvent::IsTaskInDestinations(AmTask *TaskIn) {
		vector<AmTask*>::iterator p;
		if((p = find(Destinations.begin(),Destinations.end(),TaskIn))!=Destinations.end()) {
			return true;
		}
		return false;
	}

	vector<AmTask*> dcActEvent::GetAllSource(){
		return Sources;
	}

	vector<AmTask*> dcActEvent::GetAllDestination(){
		return Destinations;
	}

	void dcActEvent::Print() {
		cout << Name ;
	}

	void dcActEvent::SetType(string TypeIn){
		Type = TypeIn;
	}

	string dcActEvent::GetType(){
		return Type;
	}

}