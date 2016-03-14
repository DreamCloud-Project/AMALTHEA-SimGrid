#ifndef DC_REMOTEACCESSINSTRUCTION_H
#define DC_REMOTEACCESSINSTRUCTION_H

#include <iostream>
#include <list>
#include "dcInstruction.h"
#include "dcLabel.h"

namespace DCApplication
{
   using namespace std;

	class dcRemoteAccessInstruction : public dcInstruction {
		dcLabel* Label_;
		bool Write_;

	public:
		dcRemoteAccessInstruction(string NameIn);
		~dcRemoteAccessInstruction();
		void SetLabel(dcLabel* LabelIn);
		dcLabel* GetLabel();
		void SetWrite(bool WriteIn);
		bool GetWrite();
		void Print();
	}; 


}

#endif // DC_REMOTEACCESSINSTRUCTION_H