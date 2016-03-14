#include "dcRemoteAccessInstruction.h"


namespace DCApplication
{
	dcRemoteAccessInstruction::dcRemoteAccessInstruction(string NameIn): dcInstruction(NameIn), Label_(NULL), Write_(false) {
	}

	dcLabel* dcRemoteAccessInstruction::GetLabel() {
		return Label_;
	}


	void dcRemoteAccessInstruction::SetLabel(dcLabel* LabelIn) {
		Label_=LabelIn;
	}

	void dcRemoteAccessInstruction::SetWrite(bool WriteIn) {
		Write_=WriteIn;
	}

	bool dcRemoteAccessInstruction::GetWrite() {
		return Write_;
	}

	dcRemoteAccessInstruction::~dcRemoteAccessInstruction() {
		//delete Label_;
	}
	void dcRemoteAccessInstruction::Print() {
		cout << GetName() << " Label: " << GetLabel()->GetName() << " Size: " << GetLabel()->GetSize();
		if (Write_) {
			cout << " W";
		}
		else {
			cout << " R";
		}
	}
}
