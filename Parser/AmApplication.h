#ifndef AmApplication_H
#define AmApplication_H

#include <iostream>
#include <vector>
#include <map>
#include "AmTask.h"
#include "dcActEvent.h"
#include "AmRunnable.h"
#include "dcLabel.h"
#include "dcQuartz.h"
#include "dcCore.h"
#include "dcCoreType.h"
#include "dcMicrocontroller.h"
#include "dcTag.h"
#include "dcRemoteAccessInstruction.h"
#include "dcInstruction.h"
#include "dcExecutionCyclesConstantInstruction.h"
#include "dcExecutionCyclesDeviationInstruction.h"
#include "dcDeterministicIrregularEvent.h"
#include "dcFixedRunnableExecTime.h"
#include "dcGroupInstruction.h"


namespace DCApplication{

	using namespace std;

	class AmApplication{

	public:

		static AmApplication* instance(); //singleton

		AmApplication();
		~AmApplication();
 

		//labels
		void AddLabel(dcLabel* LabelIn);
		void AddLabel(dcLabel* LabelIn, string IDIn);
		dcLabel* GetLabel(int Index);
		int GetNoOfLabels();
		void PrintAllLabels();
		dcLabel* GetLabel(string IDIn);
		AmRunnable* GetRunnableWithReadAcess(dcLabel* LabelIn);
		AmRunnable* GetRunnableWithWriteAccess(dcLabel* LabelIn);
		vector<dcLabel*> GetAllLabels();
		vector<dcLabel*> GetLabelsForRunnable(AmRunnable* dcRunnableIn);

		//runnables
		void AddRunnable(AmRunnable *RunnableIn);
		void AddRunnable(AmRunnable* RunnableIn,string IDIn);
		AmRunnable* GetRunnable(int Index);
		AmRunnable* GetRunnable(string IDIn);
		int GetNoOfRunnables();
		vector<AmTask*> GetRunnableReleasedTasks(AmRunnable* MyRunnable);
		vector<AmRunnable*> GetAllRunnable();
		vector<AmRunnable*> GetDestinationRunnables(AmRunnable* dcRunnableIn);
		



		//ActEvent
		void AddActEvent(dcActEvent *ActEventIn);
		void AddActEvent(dcActEvent* ActEventIn,string IDIn);
		dcActEvent* GetActEvent(int Index);
		dcActEvent* GetActEvent(string IDIn);
		int GetNoOfActEvent();
		vector<string> GetStimuliIDs(string strStimulus);
		vector<dcActEvent*> GetAllActEvent();

		//Task
		void AddTask(AmTask *TaskIn);
		AmTask* GetTask(int Index);
		int GetNoOfTasks();
		AmTask* GetTaskFromID(string IDIn);
		vector<AmTask*> GetAllTask();
		vector<AmTask*> GetDestinationTask(AmTask* TaskIn);

		//hardwares (cores, coretype, quartz)
		void AddCoreType(dcCoreType* CoreTypeIn, string IDIn);
		dcCoreType* GetCoreType(string IDIn);

		void AddQuartz(dcQuartz* QuartzIn, string IDIn);
		dcQuartz* GetQuartz(string IDIn);

		void AddCore(dcCore* CoreIn, string IDIn);
		dcCore* GetCore(string IDIn);
		dcCore* GetCore(int Index);
		int GetNoOfCores();
		vector<dcCore*> GetCores(); //get all cores

		//tag
		void AddTag(dcTag* tagIn);
		vector<dcTag*> GetTagVec();
		dcTag* GetTag(string Id);

		//util
		void AddPeriodicEvent(dcActEvent* ActionEventIn);
		void AddSporadicEvent(dcActEvent* ActionEventIn);
		void AddAperiodicEVent(dcActEvent* ActionEventIn);
		void AddDeterministicIrregularEvent(dcActEvent* ActionEventIn);
		void AddInterprocessEvent(dcActEvent* ActionEventIn);

		vector<dcActEvent*> GetPeriodicEvents();
		vector<dcActEvent*> GetSporadicEvents();
		vector<dcActEvent*> GetAperiodicEvent();
		vector<dcActEvent*> GetDeterministicIrregular();
		vector<dcActEvent*> GetInterprocessEvent();

		void SetNoOfPreemptive(int);

		void SetNoOfNonPreemptive(int);

		int GetNoOfPreemptive();

		int GetNoOfNonPreemptive();

		vector<int> GetDeadlines();

		void AddDeadlines(int);

		vector<int> GetPriorities();

		void AddProirity(int);

	private:

		//basic
		string Name;
		AmTask* Task;
		AmRunnable* Runnable;
		dcActEvent* ActEvent;
		dcLabel* Label;

		static AmApplication* pInstance;

		//vectors
		vector<dcLabel*> Labels;
		vector<AmRunnable*> Runnables;
		vector<dcActEvent*> ActEvents;
		vector<AmTask*> Tasks;
		vector<dcCore*> Cores;
		vector<dcTag*> tags;

		//maps
		map<string,dcLabel*> LabelsMap;
		map<string,AmRunnable*>RunnablesMap;
		map<string,dcActEvent*>ActEventMap;
		map<string,dcCoreType*> CoreTypesMap;
		map<string,dcQuartz*> QuartzsMap;
		map<string,dcCore*> CoresMap;

		//util
		vector<dcActEvent*> PeriodicEvents;
		vector<dcActEvent*> SporadicEvents;
		vector<dcActEvent*> AperiodicEvent;
		vector<dcActEvent*> DeterministicIrregular;
		vector<dcActEvent*> InterprocessEvent;

		int NoOfPreemptive;
		int NoOfNonPreemptive;

		vector<int> Deadlines;
		vector<int> Priorities;

	};
}





#endif // !AmApplication_H

