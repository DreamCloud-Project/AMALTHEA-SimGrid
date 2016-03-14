#ifndef DC_RUNNABLE_H
#define DC_RUNNABLE_H

#include <iostream>
#include <string>
#include <vector>
#include "dcInstruction.h"
#include "dcTag.h"
#include "dcRunnableExecutionTime.h"


namespace DCApplication
{
   using namespace std;

	class AmRunnable {
		string Name;
		dcTag* Tags;
		string ID;
		vector<dcInstruction*> Instructions;
		int Size;
		vector<string> ReleasedTasks;
		bool OrderedTaskReleased;
		dcRunnableExecutionTime* ExecutionTime;
		int Priority;
		string Preemption;
		string RunSource;
		vector<string> RunDestination;

		pair<int,string> Deadline;
		
		int RunnableID;

	public:
		AmRunnable(string NameIn);
		~AmRunnable();
		void SetName(string NameIn);
		string GetName();
		void SetTags(dcTag* TagsIn);
		dcTag* GetTags();
		int GetSize();
		void SetSize(int SizeIn);
		void AddInstruction(dcInstruction *InstructionIn);
		void Print();
		void SetID(string IDIn);
		string GetID();
		double GetWCETInTick();
		bool CheckIfIncludesExecutionCyclesDeviationInstruction();
		string GetTheFirstDeviationType();
		double GetTheFirstDeviationRemainPromille();
		double GetTheFirstDeviationStandardDeviation();
		double GetTheFirstDeviationLowerBound();
		double GetTheFirstDeviationUpperBound();
		double GetTheFirstDeviationMean();
		int GetPriority();
		void SetPriority(int PriorityIn);
		string GetPreemption();
		void SetPreemption(string PreemptionIn);
		string GetRunSource();
		void SetRunSource(string RunSourceIn);
		vector<string> GetRunnableDestination();


		vector<dcInstruction*> GetAllInstructions();
		vector<string> GetReleasedTasks();
		void AddReleasedTask(string releasedTaskIn);

		void SetOrderedTaskReleased(bool OrderedTaskReleasedIn);
		bool GetOrderedTaskReleased();

		void SetRunnableExecutionTime(dcRunnableExecutionTime* MyExecutionTimeIn);
		dcRunnableExecutionTime* GetRunnableExecutionTime();

		vector<string>GetRunDestination();
		void AddRunDestination(string RunDestinationIn);

		void SetDeadline(pair<int,string> DeadlineIn);
		int GetDeadlineValue();
		string GetDeadlineUnit();
		
		int GetRunnableID();
		void SetRunnableID(int RunnableIDIn);
	}; 


}

#endif //