#include "dcPeriodicEvent.h"

namespace DCApplication
{
	dcPeriodicEvent::dcPeriodicEvent(string NameIn): dcActEvent(NameIn) {
	}

	void dcPeriodicEvent::SetRecurrence(pair<int,string> RecurrenceIn) {
		Recurrence=RecurrenceIn;
	}

	void dcPeriodicEvent::SetOffset(pair<int,string> OffsetIn) {
		Offset=OffsetIn;
	}

	pair<int,string> dcPeriodicEvent::GetRecurrence() {
		return Recurrence;
	}

	pair<int,string> dcPeriodicEvent::GetOffset() {
		return Offset;
	}

	void dcPeriodicEvent::Print() {
			cout << GetName() ;
	}
	dcPeriodicEvent::~dcPeriodicEvent() {}

}