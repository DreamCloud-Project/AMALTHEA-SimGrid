#ifndef RUNNABLE_H_
#define RUNNABLE_H_

#include <iostream>
#include <string>
#include <vector>
#include "dcInstruction.h"
#include "dcTag.h"
#include "dcRunnableExecutionTime.h"

namespace DCApplication{
	using namespace std;

	class dcRunnableEdge;

	class dcRunnable
	{

		public:

			dcRunnable(string NameIn);
			string GetName();
			void SetName(string NameIn);
			void SetID(string IDIn);
			string GetID();
			void SetEdges(dcRunnableEdge* RunEdgeIn);
			dcRunnableEdge* GetEdges();
			void SetNext(dcRunnable *NextIn);
			dcRunnable* GetNext();
			string GetRunSource();
			void SetRunSource(string RunSourceIn);
			vector<string>GetRunDestination();
			void AddRunDestination(string RunDestinationIn);
			vector<string> GetRunnableDestination();
			void SetRunnableDestination(vector<string> RunDestinationIn);

			void SetTags(dcTag* TagsIn);
			dcTag* GetTags();
			int GetSize();
			void SetSize(int SizeIn);
			void SetInstructions(vector<dcInstruction*> InstructionIn);
			int GetPriority();
			void SetPriority(int PriorityIn);
			string GetPreemption();
			void SetPreemption(string PreemptionIn);
			vector<dcInstruction*> GetAllInstructions();
			vector<string> GetReleasedTasks();
			void SetReleasedTasks(vector<string> releasedTaskIn);

			void SetOrderedTaskReleased(bool OrderedTaskReleasedIn);
			bool GetOrderedTaskReleased();
			void SetRunnableExecutionTime(dcRunnableExecutionTime* MyExecutionTimeIn);
			dcRunnableExecutionTime* GetRunnableExecutionTime();

			void SetDeadline(pair<int,string> DeadlineIn);
			int GetDeadlineValue();
			string GetDeadlineUnit();

			dcRunnable* GetTail();
			void SetTail(dcRunnable* TailIn);
			
			void SetStartTime(int x);
			int GetStartTime();
			void SetCompletitionTime(int x);
			int GetCompletitionTime();
		

			void SetWaveID(int x);
			int GetWaveID();
			
			int GetRunnableID();
			void SetRunnableID(int RunnableIDIn);

			vector<dcRunnable*> GetActivators();
			void SetActivators(dcRunnable* x);
			

		private:
			string ID;
			string Name;
			dcRunnableEdge* RunEdge;
			dcRunnable *Next;
			dcRunnable *Tail;
			string RunSource;
			vector<string> RunDestination;

			dcTag* Tags;
			vector<dcInstruction*> Instructions;
			int Size;
			vector<string> ReleasedTasks;
			bool OrderedTaskReleased;
			dcRunnableExecutionTime* ExecutionTime;
			int Priority;
			string Preemption;

			pair<int,string> Deadline;
			int execution_time_start;
			int execution_time_completition;
			int waveID;
			
			int RunnableID;
			vector<dcRunnable*> activators;

	};

}
#endif /* RUNNABLE_H_ */
