#ifndef DC_ACTEVENT_H
#define DC_ACTEVENT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


namespace DCApplication
{
	using namespace std;
	class AmTask;

	class dcActEvent {

		string Name;
		string ID;
		string Type;
		vector<AmTask*> Sources;
		vector<AmTask*> Destinations;

	public:
		dcActEvent(string NameIn);
		void SetName(string NameIn);
		string GetName();
		void SetID(string IDIn);
		string GetID();
		void AddSource(AmTask* TaskIn);
		void AddDestination(AmTask* TaskIn);
		int GetNoOfSources();
		int GetNoOfDestinations();
		bool IsTaskInSources(AmTask *TaskIn);
		bool IsTaskInDestinations(AmTask *TaskIn);
		AmTask* GetSource(int Index);
		AmTask* GetDestination(int Index);
		void printInfo();
		virtual ~dcActEvent() {}
		virtual void Print();
		void SetType(string TypeIn);
		string GetType();
		vector<AmTask*> GetAllSource();
		vector<AmTask*> GetAllDestination();
	}; 
}

#endif // DC_ACTEVENT_H