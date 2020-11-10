#pragma once
#include "il2cpp-appdata.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d11.h>
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "kiero/kiero.h"
#include "detours/detours.h"
#include "state.hpp"
#include "menu.hpp"
#include "radar.hpp"

typedef HRESULT(__stdcall* D3D_PRESENT_FUNCTION)(IDXGISwapChain*, UINT, UINT);

struct MapTexture {
	char name[32];
	ID3D11ShaderResourceView* buffer;
	int width;
	int height;
	float x_offset;
	float y_offset;
	float scale;
};

extern std::vector<MapTexture> maps;

void DetourInitilization();

bool dAutoOpenDoor_DoUpdate(AutoOpenDoor* __this, float dt, MethodInfo* method);
bool dStatsManager_get_AmBanned(StatsManager* __this, MethodInfo* method);
float dShipStatus_CalculateLightRadius(ShipStatus* __this, GameData_PlayerInfo* player, MethodInfo* method);
float dStatsManager_get_BanPoints(StatsManager* __this, MethodInfo* method);
float dVent_CanUse(Vent* __this, GameData_PlayerInfo* pc, bool* canUse, bool* couldUse, MethodInfo* method);
HatBehaviour__Array* dHatManager_GetUnlockedHats(HatManager* __this, MethodInfo* method);
int32_t dStatsManager_get_BanMinutesLeft(StatsManager* __this, MethodInfo* method);
PetBehaviour__Array* dHatManager_GetUnlockedPets(HatManager* __this, MethodInfo* method);
SkinData__Array* dHatManager_GetUnlockedSkins(HatManager* __this, MethodInfo* method);
void dAmongUsClient_OnStartGame(AmongUsClient* __this, MethodInfo* method);
void dChatBubble_SetName(ChatBubble* __this, String* playerName, bool isDead, bool voted, Color color, MethodInfo* method);
void dChatController_AddChat(ChatController* __this, PlayerControl* sourcePlayer, String* chatText, MethodInfo* method);
void dChatController_SetVisible(ChatController* __this, bool visible, MethodInfo* method);
void dElectricTask_FixedUpdate(ElectricTask* __this, MethodInfo* method);
void dHqHudOverrideTask_FixedUpdate(HqHudOverrideTask* __this, MethodInfo* method);
void dHudManager_ShowMap(HudManager* __this, Action_1_MapBehaviour_* mapAction, MethodInfo* method);
void dHudOverrideTask_FixedUpdate(HudOverrideTask* __this, MethodInfo* method);
void dKeyboardJoystick_Update(KeyboardJoystick* __this, MethodInfo* method);
void dMeetingHud_Update(MeetingHud* __this, MethodInfo* method);
void dNoOxyTask_FixedUpdate(NoOxyTask* __this, MethodInfo* method);
void dPlainDoor_SetDoorway(PlainDoor* __this, bool open, MethodInfo* method);
void dPlayerControl_FixedUpdate(PlayerControl* __this, MethodInfo* method);
void dReactorTask_FixedUpdate(ReactorTask* __this, MethodInfo* method);
void dSceneManager_Internal_ActiveSceneChanged(Scene previousActiveScene, Scene newActiveScene, MethodInfo* method);
void dShipStatus_OnEnable(ShipStatus* __this, MethodInfo* method);
