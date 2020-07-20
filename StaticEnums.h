#pragma once

	enum class EGameObjectTeam
	{
		eUnknown = 0,
		eOrder = 100,
		eChaos = 200,
		eNeutral = 300
	};
	 
	enum class ESpellSlot
	{
		eQ = 0,
		eW = 1,
		eE = 2,
		eR = 3,
		eD = 4,
		eF = 5,
		eItem1 = 6,
		eItem2 = 7,
		eItem3 = 8,
		eItem4 = 9,
		eItem5 = 10,
		eItem6 = 11,
		eTrinket = 12,
		eRecall = 13
	};


	enum class ESpellState
	{
		eReady = 0,
		eNotAvailable = 4,
		eSurpressed = 8,
		eNotLearned = 12,
		eProcessing = 24,
		eCooldown = 32,
		eNoMana = 64,
		eUnknown
	};
