#pragma once
#include "StaticEnums.h"
#include <Windows.h>
#include "CObject.h"

class CActivator
{
public:

	static bool IsItem(char* itemName)
	{
		for (size_t i = 0; i < 6; i++)
		{
			if (CObject::GetLocalObject()->GetSpellBook()->GetSpellSlotByID(i)->GetSpellInfo()->GetSpellData()->GetSpellName() == itemName)
				return true;
		}
	}

	static bool UseItemOnTarget(int targetX, int targetY, ESpellSlot spellSlot)
	{
		if (CObject::GetLocalObject()->IsSpellReady((int)spellSlot))
		{
			POINT mousePos;
			GetCursorPos(&mousePos);

			MoveMouseToTarget(targetX, targetY);
			UseItem(spellSlot);
			Sleep(15);
			ResetMouse(mousePos.x, mousePos.y);
			return true;
		}
		return false;
	}

	static bool Item1_Ready()
	{
		return CObject::GetLocalObject()->IsSpellReady(6);
	}
	
	static bool Item2_Ready()
	{
		return CObject::GetLocalObject()->IsSpellReady(7);
	}

	static bool Item3_Ready()
	{
		return CObject::GetLocalObject()->IsSpellReady(8);
	}

	static bool Item4_Ready()
	{
		return CObject::GetLocalObject()->IsSpellReady(9);
	}

	static bool Item5_Ready()
	{
		return CObject::GetLocalObject()->IsSpellReady(10);
	}

	static bool Item6_Ready()
	{
		return CObject::GetLocalObject()->IsSpellReady(11);
	}

private:
	static void UseItem(ESpellSlot spellSlot)
	{
		INPUT input;
		WORD vkey = NULL;
		switch ((int)spellSlot)
		{
		case 0:
			vkey = 0x51;
			break;
		case 1:
			vkey = 0x57;
			break;
		case 2:
			vkey = 0x54;
			break;
		case 3:
			vkey = 0x52;
			break;
		case 4:
			vkey = 0x44;
			break;
		case 5:
			vkey = 0x46;
			break;
		case 13:
			vkey = 0x42;
			break;
		}
		input.type = INPUT_KEYBOARD;
		input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
		input.ki.time = 0;
		input.ki.dwExtraInfo = 0;
		input.ki.wVk = vkey;
		input.ki.dwFlags = 0;
		SendInput(1, &input, sizeof(INPUT));

		input.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(INPUT));
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

	static void MoveMouseToTarget(int targetX, int targetY)
	{
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
		ZeroMemory(&targetX, sizeof(int));
		ZeroMemory(&targetY, sizeof(int));
		Sleep(50);
	}

};


