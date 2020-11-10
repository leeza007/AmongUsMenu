#include "state.hpp"

Settings State;

const char* pSettings = "settings.json";

inline bool Settings::Exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

void Settings::Load() {
	if (!Settings::Exists(pSettings))
		return;

	std::ifstream i(pSettings);
	json j;
	i >> j;

	Settings::ShowMenu = j["ShowMenu"].get<bool>();

	Settings::MaxVision = j["MaxVision"].get<bool>();
	Settings::UnlockVents = j["UnlockVents"].get<bool>();

	Settings::RevealImpostors = j["RevealImpostors"].get<bool>();
	Settings::NoKillTimer = j["NoKillTimer"].get<bool>();

	Settings::NoClip = j["NoClip"].get<bool>();

	Settings::ShowRadar = j["ShowRadar"].get<bool>();
	Settings::ShowRadar_DeadBodies = j["ShowRadar_DeadBodies"].get<bool>();
	Settings::ShowRadar_Ghosts = j["ShowRadar_Ghosts"].get<bool>();
	Settings::ShowRadar_RightClick_Teleport = j["ShowRadar_RightClick_Teleport"].get<bool>();

	Settings::ChatAlwaysActive = j["ChatAlwaysActive"].get<bool>();
	Settings::ReadGhostMessages = j["ReadGhostMessages"].get<bool>();

	Settings::AutoRepairLights = j["AutoRepairLights"].get<bool>();
	Settings::AutoRepairReactor = j["AutoRepairReactor"].get<bool>();
	Settings::AutoRepairOxygen = j["AutoRepairOxygen"].get<bool>();
	Settings::AutoRepairComms = j["AutoRepairComms"].get<bool>();
}

void Settings::Save() {
	json j = json{
		{"ShowMenu", Settings::ShowMenu},

		{"MaxVision", Settings::MaxVision},
		{"UnlockVents", Settings::UnlockVents},

		{"RevealImpostors", Settings::RevealImpostors},
		{"NoKillTimer", Settings::NoKillTimer},

		{"NoClip", Settings::NoClip},

		{"ShowRadar", Settings::ShowRadar},
		{"ShowRadar_DeadBodies", Settings::ShowRadar_DeadBodies},
		{"ShowRadar_Ghosts", Settings::ShowRadar_Ghosts},
		{"ShowRadar_RightClick_Teleport", Settings::ShowRadar_RightClick_Teleport},

		{"ChatAlwaysActive", Settings::ChatAlwaysActive},
		{"ReadGhostMessages", Settings::ReadGhostMessages},

		{"AutoRepairLights", Settings::AutoRepairLights},
		{"AutoRepairReactor", Settings::AutoRepairReactor},
		{"AutoRepairOxygen", Settings::AutoRepairOxygen},
		{"AutoRepairComms", Settings::AutoRepairComms}
	};

	std::ofstream o(pSettings);
	o << std::setw(4) << j << std::endl;
}