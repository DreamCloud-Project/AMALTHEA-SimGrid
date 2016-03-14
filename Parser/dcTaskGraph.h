#ifndef dcTaskGraph_H_
#define dcTaskGraph_H_

#include "dcTask.h"

namespace DCApplication{
	using namespace std;

	class dcTaskGraph{

		public:
			dcTaskGraph();
			~dcTaskGraph();
			void SetHead(dcTask* HeadIn);
			dcTask* GetHead();
			void SetTail(dcTask* TailIn);
			dcTask* GetTail();
		private:
			dcTask *Head;
			dcTask *Tail;
	};
}

#endif /* dcTaskGraph_H_ */
