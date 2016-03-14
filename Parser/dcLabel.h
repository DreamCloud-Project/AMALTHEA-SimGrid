#ifndef DC_LABEL_H
#define DC_LABEL_H

#include <iostream>
#include <list>


namespace DCApplication{

	using namespace std;

	class dcLabel {
		string Name;
		string ID;
		int Size;
	public:
		dcLabel(string NameIn);
		void SetName(string NameIn);
		string GetName();
		void SetSize(int SizeIn);
		int GetSize();
		void SetID(string IDIn);
		string GetID();
	}; 
}

#endif // !DC_LABEL_H