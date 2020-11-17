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

	std::ifstream inSettings(pSettings);
	json j_object = json::parse(inSettings, nullptr, false);

	if (j_object.contains("ShowMenu"))
		Settings::ShowMenu = j_object["ShowMenu"].get<bool>();
	if (j_object.contains("ShowMenu_Hotkey"))
		Settings::Hotkeys[0].functionKeys = j_object["ShowMenu_Hotkey"].get<uint32_t>();

	if (j_object.contains("ShowRadar"))
		Settings::ShowRadar = j_object["ShowRadar"].get<bool>();
	if (j_object.contains("ShowRadar_Hotkey"))
		Settings::Hotkeys[1].functionKeys = j_object["ShowRadar_Hotkey"].get<uint32_t>();
	if (j_object.contains("ShowRadar_DeadBodies"))
		Settings::ShowRadar_DeadBodies = j_object["ShowRadar_DeadBodies"].get<bool>();
	if (j_object.contains("ShowRadar_Ghosts"))
		Settings::ShowRadar_Ghosts = j_object["ShowRadar_Ghosts"].get<bool>();
	if (j_object.contains("ShowRadar_RightClick_Teleport"))
		Settings::ShowRadar_RightClick_Teleport = j_object["ShowRadar_RightClick_Teleport"].get<bool>();

	if (j_object.contains("RepairSabotage_Hotkey"))
		Settings::Hotkeys[2].functionKeys = j_object["RepairSabotage_Hotkey"].get<uint32_t>();

	if (j_object.contains("MaxVision"))
		Settings::MaxVision = j_object["MaxVision"].get<bool>();
	if (j_object.contains("UnlockVents"))
		Settings::UnlockVents = j_object["UnlockVents"].get<bool>();
	if (j_object.contains("RevealImpostors"))
		Settings::RevealImpostors = j_object["RevealImpostors"].get<bool>();
	if (j_object.contains("ChatAlwaysActive"))
		Settings::ChatAlwaysActive = j_object["ChatAlwaysActive"].get<bool>();
	if (j_object.contains("ReadGhostMessages"))
		Settings::ReadGhostMessages = j_object["ReadGhostMessages"].get<bool>();
}

void Settings::Save() {
	json j_object = json{
		{"ShowMenu", Settings::ShowMenu},
		{"ShowMenu_Hotkey", Settings::Hotkeys[0].functionKeys},

		{"ShowRadar", Settings::ShowRadar},
		{"ShowRadar_Hotkey", Settings::Hotkeys[1].functionKeys},
		{"ShowRadar_DeadBodies", Settings::ShowRadar_DeadBodies},
		{"ShowRadar_Ghosts", Settings::ShowRadar_Ghosts},
		{"ShowRadar_RightClick_Teleport", Settings::ShowRadar_RightClick_Teleport},

		{"RepairSabotage_Hotkey", Settings::Hotkeys[2].functionKeys},

		{"MaxVision", Settings::MaxVision},
		{"UnlockVents", Settings::UnlockVents},
		{"RevealImpostors", Settings::RevealImpostors},
		{"ChatAlwaysActive", Settings::ChatAlwaysActive},
		{"ReadGhostMessages", Settings::ReadGhostMessages}
	};

	std::ofstream outSettings(pSettings);
	outSettings << std::setw(4) << j_object << std::endl;
}