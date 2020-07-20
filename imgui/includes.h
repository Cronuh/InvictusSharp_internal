#pragma once
#include <Windows.h>
#include <d3d9.h>
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\d3dx9.h"
#include "C:\Users\Shadow\source\repos\InvictusSharp\InvictusSharp\minhook\include\MinHook.h"
#include "C:\Users\Shadow\source\repos\InvictusSharp\InvictusSharp\imgui/imgui.h"
#include "C:\Users\Shadow\source\repos\InvictusSharp\InvictusSharp\imgui/imgui_impl_win32.h"
#include "C:\Users\Shadow\source\repos\InvictusSharp\InvictusSharp\imgui/imgui_impl_dx9.h"

typedef uintptr_t PTR;
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);