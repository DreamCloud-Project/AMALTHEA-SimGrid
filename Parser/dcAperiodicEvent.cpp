#include "dcAperiodicEvent.h"

namespace DCApplication
{
	dcAperiodicEvent::dcAperiodicEvent(string NameIn): dcActEvent(NameIn) {}

	void dcAperiodicEvent::SetVal(string ValIn){
		Val = ValIn;
	}

	string dcAperiodicEvent::GetVal(){
		return Val;
	}

	void dcAperiodicEvent::Print() {
			cout << GetName() ;
	}

	dcAperiodicEvent::~dcAperiodicEvent() {}

}