#include "dcLabel.h"


namespace DCApplication
{
	using namespace std;

	dcLabel::dcLabel(string NameIn): Name(NameIn), Size(0) {
	}

	void dcLabel::SetName(string NameIn) {
		Name=NameIn;
	}

	string dcLabel::GetName() {
		return Name;
	}

	void dcLabel::SetSize(int SizeIn) {
		Size=SizeIn;
	}

	int dcLabel::GetSize() {
		return Size;
	}

	void dcLabel::SetID(string IDIn) {
		ID=IDIn;
	}

	string dcLabel::GetID() {
		return ID;
	}


}