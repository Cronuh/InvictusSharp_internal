#pragma once
#include <Windows.h>
#include "Offsets.h"
#include "Vector.h"
#include "Utils.h"
#include "SpellInfo.h"

class SpellSlot {
public:
	int GetLevel() {
		return *(int*)((DWORD)this + 0x20);
	}

	float GetTime() {
		return *(float*)((DWORD)this + 0x28);
	}

	float GetCD() {
		return *(float*)((DWORD)this + 0x78);
	}

	CSpellInfo* GetSpellInfo() {
		return (CSpellInfo*)((DWORD)this + 0x124);
	}

};