#include "CObject.h"
#include "Utils.h"
#include "Offsets.h"
#include "GameFunctions.h"
#include "ObjectFlags.h"
#include "OrbwalkerEngine.h"


CObject* CObject::GetLocalObject()
{
	auto retAddr = *(DWORD*)((DWORD)GetModuleHandleA(NULL) + oLocalPlayer);
	return (CObject*)retAddr;

}

CObject* CObject::GetFirstObject()
{
	typedef CObject* (__thiscall* fnGetFirst)(void*);
	return ((fnGetFirst)((DWORD)GetModuleHandleA(NULL) + oGetFirstObject))(*(void**)((DWORD)GetModuleHandleA(NULL) + oObjManager));
}


CObject* CObject::GetNextObject(CObject* object)
{
	typedef CObject* (__thiscall* fnGetNext)(void*, CObject*);
	return ((fnGetNext)((DWORD)GetModuleHandleA(NULL) + oGetNextObject))(*(void**)((DWORD)GetModuleHandleA(NULL) + oObjManager), object);
}


Vector CObject::GetPos()
{
	return *(Vector*)((DWORD)this + oObjPos);
}

float CObject::GetDistance(CObject* obj1, CObject* obj2)
{
	return obj1->GetPos().DistTo(obj2->GetPos());
}

float CObject::GetDistToMe()
{
	return this->GetPos().DistTo(GetLocalObject()->GetPos());
}

bool CObject::IsVisible()
{
	return *(bool*)((DWORD)this + oObjVisibility);
}

bool CObject::IsWard()
{
	return this->GetMaxHP() == 3.f;
}

bool CObject::IsAlive()
{
	return this->GetCurrentHealth() > 0.0f;
}

bool CObject::IsValidTarget()
{
	return !this->IsDead() && this->IsAlive() && this->IsInRange() && this->IsVisible() && !this->IsInvalidObject() && this->isEnemyTo(CObject::GetLocalObject()) && this->IsTargetable();
}


bool CObject::IsInRange()
{
	return this->GetDistToMe() < GetLocalObject()->GetTrueAttackRange();
}

bool CObject::IsLasthitable()
{
	return CObject::GetLocalObject()->GetEffectiveDamage(this) > this->GetEffectiveHP();
}

bool CObject::isEnemyTo(CObject* objToCheck)
{
	return this->GetTeam() != objToCheck->GetTeam();
}

bool CObject::IsNeutral()
{
	return this->GetTeam() == (int)EGameObjectTeam::eNeutral;
}

float CObject::GetSpellCooldown(int SpellSlot)
{
	return this->GetSpellBook()->GetSpellSlotByID(SpellSlot)->GetCD();
}

float CObject::GetSpellReadyTime(int SpellSlot)
{
	return this->GetSpellBook()->GetSpellSlotByID(SpellSlot)->GetTime();
}

bool CObject::IsSpellReady(int SpellSlot)
{
	return this->GetSpellBook()->GetSpellSlotByID(SpellSlot)->GetLevel() >= 1 && OrbwalkerEngine::GetGameTime() >= this->GetSpellReadyTime(SpellSlot);
}

CSpellBook* CObject::GetSpellBook()
{
	return (CSpellBook*)((DWORD)this + oObjSpellBook);
}

CSpellInfo* CObject::GetSpellInfo() {
	return (CSpellInfo*)((DWORD)this + 0x124);
}

float CObject::GetArmor()
{
	return *(float*)((DWORD)this + oObjArmor);
}

float CObject::GetAttackRange()
{
	return *(float*)((DWORD)this + oObjAtkRange);
}

float CObject::GetBoundingRadius()
{
	typedef float(__thiscall* OriginalFn)(PVOID);
	return CallVirtual<OriginalFn>(this, 36)(this);
}

float CObject::GetTrueAttackRange()
{
	return this->GetAttackRange() + this->GetBoundingRadius();
}

float CObject::GetCurrentHealth()
{
	return *(float*)((DWORD)this + oObjHealth);
}

float CObject::GetMaxHP()
{
	return *(float*)((DWORD)this + oObjMaxHealth);
}

float CObject::GetEffectiveHP()
{
	return this->GetCurrentHealth() * (100.0f + this->GetArmor()) / 100.0f;
}

float CObject::GetEffectiveDamage(CObject* target)
{
	return this->GetTotalAD() * (100 / (100 + target->GetArmor()));
}

float CObject::GetBaseAD()
{
	return *(float*)((DWORD)this + oObjBaseAtk);
}

float CObject::GetBonusAD()
{
	return *(float*)((DWORD)this + oObjBonusAtk);
}

float CObject::GetTotalAD()
{
	return this->GetBaseAD() + this->GetBonusAD();
}

char* CObject::GetChampionName()
{
	return GetStr((DWORD)this + oObjChampionName);
}

int CObject::GetTeam()
{
	return *(int*)((DWORD)this + oObjTeam);
}

short CObject::GetSourceIndex()
{
	return *(short*)((DWORD)this + 20);
}

DWORD CObject::GetNetworkID()
{
	return *(DWORD*)((DWORD)this + oObjNetworkID);
}


bool CObject::CompareObjectTypeFlags(int objectTypeFlag)
{
	unsigned __int8* v2; // edi
	unsigned int v3; // edx
	unsigned int v4; // esi
	int* v5; // ecx
	int v6; // eax
	unsigned __int8 v7; // al
	unsigned int v8; // eax
	unsigned __int8* v9; // edx
	char v10; // cl
	int objectId; // [esp+8h] [ebp-4h]

	v2 = (unsigned __int8*)this;
	v3 = 0;
	v4 = *(BYTE*)(v2 + 81);

	objectId = *(DWORD*)&v2[4 * v2[88] + 92];
	if (v4)
	{
		v5 = (int*)(this + 84);
		do
		{
			v6 = *v5;
			++v5;
			*(&objectId + v3) ^= ~v6;
			++v3;
		} while (v3 < v4);
	}
	v7 = v2[82];
	if (v7)
	{
		v8 = 4 - v7;
		if (v8 < 4)
		{
			v9 = &v2[v8 + 84];
			do
			{
				v10 = *v9++;
				*((BYTE*)&objectId + v8++) ^= ~v10;
			} while (v8 < 4);
		}
	}

	return (objectId & objectTypeFlag) != 0;
}


CFunctions Functions;

bool CObject::IsDead() {
	return CompareObjectTypeFlags((int)ECObjectTypeFlags::DeadObject);
}

bool CObject::IsMinion() {
	return CompareObjectTypeFlags((int)ECObjectTypeFlags::Minion);
}

bool CObject::IsInvalidObject()
{
	return CompareObjectTypeFlags((int)ECObjectTypeFlags::InvalidObject);
}

bool CObject::IsTurret() {
	return CompareObjectTypeFlags((int)ECObjectTypeFlags::Turret);
}

bool CObject::IsHero() {
	return CompareObjectTypeFlags((int)ECObjectTypeFlags::Hero);
}

bool CObject::IsMissile() {
	return CompareObjectTypeFlags((int)ECObjectTypeFlags::Missile);
}


bool CObject::IsTargetable() {
	return Functions.IsTargetable(this);
}

bool CObject::IsBuilding() {
	return CompareObjectTypeFlags((int)ECObjectTypeFlags::Building);
}

bool CObject::IsTroyEnt() {
	return CompareObjectTypeFlags((int)ECObjectTypeFlags::Unknown2); //Need ObjectTypeFlag for Troy
}
