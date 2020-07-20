#pragma once
// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "GameFunctions.h"
#include "OrbwalkerEngine.h"
#include "DebugConsole.h"
//CFunctions Functions;
#include <Windows.h>
#include "Orbwalker.h"
#include "MinHook.h"
#include "C:\Users\Shadow\source\repos\InvictusSharp\InvictusSharp\imgui\includes.h"
#include "C:\Users\Shadow\source\repos\InvictusSharp\InvictusSharp\imgui\phook.h"
#pragma comment(lib,"libMinHook.x86.lib")
#include <iostream>
#include "TargetSelector.h"
#include <d3d9.h>

#include "settings.h"
#include "colors.h"
#include "Visuals.h"
#include "MenuElements.h"
#include "CheckSettings.h"


#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")


HWND window;
void* pDevice[119];
PTR EndSceneAddress;
EndScene oEndScene;
CSettings settings;
WNDPROC oWndProc;

int OrbwalkerEngine::m_TargetSelectorMode = 1;
void InitImGui(LPDIRECT3DDEVICE9 device)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange | ImGuiWindowFlags_NoBackground;
	io.WantCaptureMouse = false; //set flag to false to block mouseclicks when menu opened
	CVisuals::SetImguiStyle();
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);


}

bool initialized = false;
long __stdcall PHook::hkEndScene(LPDIRECT3DDEVICE9 device)
{


	if (!initialized)
	{
		InitImGui(device);
		initialized = true;
	}





	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	////MENU STUFF/////////////////////////////////////////////////////////////////////////////////

	ImGui::SetWindowSize(ImVec2(400, 300), 0);
	if (GetAsyncKeyState(VK_SHIFT))
	{
		ImGui::Begin("Invictus# Menu");

		//ImGui::Checkbox("Debug Mode", &settings.DebugMode);
		//ImGui::NewLine();
		if (ImGui::CollapsingHeader("TargetSelector"))
		{
			CMenu::ShowTargetSelectorModeMenu();
		}
		ImGui::NewLine();
		if (ImGui::CollapsingHeader("Orbwalker"))
		{
			CMenu::ShowOrbwalkerMenu();
		}
		ImGui::NewLine();
		if (ImGui::CollapsingHeader("Drawings"))
		{
			ImGui::LabelText("##InProgress", "In Progress");
			//CMenu::ShowDrawingsMenu();
		}
		ImGui::NewLine();


		ImGui::End();
	}

	////MENU STUFF END////////////////////////////////////////////////////////////////////////////


	CTargetSelector::SetTSTarget(); //sets the TS target
	DrawIfActivated();				// Draw if activated (checking settings here)

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());



	return oEndScene(device);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall PHook::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}



void __stdcall MainThread()
{
	while (OrbwalkerEngine::GetGameTime() <= 0.f || CObject::GetLocalObject() == NULL)
		Sleep(1);



	//Function declaration
	Functions.GetAttackCastDelay = (Typedefs::fnGetAttackCastDelay)((DWORD)GetModuleHandleA(NULL) + oGetAttackCastDelay);
	Functions.GetAttackDelay = (Typedefs::fnGetAttackDelay)((DWORD)GetModuleHandleA(NULL) + oGetAttackDelay);
	Functions.WorldToScreen = (Typedefs::fnWorldToScreen)((DWORD)GetModuleHandleA(NULL) + oWorldToScreen);
	//Functions.DrawCircle = (Typedefs::fnDrawCircle)((DWORD)GetModuleHandleA(NULL) + oDrawCircle);
	Functions.GetPing = (Typedefs::fnGetPing) ((DWORD)GetModuleHandleA(NULL) + oGetPing);
	Functions.IsTargetable = (Typedefs::fnIsTargetable) ((DWORD)GetModuleHandleA(NULL) + oIsTargetable);
}





















BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)PHook::Init, hMod, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Orbwalker::Orbwalk, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)PHook::Shutdown, hMod, 0, nullptr);
		break;
	}
	return TRUE;
}
