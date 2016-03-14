#ifndef DC_SPORADICEVENT_H
#define DC_SPORADICEVENT_H

#include <iostream>
#include <list>
#include "dcActEvent.h"

namespace DCApplication
{
	using namespace std;

	class dcSporadicEvent : public dcActEvent {
		double LowerBound;
		double UpperBound;
		string DistType;
		double Mean;
		double SD;
		double RemainPromille;
		double Kappa;
		double Lambda;

		bool LowerBoundValid;
		bool UpperBoundValid;
		bool RemainPromilleValid;
		bool MeanValid;
		bool SDValid;
		bool KappaValid;
		bool LambdaValid;

	public:
		dcSporadicEvent(string NameIn);
		~dcSporadicEvent();

		double GetLowerBound();
		void SetLowerBound(double LowerBoundIn);
		double GetUpperBound();
		void SetUpperBound(double UpperBoundIn);
		double GetSd();
		void SetSD(double SdIn);
		double GetMean();
		void SetMean(double MeanIn);
		double GetRemainPromille();
		void SetRemainPromille(double PRemanPromilleIn);
		double GetKappa();
		void SetKappa(double KappaIn);
		double GetLambda();
		void SetLambda(double LambdaIn);
		void Print();
		void SetDistType(string TypeIn);
		string GetDistType();

		bool GetLowerBoundValid(); 
		bool GetUpperBoundValid();
		bool GetRemainPromilleValid(); 
		bool GetMeanValid();
		bool GetSDValid();
		bool GetKappaValid();
		bool GetLambdaValid();
	}; 
}

#endif //