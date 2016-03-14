#include "dcRunnable.h"


namespace DCApplication
{
	using namespace std;

	dcRunnable::dcRunnable(string n):Name(n), RunEdge(NULL), Next(NULL), RunSource(""), RunDestination(NULL), Tail(0) {}

	void dcRunnable::SetName(string NameIn){
		Name = NameIn;
	}

	string dcRunnable::GetName(){
		return Name;
	}

	void dcRunnable::SetEdges(dcRunnableEdge* EdgesIn){
		RunEdge = EdgesIn;
	}

	void dcRunnable::SetID(string IDIn) {
		ID=IDIn;
	}

	string dcRunnable::GetID() {
		return ID;
	}

	dcRunnableEdge* dcRunnable::GetEdges(){
		return RunEdge;
	}

	void dcRunnable::SetNext(dcRunnable* NextIn){
		Next = NextIn;
	}

	dcRunnable* dcRunnable::GetNext(){
		return Next;
	}

	string dcRunnable::GetRunSource(){
		return RunSource;
	}

	void dcRunnable::SetRunSource(string RunSourceIn){
		RunSource = RunSourceIn;
	}

	vector<string> dcRunnable::GetRunDestination(){
		return RunDestination;
	}

	void dcRunnable::AddRunDestination(string RunDestinationIn){
		RunDestination.push_back(RunDestinationIn);
	}

	vector<string> dcRunnable::GetRunnableDestination(){
		return RunDestination;
	}

	void dcRunnable::SetRunnableDestination(vector<string> RunDestinationIn){
		RunDestination = RunDestinationIn;
	}

	void dcRunnable::SetTags(dcTag* TagsIn) {
		Tags=TagsIn;
	}

	dcTag* dcRunnable::GetTags() {
		return Tags;
	}

	void dcRunnable::SetInstructions(vector<dcInstruction*> InstructionsIn) {
		Instructions = InstructionsIn;
	}

	void dcRunnable::SetSize(int SizeIn) {
		Size=SizeIn;
	}

	int dcRunnable::GetSize() {
		return Size;
	}

	int dcRunnable::GetPriority() {
		return Priority;
	}

	void dcRunnable::SetPriority(int PriorityIn) {
		Priority=PriorityIn;
	}

	void dcRunnable::SetPreemption(string PreemptionIn) {
		Preemption=PreemptionIn;
	}

	string dcRunnable::GetPreemption() {
		return Preemption;
	}

	vector<dcInstruction*> dcRunnable::GetAllInstructions(){
		return Instructions;
	}

	vector<string> dcRunnable::GetReleasedTasks(){
		return ReleasedTasks;
	}

	void dcRunnable::SetReleasedTasks(vector<string> ReleasedTaskIn){
		ReleasedTasks = ReleasedTaskIn;
	}

	void dcRunnable::SetOrderedTaskReleased(bool OrderedTaskReleasedIn){
		OrderedTaskReleased = OrderedTaskReleasedIn;
	}

	bool dcRunnable::GetOrderedTaskReleased(){
		return OrderedTaskReleased;
	}

	void dcRunnable::SetRunnableExecutionTime(dcRunnableExecutionTime* MyExecutionTimeIn){
		ExecutionTime = MyExecutionTimeIn;
	}

	dcRunnableExecutionTime* dcRunnable::GetRunnableExecutionTime(){
		return ExecutionTime;
	}

	void dcRunnable::SetDeadline(pair<int,string> DeadlineIn) {
		Deadline=DeadlineIn;
	}

	int dcRunnable::GetDeadlineValue() {
		return Deadline.first;
	}

	string dcRunnable::GetDeadlineUnit(){
		return Deadline.second;
	}

	void dcRunnable::SetTail(dcRunnable* TailIn){
		Tail = TailIn;
	}

	dcRunnable* dcRunnable::GetTail(){
		return Tail;
	}
	
	void dcRunnable::SetRunnableID(int IDIn) {
		RunnableID=IDIn;
	}

	int dcRunnable::GetRunnableID() {
		return RunnableID;
	}
	
	void dcRunnable::SetStartTime(int x){ 
		execution_time_start = x; 
	}
	
	int dcRunnable::GetStartTime(){ 
		return execution_time_start; 
	}
	
	void dcRunnable::SetCompletitionTime(int x){ 
		execution_time_completition = x; 
	}
	
	int dcRunnable::GetCompletitionTime(){ 
		return execution_time_completition; 
	}
	
	void dcRunnable::SetWaveID(int x) { 
		waveID = x; 
	}

	int dcRunnable::GetWaveID() {
		return waveID;
	}

	void dcRunnable::SetActivators(dcRunnable* x)
	{
		activators.push_back(x);
		//cout << x->GetName() << " NOZ SIZE IS " << activators.size() << "_____________________________________";
	}


	vector<dcRunnable*> dcRunnable::GetActivators()
	{
		//cout << "GET SIZE: " << activators.size() << endl;
		return activators;
	}



	

}
