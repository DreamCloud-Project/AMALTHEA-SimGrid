#include "dcMicrocontroller.h"

namespace DCApplication
{
	dcMicrocontroller::dcMicrocontroller(string NameIn): Name(NameIn), Size(0) {
	}

	void dcMicrocontroller::SetName(string NameIn) {
		Name=NameIn;
	}

	string dcMicrocontroller::GetName() {
		return Name;
	}

	void dcMicrocontroller::SetSize(int SizeIn) {
		Size=SizeIn;
	}

	int dcMicrocontroller::GetSize() {
		return Size;
	}

	void dcMicrocontroller::SetID(string IDIn) {
		ID=IDIn;
	}

	string dcMicrocontroller::GetID() {
		return ID;
	}


}