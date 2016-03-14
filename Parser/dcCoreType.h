#ifndef DC_CORETYPE_H
#define DC_CORETYPE_H

#include <iostream>
#include <list>


namespace DCApplication
{
   using namespace std;

	class dcCoreType {
		string Name;
		string ID;
		int InstructionsPerCycle;
	public:
		dcCoreType(string NameIn);
		void SetName(string NameIn);
		string GetName();
		void SetInstructionsPerCycle(int InstructionsPerCycleIn);
		int GetInstructionsPerCycle();
		void SetID(string IDIn);
		string GetID();
	}; 
}

#endif