#include "dcTag.h"

namespace DCApplication
{
	dcTag::dcTag(string NameIn): Name(NameIn){
	}

	void dcTag::SetName(string NameIn) {
		Name=NameIn;
	}

	string dcTag::GetName() {
		return Name;
	}
	void dcTag::SetID(string IDIn){
		ID = IDIn;
	}

	string dcTag::GetID(){
		return ID;
	}
}