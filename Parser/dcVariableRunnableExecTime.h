#ifndef VARIABLERUNNABLEEXECTIME
#define VARIABLERUNNABLEEXECTIME

#include <iostream>
#include <list>
#include "dcRunnableExecutionTime.h"

namespace DCApplication
{
   using namespace std;

   class dcVariableRunnableExecTime : public dcRunnableExecutionTime {
		string LowerBound;
		string UpperBound;
		string ActualExecTime;
	public:
		dcVariableRunnableExecTime(string TypeIn);
		~dcVariableRunnableExecTime();

		void SetLowerBound(string LowerBoundIn);
		void SetUpperBound(string UpperBoundIn);
		void SetActualExecTime(string ActualExecTimeIn);

		string GetLowerBound();
		string GetUpperBound();
		string GetActualExecTime();

		void Print();
	}; 
}

#endif 