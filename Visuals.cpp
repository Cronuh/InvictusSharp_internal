#include "Visuals.h"
#include "settings.h"
#include "TargetSelector.h"
#include <stdio.h>
#include "ImRender.hpp"
#include "SpellSlot.h"
#include <string>
#include "CObjectManager.h"
#include "bytes.h"
#include "ImRender.hpp"
#pragma warning(disable:4996)

void CVisuals::DebugPrint()
{
	CObject holzer;
	auto currentObj = holzer.GetFirstObject();

	while (currentObj)
	{
		Vector objPos;
		Functions.WorldToScreen(&currentObj->GetPos(), &objPos);

		if (currentObj->IsVisible() && currentObj->IsAlive() && !currentObj->IsInvalidObject() && currentObj->GetDistToMe() < 1500)
		{
			render.begin_draw();
			render.draw_text(objPos.X, objPos.Y + 15, currentObj->GetChampionName(), TRUE, ImColor(255, 255, 255, 255));
		}

		currentObj = holzer.GetNextObject(currentObj);
	}

	render.end_draw();
}

void CVisuals::DrawAttackRange()
{
	auto friendlyColor = createRGB(0, 255, 0);
	auto enemyColor = createRGB(255, 0, 0);
	auto localPlayerColor = createRGB(255, 255, 255);

	CObject holzer;
	auto currentObj = holzer.GetFirstObject();
	while (currentObj)
	{

		if (currentObj->IsHero())
		{
			if (currentObj->IsVisible() && currentObj->IsAlive() && !currentObj->IsInvalidObject())
			{
				if (currentObj == CObject::GetLocalObject())
					CTargetSelector::target = currentObj; //DELETE THIS JUST PLACEHOLDER!!!!
					//Functions.DrawCircle(&currentObj->GetPos(), currentObj->GetTrueAttackRange(), &localPlayerColor, 0, 0, 0, 255.f);

				//else if (currentObj != CObject::GetLocalObject() && currentObj->GetTeam() == CObject::GetLocalObject()->GetTeam())
				//	Functions.DrawCircle(&currentObj->GetPos(), currentObj->GetTrueAttackRange(), &friendlyColor, 0, 0, 0, 255.f);
				//else
					//Functions.DrawCircle(&currentObj->GetPos(), currentObj->GetTrueAttackRange(), &enemyColor, 0, 0, 0, 255.f);
			}

		}


		currentObj = holzer.GetNextObject(currentObj);
	}
}

void CVisuals::DrawOrbTarget()
{
	auto color = createRGB(0, 0, 255);
	if (CTargetSelector::target != NULL)
		CTargetSelector::target = NULL; //DELETE THIS!
		//Functions.DrawCircle(&CTargetSelector::target->GetPos(), CTargetSelector::target->GetBoundingRadius(), &color, 0, 0, 0, 255.f);
}

void CVisuals::DrawGankTracker()
{
	render.begin_draw();
	CObject holzer;
	auto currentObj = holzer.GetFirstObject();

	Vector enemyPos;
	Vector localPlayerPos;
	Functions.WorldToScreen(&CObject::GetLocalObject()->GetPos(), &localPlayerPos);
	while (currentObj)
	{


		if (currentObj->IsHero())
		{
			if (currentObj->isEnemyTo(CObject::GetLocalObject()) && currentObj->IsVisible() && currentObj->IsAlive())
			{
				if (currentObj->GetDistToMe() <= 1350)
				{
					Functions.WorldToScreen(&currentObj->GetPos(), &enemyPos);
					render.draw_line(localPlayerPos.X, localPlayerPos.Y, enemyPos.X, enemyPos.Y, ImColor(255, 0, 0, 255), 5.f);
				}

			}

		}


		currentObj = holzer.GetNextObject(currentObj);
	}
	render.end_draw();
}


void CVisuals::DrawLasthitTarget()
{
	auto greenColor = createRGB(0, 255, 0);
	auto redColor = createRGB(255, 0, 0);

	CObject holzer;
	auto currentObj = holzer.GetFirstObject();

	while (currentObj)
	{
		if (currentObj->IsMinion())
		{
			if (currentObj->IsValidTarget())
			{
				if (currentObj->IsLasthitable())
					CTargetSelector::target = currentObj; // JUST PLACEHOLDER!
					//Functions.DrawCircle(&currentObj->GetPos(), currentObj->GetBoundingRadius(), &greenColor, 0, 0, 0, 255.f);
			}

		}


		currentObj = holzer.GetNextObject(currentObj);
	}
}


void CVisuals::DrawEnemyCooldowns()
{

	Vector w2s_pos;


	auto greenColor = ImColor(0, 255, 0, 255);
	auto redColor = ImColor(255, 0, 0, 255);

	render.begin_draw();

	CObject holzer;
	auto currentObj = holzer.GetFirstObject();

	while (currentObj)
	{

		if (currentObj->IsHero())
		{
			if (currentObj->IsVisible() && currentObj->IsAlive() && !currentObj->IsInvalidObject())
			{
				Functions.WorldToScreen(&currentObj->GetPos(), &w2s_pos);

				if (currentObj->IsSpellReady((int)ESpellSlot::eQ))
					render.draw_text(w2s_pos.X, w2s_pos.Y + 15, "Q", true, greenColor);
				else
					render.draw_text(w2s_pos.X, w2s_pos.Y + 15, "Q", true, redColor);

				if (currentObj->IsSpellReady((int)ESpellSlot::eW))
					render.draw_text(w2s_pos.X + 15, w2s_pos.Y + 15, "W", true, greenColor);
				else
					render.draw_text(w2s_pos.X + 15, w2s_pos.Y + 15, "W", true, redColor);

				if (currentObj->IsSpellReady((int)ESpellSlot::eE))
					render.draw_text(w2s_pos.X + 30, w2s_pos.Y + 15, "E", true, greenColor);
				else
					render.draw_text(w2s_pos.X + 30, w2s_pos.Y + 15, "E", true, redColor);

				if (currentObj->IsSpellReady((int)ESpellSlot::eR))
					render.draw_text(w2s_pos.X + 45, w2s_pos.Y + 15, "R", true, greenColor);
				else
					render.draw_text(w2s_pos.X + 45, w2s_pos.Y + 15, "R", true, redColor);

				if (currentObj->IsSpellReady((int)ESpellSlot::eD))
					render.draw_text(w2s_pos.X, w2s_pos.Y + 30, "D", true, greenColor);
				else
					render.draw_text(w2s_pos.X, w2s_pos.Y + 30, "D", true, redColor);

				if (currentObj->IsSpellReady((int)ESpellSlot::eF))
					render.draw_text(w2s_pos.X + 15, w2s_pos.Y + 30, "F", true, greenColor);
				else
					render.draw_text(w2s_pos.X + 15, w2s_pos.Y + 30, "F", true, redColor);
			}

		}
		currentObj = holzer.GetNextObject(currentObj);
	}

	render.end_draw();

}


void CVisuals::DrawWardTracker()
{
	render.begin_draw();

	CObject holzer;
	auto currentObj = holzer.GetFirstObject();


	while (currentObj)
	{
		if (currentObj->IsMinion())
		{
			if (currentObj->IsWard() && currentObj->isEnemyTo(CObject::GetLocalObject()))
			{
				if (currentObj->IsAlive())
				{
					Vector w2s_pos;
					Functions.WorldToScreen(&currentObj->GetPos(), &w2s_pos);
					render.draw_circle(w2s_pos.X, w2s_pos.Y, currentObj->GetTrueAttackRange(), ImColor(255, 255, 255, 255), render.circle_normal);
				}
			}
		}
		currentObj = holzer.GetNextObject(currentObj);
	}
}

void CVisuals::DrawLastPosition()
{
	render.begin_draw();
	CObject holzer;
	auto currentObj = holzer.GetFirstObject();
	auto color = createRGB(255.f, 0.f, 0.f);

	Vector lastPos;
	Vector lastPos_w2s;
	while (currentObj)
	{
		if (currentObj->IsHero())
		{
			if (currentObj->isEnemyTo(CObject::GetLocalObject()) && currentObj->IsAlive())
				lastPos = currentObj->GetPos();


			if (!currentObj->IsVisible())
			{
				Functions.WorldToScreen(&lastPos, &lastPos_w2s);
				Vector w2s_pos;
				Functions.WorldToScreen(&currentObj->GetPos(), &w2s_pos);
				render.draw_circle(w2s_pos.X, w2s_pos.Y, currentObj->GetTrueAttackRange(), ImColor(255, 255, 255, 255), render.circle_normal);
				//<render.draw_text(lastPos_w2s.X, lastPos_w2s.Y, CHAMPNAMEHERE , true, ImColor(255, 255, 255, 255));
			}

		}

		currentObj = holzer.GetNextObject(currentObj);
	}
}

void CVisuals::DrawEvade()
{
	CObject holzer;
	auto currentObj = holzer.GetFirstObject();
	auto color = createRGB(255.f, 0.f, 0.f);

	while (currentObj)
	{
		if (currentObj->IsMissile())
		{
			short id = currentObj->GetSourceIndex();
			CObject* caster = CObjectManager::GetObjByIndex(id);

			if (caster->IsHero())
			{
				if (caster->IsAlive() && !caster->IsInvalidObject())
				{
					Vector startPos;
					Vector endPos;
					Functions.WorldToScreen(&currentObj->GetSpellInfo()->GetSpellData()->GetSpellCastPos(), &startPos);
					Functions.WorldToScreen(&currentObj->GetSpellInfo()->GetSpellData()->GetSpellEndPos(), &endPos);
					render.draw_line(startPos.X, startPos.Y, endPos.X, endPos.Y, ImColor(255, 255, 255, 255), 255.f);
				}
			}

		}


		currentObj = holzer.GetNextObject(currentObj);
	}
}












void CVisuals::SetImguiStyle()
{
	// cherry colors, 3 intensities
#define HI(v)   ImVec4(0.502f, 0.075f, 0.256f, v)
#define MED(v)  ImVec4(0.455f, 0.198f, 0.301f, v)
#define LOW(v)  ImVec4(0.232f, 0.201f, 0.271f, v)
// backgrounds (@todo: complete with BG_MED, BG_LOW)
#define BG(v)   ImVec4(0.200f, 0.220f, 0.270f, v)
// text
#define TEXT(v) ImVec4(0.860f, 0.930f, 0.890f, v)

	auto& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = TEXT(0.78f);
	style.Colors[ImGuiCol_TextDisabled] = TEXT(0.28f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	// style.Colors[ImGuiCol_ChildWindowBg] = BG(0.58f);
	style.Colors[ImGuiCol_PopupBg] = BG(0.9f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = BG(1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = MED(0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = MED(1.00f);
	style.Colors[ImGuiCol_TitleBg] = LOW(1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = HI(1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = BG(0.75f);
	style.Colors[ImGuiCol_MenuBarBg] = BG(0.47f);
	style.Colors[ImGuiCol_ScrollbarBg] = BG(1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = MED(1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
	style.Colors[ImGuiCol_ButtonHovered] = MED(0.86f);
	style.Colors[ImGuiCol_ButtonActive] = MED(1.00f);
	style.Colors[ImGuiCol_Header] = MED(0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = MED(0.86f);
	style.Colors[ImGuiCol_HeaderActive] = HI(1.00f);
	//  style.Colors[ImGuiCol_Column] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
   //   style.Colors[ImGuiCol_ColumnHovered] = MED(0.78f);
	 // style.Colors[ImGuiCol_ColumnActive] = MED(1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
	style.Colors[ImGuiCol_ResizeGripHovered] = MED(0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = MED(1.00f);
	style.Colors[ImGuiCol_PlotLines] = TEXT(0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = MED(1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = TEXT(0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = MED(0.43f);
	// [...]
	style.Colors[ImGuiCol_ModalWindowDarkening] = BG(0.73f);

	style.WindowPadding = ImVec2(6, 4);
	style.WindowRounding = 0.0f;
	style.FramePadding = ImVec2(5, 2);
	style.FrameRounding = 3.0f;
	style.ItemSpacing = ImVec2(7, 1);
	style.ItemInnerSpacing = ImVec2(1, 1);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 6.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 16.0f;
	style.GrabMinSize = 20.0f;
	style.GrabRounding = 2.0f;

	style.WindowTitleAlign.x = 0.50f;

	style.Colors[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
	style.FrameBorderSize = 0.0f;
	style.WindowBorderSize = 1.0f;
}