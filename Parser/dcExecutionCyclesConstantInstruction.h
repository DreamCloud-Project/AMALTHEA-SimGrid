#ifndef DC_EXECUTIONCYCLESCONSTANTINSTRUCTION_H
#define DC_EXECUTIONCYCLESCONSTANTINSTRUCTION_H

#include <iostream>
#include <list>
#include "dcInstruction.h"

namespace DCApplication
{
   using namespace std;

	class dcExecutionCyclesConstantInstruction : public dcInstruction {

		int Value;
	public:
		dcExecutionCyclesConstantInstruction(string NameIn);
		int GetValue();
        void SetValue(int ValueIn);
		void Print();

	}; 


}

#endif // DC_EXECUTIONCYCLESCONSTANTINSTRUCTION_H