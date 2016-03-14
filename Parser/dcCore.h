#ifndef IA_AMCORE_H
#define IA_AMCORE_H

#include <iostream>
#include <list>
#include "dcCoreType.h"
#include "dcQuartz.h"

namespace DCApplication
{
   using namespace std;

	class dcCore {
		string Name;
		string ID;
		dcCoreType* CoreType_;
		dcQuartz *Quartz_;
	public:
		dcCore(string NameIn);
		void SetName(string NameIn);
		string GetName();
		void SetCoreType(dcCoreType* CoreTypeIn);
		dcCoreType* GetCoreType();
		void SetID(string IDIn);
		string GetID();
		void SetQuartz(dcQuartz* QuartzIn);
		dcQuartz* GetQuartz();
		
	}; 
}

#endif // IA_AMCORE_H