#include "Orbwalker.h"
#include "CObject.h"
#include "TargetSelector.h"
#include "OrbwalkerEngine.h"
#include "GameFunctions.h"
#include <ctime>
#include "chrono"
#include "settings.h"
#include "Activator.hpp"

clock_t lastmove = NULL;
clock_t lastMouseMove = NULL;


void IssueClick()
{
	int delay = rand() % 30 + 44;
	if (lastmove == NULL || clock() - lastmove > delay)
	{
		lastmove = clock();
		INPUT    Input = { 0 };

		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		::SendInput(1, &Input, sizeof(INPUT));
		::ZeroMemory(&Input, sizeof(INPUT));
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		::SendInput(1, &Input, sizeof(INPUT));
	}
}

static void ResetMouse(int x, int y)
{
	//RESET MOUSE
	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
	double fx = x * (65535.0f / fScreenWidth);
	double fy = y * (65535.0f / fScreenHeight);
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = fx;
	Input.mi.dy = fy;
	SendInput(1, &Input, sizeof(INPUT));
	::ZeroMemory(&Input, sizeof(INPUT));
	ZeroMemory(&x, sizeof(int));
	ZeroMemory(&y, sizeof(int));
}

void IssueAttack(int targetX, int targetY)
{

	POINT mousePos;
	GetCursorPos(&mousePos);
	//calc resolution to get orper coordinates
	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
	double fx = targetX * (65535.0f / fScreenWidth);
	double fy = targetY * (65535.0f / fScreenHeight);
	//send input
	INPUT  Input = { 0 }; //input buffer
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = fx;
	Input.mi.dy = fy;
	SendInput(1, &Input, sizeof(INPUT));
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	::ZeroMemory(&Input, sizeof(INPUT));
	ZeroMemory(&targetX, sizeof(int));
	ZeroMemory(&targetY, sizeof(int));
	Sleep(25);
	ResetMouse(mousePos.x, mousePos.y);

}

CObject* CTargetSelector::target = NULL;

int Orbwalker::targetX = 0;
int Orbwalker::targetY = 0;
void __stdcall Orbwalker::Orbwalk()
{
	while (true)
	{



		if (GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(0x58) || GetAsyncKeyState(0x56))
		{

			if (OrbwalkerEngine::CanAttack() && CTargetSelector::target != NULL && Orbwalker::targetX != 0 && Orbwalker::targetY != 0 && CTargetSelector::target->IsValidTarget())
			{
				IssueAttack(Orbwalker::targetX, Orbwalker::targetY);
				OrbwalkerEngine::m_LastAATick = OrbwalkerEngine::GetGameTimeTickCount() - OrbwalkerEngine::GetPing() / 100;

			}
			else if (OrbwalkerEngine::CanMove(settings.windupTime))
			{

				IssueClick();
			}
		}







		//if lasthit key pressed (X)
		/*
		if (GetAsyncKeyState(0x58))
		{
			TS::target = TS::GetLasthitTarget();
			if (OrbwalkerEngine::CanAttack() && TS::target != NULL && targetX != 0 && targetY != 0)
			{
				IssueAttack(targetX, targetY);
				OrbwalkerEngine::m_LastAATick = OrbwalkerEngine::GetGameTimeTickCount() - OrbwalkerEngine::GetPing() / 100;

			}
			else if (OrbwalkerEngine::CanMove(90))
			{
				IssueClick();
			}
		}
		*/
	}
	
}













