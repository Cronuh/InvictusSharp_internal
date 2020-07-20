#pragma once

class CSettings
{
public:
	bool DebugMode = false;

	bool drawAttackRange = false;
	bool drawLasthitTarget = false;
	bool drawOrbTarget = false;
	bool drawSpellColdowns = false;
	bool drawGankTracker = false;
	bool drawWardTracker = false;
	bool DrawLastTargetPos = false;
	bool DrawEvade = false;

	float windupTime = 0.f;

	
}; extern CSettings settings;

