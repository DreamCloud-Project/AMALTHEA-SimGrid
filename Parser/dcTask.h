/*
* Vertex.h
*
*  Created on: Oct 6, 2014
*      Author: Charles
*/

#ifndef VERTEX_H_
#define VERTEX_H_
#include <iostream>
#include <vector>
#include "AmRunnable.h"
#include "dcActEvent.h"
#include "dcCore.h"
#include "dcTag.h"


namespace DCApplication{
	using namespace std;
	class dcTaskEdge;
	class dcRunnable;
	class dcTask
	{
		public:
			dcTask(string NameIn);
			string GetName();
			void SetName(string NameIn);
			void SetEdges(dcTaskEdge* EdgesIn);
			dcTaskEdge* GetEdges();
			void SetNext(dcTask *NextIn);
			dcTask* GetNext();
			void SetRunnables(dcRunnable* RunnableIn);
			dcRunnable* GetRunnables();
			void SetVisited(bool visitedIn);
			bool GetVisited();
			void SetTag(dcTag* tagIn);
			dcTag* GetTag();

			int GetPriority();
			void SetPriority(int PriorityIn);
			bool GetPriorityValid();
			int GetMultipleTaskActivationLimit();
			void SetMultipleTaskActivationLimit(int MultipleTaskActivationLimitIn);
			bool GetMultipleTaskActivationLimitValid();
			string GetPreemption();
			void SetPreemption(string PreemptionIn);
			void SetDeadline(pair<int,string> DeadlineIn);
			int GetDeadlineValue();
			string GetDeadlineUnit();
			int GetSize();
			void SetSize(int SizeIn);
			void SetActEvent(dcActEvent* ActEventIn);
			dcActEvent* GetActEvent();
			vector<string> GetResources();
			void SetResources(vector<string> ResourceIn);
			string GetID();
			void SetID(string IDIn);
			
			int GetTaskID();
			void SetTaskID(int TaskIDIn);

		private:
			string Name;
			dcTaskEdge *Edges;
			dcTask *Next;
			dcRunnable *Runnables;
			bool Visited;
			dcTag* tag;

			int Priority;
			bool PriorityValid;
			int MultipleTaskActivationLimit;
			bool MultipleTaskActivationLimitValid;
			string Preemption;
			pair<int,string> Deadline;
			dcActEvent *ActEvent_;
			int Size;
			vector<string> Resources;
			string ID;
			int TaskID;
	};
}
#endif /* VERTEX_H_ */