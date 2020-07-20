#pragma once
#include "Utils.h"
class CSpellData
{
public:
	char* GetMissileName() {
		return GetStr((DWORD)this + 0x0058);
	}
	char* GetSpellName() {
		return GetStr((DWORD)this + 0x007C);
	}
	char* GetDescription() {
		return GetStr((DWORD)this + 0x0088);
	}
	float GetEffectAmount() {
		return *(float*)((DWORD)this + 0xD0);
	}
	float GetIncreaseDamage() {
		return *(float*)((DWORD)this + 0xEC);
	}
	float GetSpellDuration() {
		return *(float*)((DWORD)this + 0x108);
	}

	float GetRootDuration() {
		return *(float*)((DWORD)this + 0x15C);
	}
	float GetIncreaseDamageBonus() {
		return *(float*)((DWORD)this + 0x178);
	}
	float GetCoefficient() {
		return *(float*)((DWORD)this + 0x200);
	}
	float GetCoefficient2() {
		return *(float*)((DWORD)this + 0x204);
	}
	int GetMaxHighlightTargets() {
		return *(int*)((DWORD)this + 0x208);
	}
	float GetCooldownTime() {
		return *(float*)((DWORD)this + 0x280);
	}

	float GetDelayCastOffsetPercent() {
		return *(float*)((DWORD)this + 0x29C);
	}

	float GetDelayTotalTimePercent() {
		return *(float*)((DWORD)this + 0x2A0);
	}

	int GetMaxAmmo() {
		return *(int*)((DWORD)this + 0x31C);
	}
	int GetAmmoUsed() {
		return *(int*)((DWORD)this + 0x338);
	}
	float GetAmmoRechargeTime() {
		return *(float*)((DWORD)this + 0x354);
	}

	Vector GetSpellEndPos() {
		Vector endPos = *(Vector*)((DWORD)this + 0x80);
		endPos.Y += 100;
		return endPos;
	}

	float GetSpellWidth() {
		return *(float*)(DWORD)this + 0x44C;
	}

	Vector GetSpellCastPos() {
		return *(Vector*)((DWORD)this + 0x8C);
	}

	float GetMissileSpeed() {
		return *(float*)((DWORD)this + 0x450);
	}
	CSpellData* GetSpellData() {
		return *(CSpellData**)((DWORD)this + 0x38);
	}
};