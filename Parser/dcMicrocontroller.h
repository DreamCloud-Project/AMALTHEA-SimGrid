#ifndef DC_MICROCONTROLLER_H
#define DC_MICROCONTROLLER_H

#include <iostream>
#include <list>


namespace DCApplication
{
   using namespace std;

	class dcMicrocontroller {
		string Name;
		string ID;
		int Size;
	public:
		dcMicrocontroller(string NameIn);
		void SetName(string NameIn);
		string GetName();
		void SetSize(int SizeIn);
		int GetSize();
		void SetID(string IDIn);
		string GetID();
	}; 


}

#endif // DC_MICROCONTROLLER_H