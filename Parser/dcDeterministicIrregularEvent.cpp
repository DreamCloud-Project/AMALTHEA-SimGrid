#include "dcDeterministicIrregularEvent.h"

namespace DCApplication
{
	dcDeterministicIrregularEvent::dcDeterministicIrregularEvent(string NameIn): dcActEvent(NameIn) {}

	void dcDeterministicIrregularEvent::SetArrivalTimes(vector<string> ArrivalTimesIn){
		ArrivalTimes = ArrivalTimesIn;
	}

	vector<string> dcDeterministicIrregularEvent::GetArrivalTimes(){
		return ArrivalTimes;
	}

	void dcDeterministicIrregularEvent::Print() {
			cout << GetName() ;
	}

	void dcDeterministicIrregularEvent::AddArrivalTimes(string ArrivalTimesIn){
		ArrivalTimes.push_back(ArrivalTimesIn);
	}
	dcDeterministicIrregularEvent::~dcDeterministicIrregularEvent() {}

}
