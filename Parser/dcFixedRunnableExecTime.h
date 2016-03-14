#ifndef DC_FIXEDRUNNABLEEXECTIME_H
#define DC_FIXEDRUNNABLEEXECTIME_H

#include <iostream>
#include <list>
#include "dcRunnableExecutionTime.h"

namespace DCApplication
{
   using namespace std;

   class dcFixedRunnableExecTime : public dcRunnableExecutionTime {
		string ExecutionTime;

	public:
		dcFixedRunnableExecTime(string TypeIn);
		~dcFixedRunnableExecTime();
		string GetExecutionTime();
		void SetExecutionTime(string ExecutionTimeIn);

		void Print();
	}; 
}

#endif 