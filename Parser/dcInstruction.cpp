#include "dcInstruction.h"



namespace DCApplication
{
		dcInstruction::dcInstruction(string NameIn) {
			Name=NameIn;
		}

		void dcInstruction::SetName(string NameIn) {
			Name=NameIn;
		}

		string dcInstruction::GetName() {
			return Name;
		}

		void dcInstruction::Print() {
			cout << Name ;
		}
}