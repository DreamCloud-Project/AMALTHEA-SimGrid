#include "dcSporadicEvent.h"


namespace DCApplication
{
	dcSporadicEvent::dcSporadicEvent(string NameIn): dcActEvent(NameIn) {
	}

	double dcSporadicEvent::GetLowerBound(){
		return LowerBound;
	}

	double dcSporadicEvent::GetUpperBound(){
		return UpperBound;
	}

	void dcSporadicEvent::SetLowerBound(double LowerBoundsIn){
		LowerBound = LowerBoundsIn;
		LowerBoundValid=true;
	}

	void dcSporadicEvent::SetUpperBound(double UpperBoundIn){
		UpperBound = UpperBoundIn;
		UpperBoundValid=true;
	}

	double dcSporadicEvent::GetSd(){
		return SD;
	}

	void dcSporadicEvent::SetSD(double SdIn){
		SD = SdIn;
		SDValid=true;
	}

	double dcSporadicEvent::GetMean(){
		return Mean;
	}

	void dcSporadicEvent::SetMean(double MeanIn){
		Mean = MeanIn;
		MeanValid=true;
	}

	double dcSporadicEvent::GetRemainPromille(){
		return RemainPromille;
	}

	void dcSporadicEvent::SetRemainPromille(double PRemanPromilleIn){
		RemainPromille = PRemanPromilleIn;
		RemainPromilleValid=true;
	}

	double dcSporadicEvent::GetKappa(){
		return Kappa;
	}

	void dcSporadicEvent::SetKappa(double KappaIn){
		Kappa = KappaIn;
		KappaValid=true;
	}

	double dcSporadicEvent::GetLambda(){
		return Lambda;
	}

	void dcSporadicEvent::SetLambda(double LambdaIn){
		Lambda = LambdaIn;
		LambdaValid=true;
	}

	void dcSporadicEvent::Print() {
		cout << GetName() << " Type: " << DistType;

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
	dcSporadicEvent::~dcSporadicEvent() {}

	void dcSporadicEvent::SetDistType(string TypeIn){
		DistType = TypeIn;
	}

	string dcSporadicEvent::GetDistType(){
		return DistType;
	}

	bool dcSporadicEvent::GetLowerBoundValid() {
		return LowerBoundValid;
	}

	bool dcSporadicEvent::GetUpperBoundValid() {
		return UpperBoundValid;
	}

	bool dcSporadicEvent::GetRemainPromilleValid() {
		return RemainPromilleValid;
	}

	bool dcSporadicEvent::GetMeanValid() {
		return MeanValid;
	}

	bool dcSporadicEvent::GetSDValid() {
		return SDValid;
	}

	bool dcSporadicEvent::GetKappaValid() {
		return KappaValid;
	}

	bool dcSporadicEvent::GetLambdaValid() {
		return LambdaValid;
	}
}