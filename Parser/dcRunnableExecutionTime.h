#ifndef DC_RUNEXECTIME
#define DC_RUNEXECTIME

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


namespace DCApplication
{
	using namespace std;

	class dcRunnableExecutionTime {

		string Type;
		string ResourceType;
	public:
		dcRunnableExecutionTime(string TypeIn);
		void SetType(string TypeIn);
		string GetType();

		void SetResourceType(string TypeIn);
		string GetResourceType();

		virtual ~dcRunnableExecutionTime() {}
		virtual void Print();
		
	}; 


}
#endif 