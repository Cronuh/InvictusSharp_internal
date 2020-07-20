#pragma once
#include "settings.h"
#include "Visuals.h"

static void DrawIfActivated()
{
	if (settings.DebugMode)
		CVisuals::DebugPrint();

	if (settings.drawAttackRange)
		CVisuals::DrawAttackRange();

	if (settings.drawWardTracker)
		CVisuals::DrawWardTracker();

	if (settings.drawOrbTarget)
		CVisuals::DrawOrbTarget();

	if (settings.drawSpellColdowns)
		CVisuals::DrawEnemyCooldowns();

	if (settings.drawLasthitTarget)
		CVisuals::DrawLasthitTarget();

	if (settings.drawGankTracker)
		CVisuals::DrawGankTracker();

	if (settings.DrawLastTargetPos)
		CVisuals::DrawLastPosition();

	if (settings.DrawEvade)
		CVisuals::DrawEvade();
}