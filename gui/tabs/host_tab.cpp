#include "host_tab.h"

namespace HostTab {
	void Render() {
		if (IsHost() && IsInLobby()) {
			if (ImGui::BeginTabItem("Host")) {
				ImGui::Text("Select Impostors:");
				ImGui::BeginChild("host#list", ImVec2(200, 0), true);
				ImGui::ListBoxHeader("Choose Impostors", ImVec2(200, 150));
				for (auto playerData : GetAllPlayerData()) {
					if (playerData->fields.Disconnected) continue;

					std::string playerName = convert_from_string(playerData->fields.PlayerName);

					PlayerControl* playerCtrl = GetPlayerControlById(playerData->fields.PlayerId);

					bool impostor = std::find(State.impostors.begin(), State.impostors.end(), playerCtrl) != State.impostors.end();
					if (ImGui::Checkbox(std::string("##" + playerName + "_CheckBox").c_str(), &impostor)) {
						if (!(std::find(State.impostors.begin(), State.impostors.end(), playerCtrl) != State.impostors.end())) {
							bool set = false;

							for (int i = 0; i < (*Game::pGameOptionsData)->fields.NumImpostors; i++) {
								if (State.impostors[i] == nullptr) {
									State.impostors[i] = playerCtrl;
									set = true;
									break;
								}
							}

							if (!set) {
								if ((*Game::pGameOptionsData)->fields.NumImpostors > 2) {
									State.impostors[2] = State.impostors[1];
								}
								if ((*Game::pGameOptionsData)->fields.NumImpostors > 1) {
									State.impostors[1] = State.impostors[0];
								}
								State.impostors[0] = playerCtrl;
							}
						}
						else {
							for (int i = 0; i < (*Game::pGameOptionsData)->fields.NumImpostors; i++) {
								if (State.impostors[i] == playerCtrl) {
									State.impostors[i] = nullptr;
									break;
								}
							}
						}

					}
					ImGui::SameLine();
					ImGui::Dummy(ImVec2(0, 0));
					ImGui::SameLine();

					ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(playerData->fields.ColorId)),playerName.c_str());
				}
				ImGui::ListBoxFooter();
				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("host#actions", ImVec2(200, 0), true);
				/*if (ImGui::Button("Force Start Game")) {
					AmongUsClient_StartGame((*Game::pAmongUsClient), NULL);
				}*/
				int Map = (*Game::pGameOptionsData)->fields.MapId;
				if (CustomListBoxInt("Map", &Map, MAP_NAMES, 100)) {
					if (!IsInGame()) (*Game::pGameOptionsData)->fields.MapId = Map;
				}
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
		}
	}
}