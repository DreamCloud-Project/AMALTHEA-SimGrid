#include "dcFixedRunnableExecTime.h"

namespace DCApplication
{
	dcFixedRunnableExecTime::dcFixedRunnableExecTime(string TypeIn): dcRunnableExecutionTime(TypeIn) {
	}

	void dcFixedRunnableExecTime::SetExecutionTime(string ExecTimeIn){
		ExecutionTime = ExecTimeIn;
	}

	string dcFixedRunnableExecTime::GetExecutionTime(){
		return ExecutionTime;
	}

	void dcFixedRunnableExecTime::Print() {
		cout << GetType() ;
	}
	dcFixedRunnableExecTime::~dcFixedRunnableExecTime() {}

}