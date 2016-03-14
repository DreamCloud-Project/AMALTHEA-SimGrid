#include "dcVariableRunnableExecTime.h"

namespace DCApplication
{
	dcVariableRunnableExecTime::dcVariableRunnableExecTime(string TypeIn): dcRunnableExecutionTime(TypeIn) {
	}

	void dcVariableRunnableExecTime::SetLowerBound(string LowerBoundIn){
		LowerBound = LowerBoundIn;
	}

	void dcVariableRunnableExecTime::SetUpperBound(string UpperBoundIn){
		UpperBound = UpperBoundIn;
	}

	void dcVariableRunnableExecTime::SetActualExecTime(string ActualExecTimeIn){
		ActualExecTime = ActualExecTimeIn;
	}

	string dcVariableRunnableExecTime::GetLowerBound(){
		return LowerBound;
	}

	string dcVariableRunnableExecTime::GetUpperBound(){
		return UpperBound;
	}

	string dcVariableRunnableExecTime::GetActualExecTime(){
		return ActualExecTime;
	}


	void dcVariableRunnableExecTime::Print() {
		cout << GetType() ;
	}
	dcVariableRunnableExecTime::~dcVariableRunnableExecTime() {}

}