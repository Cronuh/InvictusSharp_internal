#include "OrbwalkerEngine.h"
#include "GameFunctions.h"


int OrbwalkerEngine::m_LastAATick = 0;


float OrbwalkerEngine::GetGameTime()
{
	return *(float*)((DWORD)GetModuleHandleA(NULL) + oGameTime);
}

int OrbwalkerEngine::GetGameTimeTickCount()
{
	return (int)(GetGameTime() * 1000);
}

int OrbwalkerEngine::GetPing()
{
	static DWORD Base = (DWORD)GetModuleHandle(NULL);
	return Functions.GetPing(*(void**)(Base + oNetClient));	
}

bool OrbwalkerEngine::IsLeagueInForeground()
{
	TCHAR title[500];
	GetWindowText(GetForegroundWindow(), title, 500);
	return title == L"League of Legends (TM) Client";
}


bool OrbwalkerEngine::CanAttack()
{
	return GetGameTimeTickCount() + GetPing() / 100 >= OrbwalkerEngine::m_LastAATick + Functions.GetAttackDelay(CObject::GetLocalObject()) * 1000;
}
bool OrbwalkerEngine::CanMove(float extraWindUp)
{
	return GetGameTimeTickCount() + GetPing() / 100 >= OrbwalkerEngine::m_LastAATick + Functions.GetAttackCastDelay(CObject::GetLocalObject()) * 1000 + extraWindUp;

	//return GetGameTimeTickCount() + GetPing() / 100 >= OrbwalkerEngine::m_LastAATick + Functions.GetAttackCastDelay(CObject::GetLocalObject()) * 1000 + extraWindUp;
}



