#ifndef DC_QUARTZ_H
#define DC_QUARTZ_H

#include <iostream>
#include <list>


namespace DCApplication
{
   using namespace std;

	class dcQuartz {
		string Name;
		string ID;
		int Frequency;
	public:
		dcQuartz(string NameIn);
		void SetName(string NameIn);
		string GetName();
		void SetFrequency(int FrequencyIn);
		int GetFrequency();
		void SetID(string IDIn);
		string GetID();
	}; 


}

#endif // DC_QUARTZ_H