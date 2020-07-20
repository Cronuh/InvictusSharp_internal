#pragma once
#include <Windows.h>
#include "Vector.h"
#include "CSpellBook.h"
#define me (DWORD)CObject::GetLocalObject();

class CObject
{
public:
	

	bool IsTurret();
	bool IsMinion();
	bool IsHero();
	bool IsBuilding();
	bool IsMissile();
	bool IsWard();
	bool IsDead();
	bool IsInvalidObject();
	bool IsTargetable();
	bool IsLasthitable();

	//Spell
	bool IsSpellReady(int SpellSlot);
	float GetSpellReadyTime(int SpellSlot);
	float GetSpellCooldown(int SpellSlot);

	bool IsTroyEnt();

	//bool IsTargetable();

	static CObject* GetLocalObject();
	Vector GetPos();

	CObject* GetFirstObject();
	CObject* GetNextObject(CObject* obj);

	bool IsVisible();
	bool IsAlive();
	bool IsValidTarget();
	bool IsInRange();
	bool isEnemyTo(CObject* objToCheck);
	bool IsNeutral();

	float GetDistance(CObject* obj1, CObject* obj2);
	float GetDistToMe();
	float GetAttackRange();
	float GetTrueAttackRange();
	float GetBoundingRadius();
	float GetCurrentHealth();
	float GetMaxHP();
	float GetEffectiveHP();
	float GetEffectiveDamage(CObject* target);
	float GetBaseAD();
	float GetBonusAD();
	float GetTotalAD();
	float GetArmor();
	char* GetChampionName();
	int GetTeam();

	short GetSourceIndex();
	DWORD GetNetworkID();

	CSpellBook* GetSpellBook();
	CSpellInfo* GetSpellInfo();

private:
	bool CompareObjectTypeFlags(int objectTypeFlag);
};
