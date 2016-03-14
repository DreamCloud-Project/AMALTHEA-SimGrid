#include "dcRunnableExecutionTime.h"


namespace DCApplication
{
	dcRunnableExecutionTime::dcRunnableExecutionTime(string TypeIn){}

	void dcRunnableExecutionTime::Print() {
		cout << Type ;
	}

	void dcRunnableExecutionTime::SetType(string TypeIn){
		Type = TypeIn;
	}

	string dcRunnableExecutionTime::GetType(){
		return Type;
	}

	void dcRunnableExecutionTime::SetResourceType(string TypeIn){
		ResourceType = TypeIn;
	}

	string dcRunnableExecutionTime::GetResourceType(){
		return ResourceType;
	}

}