#pragma once
#pragma once
#include "CObject.h"
#include "StaticEnums.h"
#include <math.h>
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\d3dx9math.h"
#include "C:\Users\Shadow\source\repos\InvictusSharp\InvictusSharp\imgui\imgui.h"



class Typedefs
{
public:
	typedef float(__cdecl* fnGetAttackCastDelay)(CObject* pObj);
	typedef float(__cdecl* fnGetAttackDelay)(CObject* pObj);
	typedef int(__thiscall* fnGetPing)(void* thisptr);
	typedef bool(__cdecl* fnWorldToScreen)(Vector* in, Vector* out);
	typedef bool(__thiscall* fnIsTargetable)(CObject* pObj);
	//typedef void(__cdecl* fnDrawCircle)(Vector* position, float range, int* color, int a4, float a5, int a6, float alpha);
};

class CFunctions
{
public:
	Typedefs::fnGetAttackCastDelay GetAttackCastDelay;
	Typedefs::fnGetAttackDelay GetAttackDelay;
	Typedefs::fnGetPing GetPing;
	Typedefs::fnWorldToScreen WorldToScreen;
	Typedefs::fnIsTargetable IsTargetable;
	//Typedefs::fnDrawCircle DrawCircle;
};

extern CFunctions Functions;