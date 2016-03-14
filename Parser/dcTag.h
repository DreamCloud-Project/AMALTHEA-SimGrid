#ifndef DC_TAG_H
#define DC_TAG_H

#include <iostream>
#include <list>


namespace DCApplication
{
   using namespace std;

	class dcTag {
		string Name;
		string ID;
	public:
		dcTag(string NameIn);
		void SetName(string NameIn);
		string GetName();
		void SetID(string IDIn);
		string GetID();
	}; 


}

#endif // DC_TAG_H