#ifndef RUNNABLELABEL_H_
#define RUNNABLELABEL_H_


#include <iostream>
#include <string>

namespace DCApplication{
	using namespace std;
	class dcRunnable;
	class dcRunnableEdge
	{
		public:
			dcRunnableEdge();
			void SetConnectTo(dcRunnable* ConnectToIn);
			void SetNext(dcRunnableEdge* NextIn);
			dcRunnable* GetConnectTo();
			dcRunnableEdge* GetNext();
			dcRunnableEdge* GetTail();
			void SetTail(dcRunnableEdge* TailIn);

		private:
			dcRunnable *ConnectsTo;
			dcRunnableEdge *Next;
			dcRunnableEdge *Tail;
	};
}



#endif /* RUNNABLELABEL_H_ */