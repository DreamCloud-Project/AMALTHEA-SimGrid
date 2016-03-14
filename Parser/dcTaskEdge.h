#ifndef EDGE_H_
#define EDGE_H_

#include <iostream>
#include <string>


namespace DCApplication{
	using namespace std;
	class dcTask;
	class dcTaskEdge
	{
		public:
			dcTaskEdge();
			~dcTaskEdge();
			void SetConnectTo(dcTask* ConnectToIn);
			void SetNext(dcTaskEdge* NextIn);
			dcTask* GetConnectTo();
			dcTaskEdge* GetNext();
			bool GetType();
			void SetType(bool TypeIn);
			dcTaskEdge* GetTail();
			void SetTail(dcTaskEdge* TailIn);

		private:
			dcTask *ConnectsTo;
			dcTaskEdge *Next;
			dcTaskEdge *Tail;
			bool Type;
	};
}

#endif /* EDGE_H_ */
