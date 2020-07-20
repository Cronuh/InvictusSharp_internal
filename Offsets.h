#pragma once
#define TARGET_GAMEVERSION "Version 10.12.320.3039 [PUBLIC]"  // 

#define oRetnAddress 0xAFEF1

#define BASEADDRESS GetModuleHandle(NULL)
#define oGetAttackDelay 0x2B63B0	//8B 44 24 04 51 F3
#define oGetAttackCastDelay 0x2B62B0	//83 EC 0C 53 8B 5C 24 14 8B CB 56 57 8B 03 FF 90
#define oGetPing 0x342AC0	//E8 ? ? ? ? 8B 4F 2C 85 C9 0F
#define oDrawCircle 0x50D340	//E8 ? ? ? ? 83 C4 1C 8B 7C 24 28
#define oIsAlive 0x1B7F20	//56 8B F1 8B 06 8B 80 ? ? ? ? FF D0 84 C0 74 19
#define oIsInhib 0x1CB900	//E8 ? ? ? ? 83 C4 04 84 C0 74 38
#define oIsNexus 0x1CBA00	//E8 ? ? ? ? 57 88 44 24 20
#define oIsTurret 0x1CBC70	//E8 ? ? ? ? 83 C4 04 84 C0 74 09 5F
#define oIsMinion 0x1CBAC0	//E8 ? ? ? ? 83 C4 04 80 7F 26 06
#define oIsDragon 0x1883F0	//83 EC 10 A1 ? ? ? ? 33 C4 89 44 24 0C 56 81 C1 ? ? ? ?
#define oIsBaron 0x18A2F0	//E8 ? ? ? ? 84 C0 74 0A BB ? ? ? ?
#define oIsHero 0x1CBA80	//E8 ? ? ? ? 83 C4 04 84 C0 74 2B
#define oIsMissile 0x0	//E8 ? ? ? ? 83 C4 04 84 C0 74 1C FF
#define oIsTargetable 0x1EFBE0	//56 8B F1 E8 ? ? ? ? 84 C0 74 2E
#define oIssueOrder 0x18A3A0	//81 EC ? ? ? ? 56 57 8B F9 C7
#define oGetSpellState 0x50A410	//E8 ? ? ? ? 8B F8 8B CB 89
#define oCastSpell 0x0	//83 EC 38 56 8B 74 24 40
#define oGetBasicAttack 0x176A10	//53 8B D9 B8 ? ? ? ? 8B 93
#define oUpdateChargeableSpell 0x51AD20	//E8 ? ? ? ? 8B 43 24 8B 0D ? ? ? ?
#define oIsNotWall 0x0	//E8 ? ? ? ? 33 C9 83 C4 0C 84
#define oGameVersion 0x578620	//8B 44 24 04 BA ? ? ? ? 2B D0
#define oWorldToScreen 0x969AA0	//83 EC 10 56 E8 ? ? ? ? 8B 08
#define oGetFirstObject 0x2BB8E0	//8B 41 14 8B 51 18
#define oGetNextObject 0x2BC8B0	//E8 ? ? ? ? 8B F0 85 F6 75 E4
#define oChatClientPtr 0x18E38B	//8B 35 ? ? ? ? 52
#define oIsTroy 0xA8D8B0	//53 56 8B 74 24 10 57 8B 7C 24 10 8A 
#define oLocalPlayer 0x3501F1C	//A1 ? ? ? ? 85 C0 74 07 05 ? ? ? ? EB 02 33 C0 56
#define oObjManager 0x1C5F930	//8B 0D ? ? ? ? E8 ? ? ? ? FF 77
#define oGameTime 0x34FA7BC	//F3 0F 11 05 ? ? ? ? 8B 49
#define oHudInstance 0x1C5F96C	//8B 0D ? ? ? ? F3 0F 11 04 24 50 8B 49 0C E8 ? ? ? ? 83 C4 0C
#define oRenderer 0x35290FC	//8B 15 ? ? ? ? 83 EC 08 F3
#define oD3DRenderer 0x352BDCC	//A1 ? ? ? ? 89 54 24 18
#define oZoomClass 0x34FA744	//A3 ? ? ? ? 83 FA 10 72 32
#define oNetClient 0x3508F9C	//8B 0D ? ? ? ? 85 C9 74 07 8B 01 6A 01 FF 50 08 8B
#define oUnderMouseObject 0x34EF504	//8B 0D ? ? ? ? 89 0D ? ? ? ? 3B 44 24 30
#define oGameInfo 0x34FB6F4	//A1 ? ? ? ? 83 78 08 02 0F 94 C0
#define oViewMatrix 0x6C	//8D 4A ? 51 81 C2 ? ? ? ? 52
#define oProjection 0xAC	//8D 4A ? 51 81 C2 ? ? ? ? 52
#define oObjAttackRange 0x14A4	//D8 81 ? ? ? ? 8B 81 ? ? ? ?
#define oNetClient 0x3508F9C	//8B 0D ? ? ? ? 85 C9 74 07 8B 01 6A 01 FF 50 08 8B


//CObject
#define oObjIndex 0x20
#define oObjTeam 0x4C
#define oObjName 0x6C
#define oObjNetworkID 0xCC
#define oObjPos 0x1D8
#define oObjVisibility 0x39C
#define oObjHealth 0xFA8
#define oObjMaxHealth 0xFB8
#define oObjArmor 0x1464 // previous: 0x1468
#define oObjBaseAtk 0x145C // OR 0x1440
#define oObjBonusAtk 0x13BC // previous: 0x13B4
#define oObjMoveSpeed 0x147C
#define oObjAtkRange 0x14A4
#define oObjBuffMgr 0x2320
#define oObjSpellBook 0x2AD0
#define oObjChampionName 0x358C
#define oObjLevel 0x4EA4

//
#define objectArray 0x14