#include "dcQuartz.h"


namespace DCApplication
{
	dcQuartz::dcQuartz(string NameIn): Name(NameIn), Frequency(0) {
	}

	void dcQuartz::SetName(string NameIn) {
		Name=NameIn;
	}

	string dcQuartz::GetName() {
		return Name;
	}

	void dcQuartz::SetFrequency(int FrequencyIn) {
		Frequency=FrequencyIn;
	}

	int dcQuartz::GetFrequency() {
		return Frequency;
	}

	void dcQuartz::SetID(string IDIn) {
		ID=IDIn;
	}

	string dcQuartz::GetID() {
		return ID;
	}


}