#pragma once
#include "CObject.h"



class CTargetSelector
{
public:
	static CObject* GetLowestHPTarget();
	static CObject* GetClosestTarget();
	static CObject* GetLasthitTarget();
	static CObject* GetWaveclearTarget();
	static void SetTSTarget();

	static CObject* target; 
};