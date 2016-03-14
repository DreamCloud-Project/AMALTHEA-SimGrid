#include "dcTaskEdge.h"

namespace DCApplication
{
	using namespace std;
	dcTaskEdge::dcTaskEdge():ConnectsTo(NULL), Next(NULL), Type(1), Tail(0) {}

	dcTaskEdge::~dcTaskEdge(){}

	void dcTaskEdge::SetConnectTo(dcTask* ConnectToIn){
		ConnectsTo = ConnectToIn;
	}

	void dcTaskEdge::SetNext(dcTaskEdge* NextIn){
		Next = NextIn;
	}

	dcTask* dcTaskEdge::GetConnectTo(){
		return ConnectsTo;
	}

	dcTaskEdge* dcTaskEdge::GetNext(){
		return Next;
	}

	bool dcTaskEdge::GetType(){
		return Type;
	}

	void dcTaskEdge::SetType(bool TypeIn){
		Type = TypeIn;	
	}

	void dcTaskEdge::SetTail(dcTaskEdge* TailIn){
		Tail = TailIn;
	}

	dcTaskEdge* dcTaskEdge::GetTail(){
		return Tail;
	}

}



