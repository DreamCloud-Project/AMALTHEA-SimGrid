#include "dcCoreType.h"


namespace DCApplication
{
	dcCoreType::dcCoreType(string NameIn): Name(NameIn), InstructionsPerCycle(0) {
	}

	void dcCoreType::SetName(string NameIn) {
		Name=NameIn;
	}

	string dcCoreType::GetName() {
		return Name;
	}

	void dcCoreType::SetInstructionsPerCycle(int InstructionsPerCycleIn) {
		InstructionsPerCycle=InstructionsPerCycleIn;
	}

	int dcCoreType::GetInstructionsPerCycle() {
		return InstructionsPerCycle;
	}

	void dcCoreType::SetID(string IDIn) {
		ID=IDIn;
	}

	string dcCoreType::GetID() {
		return ID;
	}
}