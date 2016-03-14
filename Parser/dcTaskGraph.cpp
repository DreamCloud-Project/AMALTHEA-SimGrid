#include "dcTaskGraph.h"

namespace DCApplication
{	using namespace std;

dcTaskGraph::dcTaskGraph() : Head(0), Tail(0){}
	
	dcTaskGraph::~dcTaskGraph(){}

	void dcTaskGraph::SetHead(dcTask* HeadIn){
		Head = HeadIn;
	}

	dcTask* dcTaskGraph::GetHead(){
		return Head;
	}

	void dcTaskGraph::SetTail(dcTask* TailIn){
		Tail = TailIn;
	}

	dcTask* dcTaskGraph::GetTail(){
		return Tail;
	}
}
