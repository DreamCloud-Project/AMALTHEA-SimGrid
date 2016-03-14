#ifndef DC_INSTRUCTION_H
#define DC_INSTRUCTION_H

#include <iostream>
#include <string>
#include <list>

namespace DCApplication
{
   using namespace std;

	class dcInstruction {
		string Name;
	public:
		dcInstruction(string NameIn);
		virtual ~dcInstruction() {}
		void SetName(string NameIn);
		string GetName();
		virtual void Print();
	}; 


}

#endif // DC_INSTRUCTION_H