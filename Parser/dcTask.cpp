#include "dcTask.h"


namespace DCApplication
{
	using namespace std;

	dcTask::dcTask(string n):Name(n), Edges(NULL), Next(NULL), Runnables(NULL), Visited(false) {}

	void dcTask::SetName(string NameIn){
		Name = NameIn;
	}

	string dcTask::GetName(){
		return Name;
	}

	void dcTask::SetEdges(dcTaskEdge* EdgeIn){
		Edges = EdgeIn;
	}

	dcTaskEdge* dcTask::GetEdges(){
		return Edges;
	}

	void dcTask::SetNext(dcTask* NextIn){
		Next = NextIn;
	}

	dcTask* dcTask::GetNext(){
		return Next;
	}

	dcRunnable* dcTask::GetRunnables(){
		return Runnables;
	}

	void dcTask::SetRunnables(dcRunnable* RunnableIn){
		Runnables = RunnableIn;
	}

	void dcTask::SetVisited(bool VisitedIn){
		Visited = VisitedIn;
	}
	bool dcTask::GetVisited(){
		return Visited;
	}

	void dcTask::SetTag(dcTag* tagIn){
		tag= tagIn;
	}

	dcTag* dcTask::GetTag(){
		return tag;
	}

	int dcTask::GetPriority() {
		return Priority;
	}

	void dcTask::SetPriority(int PriorityIn) {
		Priority=PriorityIn;
	}

	bool dcTask::GetPriorityValid() {
		return PriorityValid;
	}

	int dcTask::GetMultipleTaskActivationLimit() {
		return MultipleTaskActivationLimit;
	}

	void dcTask::SetMultipleTaskActivationLimit(int MultipledcTaskActivationLimitIn) {
		MultipleTaskActivationLimit=MultipledcTaskActivationLimitIn;
	}

	bool dcTask::GetMultipleTaskActivationLimitValid() {
		return MultipleTaskActivationLimitValid;
	}

	void dcTask::SetPreemption(string PreemptionIn) {
		Preemption=PreemptionIn;
	}

	string dcTask::GetPreemption() {
		return Preemption;
	}

	void dcTask::SetDeadline(pair<int,string> DeadlineIn) {
		Deadline=DeadlineIn;
	}

	int dcTask::GetDeadlineValue() {
		return Deadline.first;
	}

	string dcTask::GetDeadlineUnit(){
		return Deadline.second;
	}

	void dcTask::SetSize(int SizeIn) {
		Size=SizeIn;
	}

	int dcTask::GetSize() {
		return Size;
	}

	void dcTask::SetActEvent(dcActEvent* StimulusIn) {
		ActEvent_=StimulusIn;
	}

	dcActEvent*  dcTask::GetActEvent() {
		return ActEvent_;
	}

	void dcTask::SetResources(vector<string> ResourceIn){
		Resources = ResourceIn;
	}
	vector<string> dcTask::GetResources(){
		return Resources;
	}

	string dcTask::GetID(){
		return ID;
	}
	void dcTask::SetID(string IDIn){
		ID = IDIn;
	}

	int dcTask::GetTaskID(){
		return TaskID;
	}
	void dcTask::SetTaskID(int TaskIDIn){
		TaskID = TaskIDIn;
	}
}
