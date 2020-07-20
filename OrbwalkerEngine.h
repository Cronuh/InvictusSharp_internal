#pragma once
#include <Windows.h>
#include "CObjectManager.h"
#include <vector>
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\d3dx9math.h"
class OrbwalkerEngine
{
public:

	static float GetGameTime();
	static int GetGameTimeTickCount();
	static int GetPing();

	static bool CanAttack();
	static bool CanMove(float extraWindup);

	static bool IsLeagueInForeground();
	static int m_LastAATick;
	static int m_TargetSelectorMode;

private:


	static void pushTurrets();
};