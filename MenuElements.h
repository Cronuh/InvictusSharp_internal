#pragma once
#include "imgui/imgui.h"
#include "OrbwalkerEngine.h"

class CMenu
{
public:

	static void ShowTargetSelectorModeMenu()
	{
		ImGui::NewLine();

		const char* TSCombo[] =
		{
		"ClosestTarget",
		"LowestHP"
		};


		if (ImGui::BeginCombo("##TsCombo", TSCombo[OrbwalkerEngine::m_TargetSelectorMode]))
		{
			static const char* current_item = NULL;
			for (int n = 0; n < IM_ARRAYSIZE(TSCombo); n++)
			{
				bool is_selected = (OrbwalkerEngine::m_TargetSelectorMode == n);
				if (ImGui::Selectable(TSCombo[n], is_selected))
					OrbwalkerEngine::m_TargetSelectorMode = n;
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
	}
	
	static void ShowOrbwalkerMenu()
	{
		ImGui::NewLine();

		ImGui::SliderFloat("Windup", &settings.windupTime, 0.f, 90.f, "%.2f", 0.01f);

		ImGui::NewLine();
		ImGui::LabelText("##OrbwalkerKeys", "Orbwalker Keys");
		ImGui::LabelText("##LasthitKey", "LastHit: X");
		ImGui::LabelText("##WaveclearJungleclear", "Waveclear/Jungleclear: V");
		ImGui::LabelText("##Orbwalk/Harass", "Orbwalk/Harass: Spacebar");
	}

	static void ShowDrawingsMenu()
	{
		ImGui::NewLine();

		ImGui::LabelText("##OrbDrawings", "Orbwalker Drawings");
		ImGui::Checkbox("AttackRange", &settings.drawAttackRange);
		ImGui::Checkbox("Lasthitable Minion", &settings.drawLasthitTarget);
		ImGui::Checkbox("Orbwalker Target", &settings.drawOrbTarget);
		ImGui::NewLine();

		ImGui::LabelText("##Helper", "Helper");
		ImGui::Checkbox("Cooldown Tracker", &settings.drawSpellColdowns);
		ImGui::Checkbox("Gank Tracker", &settings.drawGankTracker);
		ImGui::Checkbox("Ward Tracker", &settings.drawWardTracker);
		//ImGui::Checkbox("Evade Drawings", &settings.DrawEvade);
		ImGui::Checkbox("Last Position", &settings.DrawLastTargetPos);
	}

private:

};

