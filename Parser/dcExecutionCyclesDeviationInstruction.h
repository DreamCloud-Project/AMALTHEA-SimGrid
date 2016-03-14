#ifndef DC_EXECUTIONCYCLESDEVIATIONINSTRUCTION_H
#define DC_EXECUTIONCYCLESDEVIATIONINSTRUCTION_H

#include <iostream>
#include <list>
#include "dcInstruction.h"
#include <vector>


namespace DCApplication
{
   using namespace std;

   class dcExecutionCyclesDeviationInstruction : public dcInstruction {
        double LowerBound;
        double UpperBound;
        string Type;
		double RemainPromille;
		double Mean;
		double SD;
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
		dcExecutionCyclesDeviationInstruction(string NameIn);

		double GetLowerBound();
        double GetUpperBound();
        string GetType();
		double GetRemainPromille();
		double GetMean();
		double GetSD();
		double GetLambda();
		double GetKappa();

		void SetLowerBound(double);
		void SetUpperBound(double);
		void SetType(string);
		void SetRemainPromille(double);
		void SetMean(double);
		void SetSD(double);
		void SetLambda(double LambdaIn);
		void SetKappa(double KappaIn);

		bool GetLowerBoundValid(); 
		bool GetUpperBoundValid();
		bool GetRemainPromilleValid(); 
		bool GetMeanValid();
		bool GetSDValid();
		bool GetKappaValid();
		bool GetLambdaValid();

		void Print();


	}; 


}

#endif // DC_EXECUTIONCYCLESDEVIATIONINSTRUCTION_H