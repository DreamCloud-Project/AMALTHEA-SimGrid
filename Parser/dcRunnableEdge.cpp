#include "dcRunnableEdge.h"

namespace DCApplication
{
	using namespace std;
	dcRunnableEdge::dcRunnableEdge():ConnectsTo(NULL), Next(NULL), Tail(0){}

	void dcRunnableEdge::SetConnectTo(dcRunnable* ConnectToIn){
		ConnectsTo = ConnectToIn;
	}

	void dcRunnableEdge::SetNext(dcRunnableEdge* NextIn){
		Next = NextIn;
	}

	dcRunnable* dcRunnableEdge::GetConnectTo(){
		return ConnectsTo;
	}

	dcRunnableEdge* dcRunnableEdge::GetNext(){
		return Next;
	}

	void dcRunnableEdge::SetTail(dcRunnableEdge* TailIn){
		Tail = TailIn;
	}

	dcRunnableEdge* dcRunnableEdge::GetTail(){
		return Tail;
	}
}



