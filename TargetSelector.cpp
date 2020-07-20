#include "TargetSelector.h"
#include "OrbwalkerEngine.h"
#include "Orbwalker.h"
#include "GameFunctions.h"

void CTargetSelector::SetTSTarget()
{
		CTargetSelector::target = NULL; //reset target

		
		if (GetAsyncKeyState(0x58))
		{
			CTargetSelector::target = CTargetSelector::GetLasthitTarget();
		}
		else if (GetAsyncKeyState(0x56))
		{
			CTargetSelector::target = CTargetSelector::GetWaveclearTarget();
		}
		else
		{
			switch (OrbwalkerEngine::m_TargetSelectorMode)
			{
			case 0:
				CTargetSelector::target = CTargetSelector::GetClosestTarget();
				break;
			case 1:
				CTargetSelector::target = CTargetSelector::GetLowestHPTarget();
				break;
			}
		}
		
}

CObject* CTargetSelector::GetLowestHPTarget()
{
	CObject* lowestHPTarget = NULL;
	Vector targetPos;

	CObject holzer;
	auto currentObj = holzer.GetFirstObject();

	while (currentObj)
	{
		if (currentObj->IsHero())
		{
			if (currentObj->IsValidTarget())
			{
				if (lowestHPTarget == NULL)
					lowestHPTarget = currentObj;
				else
					if (lowestHPTarget->GetCurrentHealth() > currentObj->GetCurrentHealth())
						lowestHPTarget = currentObj;
			}
		}

		currentObj = holzer.GetNextObject(currentObj);
	}

	if (lowestHPTarget != NULL)
	{
		Functions.WorldToScreen(&lowestHPTarget->GetPos(), &targetPos);
		Orbwalker::targetX = targetPos.X;
		Orbwalker::targetY = targetPos.Y;
	}


	return lowestHPTarget;
}

CObject* CTargetSelector::GetClosestTarget()
{
	// REMAKE IT
	return NULL;
}



//MINION LOGICS


CObject* CTargetSelector::GetLasthitTarget()
{
	CObject* lasthitTarget = NULL;
	Vector targetPos;
	CObject holzer;
	auto currentObj = holzer.GetFirstObject();

	while (currentObj)
	{
		if (currentObj->IsMinion())
		{
			if (currentObj->IsValidTarget())
			{
				if (currentObj->IsLasthitable())
				{
					if (lasthitTarget == NULL)
						lasthitTarget = currentObj;
					
					else if (currentObj->GetCurrentHealth() < lasthitTarget->GetCurrentHealth() || currentObj->GetDistToMe() <= 50)
						lasthitTarget = currentObj;
				}
			}
		}
		currentObj = holzer.GetNextObject(currentObj);
	}

	if (lasthitTarget != NULL)
	{
		Functions.WorldToScreen(&lasthitTarget->GetPos(), &targetPos);
		Orbwalker::targetX = targetPos.X;
		Orbwalker::targetY = targetPos.Y;
	}

	return lasthitTarget;
}


CObject* CTargetSelector::GetWaveclearTarget()
{
	CObject* waveclearTarget = NULL;
	Vector targetPos;
	CObject holzer;
	auto currentObj = holzer.GetFirstObject();

	while (currentObj)
	{

		if (currentObj->IsNeutral())
		{
			if (currentObj->IsInRange() && currentObj->IsAlive() && currentObj->IsVisible() && !currentObj->IsInvalidObject() && currentObj->IsTargetable())
			{
				if (waveclearTarget == NULL)
					waveclearTarget = currentObj;

				else if (currentObj->GetCurrentHealth() < waveclearTarget->GetCurrentHealth())
					waveclearTarget = currentObj;
			}
		}
		else if (currentObj->IsMinion() || currentObj->IsBuilding())
		{
			if (currentObj->IsValidTarget())
			{
				if (waveclearTarget == NULL)
					waveclearTarget = currentObj;

				if (currentObj->IsLasthitable())
					waveclearTarget = currentObj;
				else if (currentObj->GetCurrentHealth() < waveclearTarget->GetCurrentHealth())
					waveclearTarget = currentObj;

			}
		}

		currentObj = holzer.GetNextObject(currentObj);
	}

	if (waveclearTarget != NULL)
	{
		Functions.WorldToScreen(&waveclearTarget->GetPos(), &targetPos);
		Orbwalker::targetX = targetPos.X;
		Orbwalker::targetY = targetPos.Y;
	}

	return waveclearTarget;
}