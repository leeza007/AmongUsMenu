#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "il2cpp-appdata.h"
#include <queue>
#include <optional>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "_rpc.h"
#include "json.hpp"
#include "imgui/imHotKey.h"

using namespace app;
using json = nlohmann::ordered_json;

class Settings
{
private:
    inline bool Exists(const std::string& name);

public:
    std::vector<ImHotKey::HotKey> Hotkeys = {
        {"Toggle Menu", "Toggles the visibility of AmongUsMenu", 0xFFFFFF53},
        {"Toggle Rader", "Toggles the visibility of AmongUsMenu's Rader", 0xFFFFFF52}
    };

    bool ImGuiInitialized = false;
    bool ShowMenu = false;

    std::string CurrentScene;

    bool MaxVision = false;
    float PrevPlayerSpeed = 1.f;
    float PlayerSpeed = 1.f;
    bool UnlockVents = false;

    bool RevealImpostors = false;
    int PrevKillDistance = 0;
    int KillDistance = 0;
    int PrevTaskBarUpdates = 0;
    int TaskBarUpdates = 0;
    bool NoKillCooldown = false;

    bool NoClip = false;

    int selectedPlayerId = -1;
    PlayerControl* selectedPlayer = NULL;
    std::queue<RPCInterface*> rpcQueue;

    bool ShowRadar = false;
    bool ShowRadar_DeadBodies = false;
    bool ShowRadar_Ghosts = false;
    bool ShowRadar_RightClick_Teleport = false;

    bool ChatAlwaysActive = false;
    bool ReadGhostMessages = false;

    SystemTypes__Enum selectedDoor;
    std::vector<SystemTypes__Enum> mapDoors;
    std::vector<SystemTypes__Enum> pinnedDoors;

    void Load();
    void Save();
};

extern Settings State;