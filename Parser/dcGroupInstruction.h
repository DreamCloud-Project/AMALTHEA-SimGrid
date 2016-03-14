#ifndef DC_GROUPINSTRUCTION_H
#define DC_GROUPINSTRUCTION_H

#include <iostream>
#include <list>
#include "dcInstruction.h"

namespace DCApplication
{
   using namespace std;

	class dcGroupInstruction : public dcInstruction {
		string Name;
	public:
		dcGroupInstruction(string NameIn);




	}; 


}

#endif // DC_GROUPINSTRUCTION_H