#include "dcExecutionCyclesDeviationInstruction.h"
#include "dcInstruction.h"


namespace DCApplication
{
	dcExecutionCyclesDeviationInstruction::dcExecutionCyclesDeviationInstruction(string NameIn): dcInstruction(NameIn), RemainPromille(0), Mean(0), LowerBound(0), UpperBound(0), SD(0), LowerBoundValid(false), UpperBoundValid(false), RemainPromilleValid(false), MeanValid(false), SDValid(false) {
	}


	double dcExecutionCyclesDeviationInstruction::GetLowerBound() {
		return LowerBound;
	}

	double dcExecutionCyclesDeviationInstruction::GetUpperBound() {
		return UpperBound;
	}

	string dcExecutionCyclesDeviationInstruction::GetType() {
		return Type;
	}

	double dcExecutionCyclesDeviationInstruction::GetRemainPromille() {
		return RemainPromille;
	}

	double dcExecutionCyclesDeviationInstruction::GetMean() {
		return Mean;
	}

	double dcExecutionCyclesDeviationInstruction::GetSD() {
		return SD;
	}

	void dcExecutionCyclesDeviationInstruction::SetLowerBound(double LowerBoundIn) {
		LowerBound=LowerBoundIn;
		LowerBoundValid=true;
	}

	void dcExecutionCyclesDeviationInstruction::SetUpperBound(double UpperBoundIn) {
		UpperBound=UpperBoundIn;
		UpperBoundValid=true;
	}

	void dcExecutionCyclesDeviationInstruction::SetType(string TypeIn) {
		Type=TypeIn;
	}

	void dcExecutionCyclesDeviationInstruction::SetRemainPromille(double RemainPromilleIn) {
		RemainPromille=RemainPromilleIn;
		RemainPromilleValid=true;
	}

	void dcExecutionCyclesDeviationInstruction::SetMean(double MeanIn) {
		Mean=MeanIn;
		MeanValid=true;
	}

	void dcExecutionCyclesDeviationInstruction::SetSD(double SDIn) {
		SD=SDIn;
		SDValid=true;
	}

	double dcExecutionCyclesDeviationInstruction::GetKappa(){
		return Kappa;
	}

	void dcExecutionCyclesDeviationInstruction::SetKappa(double KappaIn){
		Kappa = KappaIn;
		KappaValid=true;
	}

	double dcExecutionCyclesDeviationInstruction::GetLambda(){
		return Lambda;
	}

	void dcExecutionCyclesDeviationInstruction::SetLambda(double LambdaIn){
		Lambda = LambdaIn;
		LambdaValid=true;
	}

	bool dcExecutionCyclesDeviationInstruction::GetLowerBoundValid() {
		return LowerBoundValid;
	}

	bool dcExecutionCyclesDeviationInstruction::GetUpperBoundValid() {
		return UpperBoundValid;
	}

	bool dcExecutionCyclesDeviationInstruction::GetRemainPromilleValid() {
		return RemainPromilleValid;
	}

	bool dcExecutionCyclesDeviationInstruction::GetMeanValid() {
		return MeanValid;
	}

	bool dcExecutionCyclesDeviationInstruction::GetSDValid() {
		return SDValid;
	}

	bool dcExecutionCyclesDeviationInstruction::GetKappaValid() {
		return KappaValid;
	}

	bool dcExecutionCyclesDeviationInstruction::GetLambdaValid() {
		return LambdaValid;
	}

	void dcExecutionCyclesDeviationInstruction::Print() {
		cout << GetName() << " Type: " << Type;
		if (RemainPromilleValid) {
			cout << " RemainPromille: " << RemainPromille;
		}
		if (MeanValid) {
			cout << " Mean: " << Mean;
		}
		if (SDValid) {
			cout << " SD: " << SD;
		}
		if (LowerBoundValid) {
			cout << " LowerBound: " << LowerBound;
		}
		if (UpperBoundValid) {
			cout << " UpperBound: " << UpperBound;
		}
	}

}