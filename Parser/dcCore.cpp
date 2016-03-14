#include "dcCore.h"


namespace DCApplication
{
	dcCore::dcCore(string NameIn): Name(NameIn), CoreType_(NULL), Quartz_(NULL) {
	}

	void dcCore::SetName(string NameIn) {
		Name=NameIn;
	}

	string dcCore::GetName() {
		return Name;
	}

	void dcCore::SetCoreType(dcCoreType* CoreTypeIn) {
		CoreType_=CoreTypeIn;
	}

	dcCoreType* dcCore::GetCoreType() {
		return CoreType_;
	}

	void dcCore::SetQuartz(dcQuartz* QuartzIn) {
		Quartz_=QuartzIn;
	}

	dcQuartz* dcCore::GetQuartz() {
		return Quartz_;
	}

	void dcCore::SetID(string IDIn) {
		ID=IDIn;
	}

	string dcCore::GetID() {
		return ID;
	}


}