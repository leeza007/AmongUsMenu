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

using namespace app;
using json = nlohmann::json;

class Settings
{
private:
    inline bool Exists(const std::string& name);

public:
    bool ImGuiInitialized = false;
    bool ShowMenu = false;

    std::string CurrentScene;

    bool MaxVision = false;
    bool PlayerSpeed_Enabled = false;
    float PlayerSpeed = 1.f;
    bool UnlockVents = false;

    bool RevealImpostors = false;
    bool NoKillTimer = false;
    bool KillDistance_Enabled = false;
    int KillDistance = 0;

    bool NoClip = false;

    uint8_t selectedPlayerId = -1;
    std::queue<RPCInterface*> rpcQueue;

    bool ShowRadar = false;
    bool ShowRadar_DeadBodies = false;
    bool ShowRadar_Ghosts = false;
    bool ShowRadar_RightClick_Teleport = false;

    bool ChatAlwaysActive = false;
    bool ReadGhostMessages = false;

    bool AutoRepairLights = false;
    bool AutoRepairReactor = false;
    bool AutoRepairOxygen = false;
    bool AutoRepairComms = false;

    SystemTypes__Enum selectedDoor;
    std::vector<SystemTypes__Enum> mapDoors;
    std::vector<SystemTypes__Enum> pinnedDoors;

    void Load();
    void Save();
};

extern Settings State;