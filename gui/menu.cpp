#include "menu.hpp"

using namespace app;

namespace Menu {
	const std::vector<const char*> KILL_DISTANCE = { "Short", "Medium", "Long" };

	bool SteppedSliderFloat(const char* label, float* v, float v_min, float v_max, float v_step, const char* format = "%.3f", ImGuiSliderFlags flags = 0) {
		char text_buf[64] = {};
		ImFormatString(text_buf, IM_ARRAYSIZE(text_buf), format, *v);

		const int stepCount = int((v_max - v_min) / v_step);
		int v_i = int((*v - v_min) / v_step);
		const bool valueChanged = ImGui::SliderInt(label, &v_i, 0, stepCount, text_buf);

		*v = v_min + float(v_i) * v_step;
		return valueChanged;
	}

	void Init() {
		ImVec2 winpos = ImGui::GetWindowPos();
		ImGui::SetNextWindowSize(ImVec2(400, 250), ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(1.F);
	}

	bool init = false;
	void Render() {
		if (!init)
			Menu::Init();

		ImGui::Begin("AmongUsMenu", &State.ShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::BeginTabBar("AmongUs#TopBar", ImGuiTabBarFlags_NoTabListScrollingButtons);

		if (ImGui::BeginTabItem("Game")) {
			ImGui::Checkbox("Max Vision", &State.MaxVision);
			if (SteppedSliderFloat("Player Speed", &State.PlayerSpeed, 0.5f, 3.f, 0.25f, "%.2fx", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput)) {
				State.PlayerSpeed_Enabled = true;
			}
			ImGuiStyle& style = ImGui::GetStyle();
			float w = ImGui::CalcItemWidth();
			float spacing = style.ItemInnerSpacing.x;
			float button_sz = ImGui::GetFrameHeight();
			ImGui::PushItemWidth(w - spacing * 2.0f - button_sz * 2.0f);
			if (ImGui::BeginCombo("##killDistance", KILL_DISTANCE.at(State.KillDistance), ImGuiComboFlags_NoArrowButton)) {
				for (int i = 0; i < KILL_DISTANCE.size(); i++) {
					bool is_selected = (State.KillDistance == i);
					if (ImGui::Selectable(KILL_DISTANCE.at(i), is_selected))
						State.KillDistance = i;
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			ImGui::SameLine(0, spacing);
			if (ImGui::ArrowButton("##killDistanceLeft", ImGuiDir_Left)) {
				State.KillDistance--;
				if (State.KillDistance < 0) State.KillDistance = 0;
			}
			ImGui::SameLine(0, spacing);
			if (ImGui::ArrowButton("##killDistanceRight", ImGuiDir_Right)) {
				State.KillDistance++;
				if (State.KillDistance > (KILL_DISTANCE.size() - 1)) State.KillDistance = (KILL_DISTANCE.size() - 1);
			}
			ImGui::SameLine(0, style.ItemInnerSpacing.x);
			ImGui::Text("Kill Distance");
			ImGui::Checkbox("No Kill Timer", &State.NoKillTimer);
			if (ImGui::Checkbox("NoClip", &State.NoClip)) {
				if (!State.NoClip && IsInGame())
					GameObject_set_layer(Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), 8, NULL);
			}
			ImGui::Checkbox("Reveal Impostors", &State.RevealImpostors);
			ImGui::Checkbox("Unlock Vents", &State.UnlockVents);
			ImGui::Checkbox("Chat Always Active", &State.ChatAlwaysActive);
			ImGui::Checkbox("Read Messages by Ghosts", &State.ReadGhostMessages);

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Radar")) {
			ImGui::Checkbox("Show Radar", &State.ShowRadar);
			ImGui::Checkbox("Show Dead Bodies", &State.ShowRadar_DeadBodies);
			ImGui::Checkbox("Show Ghosts", &State.ShowRadar_Ghosts);
			ImGui::Checkbox("Right Click to Teleport", &State.ShowRadar_RightClick_Teleport);
			ImGui::EndTabItem();
		}

		if (IsInGame()) {
			if (ImGui::BeginTabItem("Players")) {
				ImGui::BeginChild("players#list", ImVec2(200, 0), true);
				ImGui::ListBoxHeader("", ImVec2(200, 150));
				for (auto playerData : GetAllPlayerData()) {
					if (playerData->fields.Disconnected) continue;

					std::string playerName = convert_from_string(playerData->fields.PlayerName);
					ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
					if (ImGui::Selectable(std::string("##" + playerName).c_str(), State.selectedPlayerId == playerData->fields.PlayerId)) {
						State.selectedPlayerId = playerData->fields.PlayerId;
					}
					ImGui::SameLine();
					ImGui::ColorButton(std::string("##" + playerName + "_ColorButton").c_str(), AmongUsColorToImVec4(GetPlayerColor(playerData->fields.ColorId)), ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip);
					ImGui::SameLine();
					ImGui::PopStyleVar(2);
					ImGui::Dummy(ImVec2(0, 0));
					ImGui::SameLine();

					ImVec4 nameColor;
					if (State.RevealImpostors && playerData->fields.IsImpostor)
						nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->ImpostorRed);
					else
						nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->White);

					if(playerData->fields.IsDead) nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->DisabledGrey);

					ImGui::TextColored(nameColor, playerName.c_str());
				}
				ImGui::ListBoxFooter();
				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("players#options", ImVec2(200, 0));

				GameData_PlayerInfo* targetedPlayer = GetPlayerDataById(State.selectedPlayerId);
				if (targetedPlayer != NULL && !targetedPlayer->fields.Disconnected) {
					GameData_PlayerInfo* localPlayer = GetPlayerData((*Game::pLocalPlayer));
					if (localPlayer->fields.IsImpostor) {
						if (ImGui::Button("Murder")) {
							State.rpcQueue.push(new MurderRPC(localPlayer->fields.PlayerId, targetedPlayer->fields.PlayerId));
						}
					}

					if (ImGui::Button("Teleport To")) {
						State.rpcQueue.push(new TeleportRPC(localPlayer->fields.PlayerId, PlayerControl_GetTruePosition(targetedPlayer->fields._object, NULL)));
					}
				}

				ImGui::EndChild();

				ImGui::EndTabItem();
			}

			if (GetPlayerData(*Game::pLocalPlayer)->fields.Tasks != NULL && !GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor) {
				if (ImGui::BeginTabItem("Tasks")) {
					auto tasks = GetPlayerTasks(*Game::pLocalPlayer);

					if (tasks.size() > 0 && ImGui::Button("Complete All Tasks")) {
						for (auto task : tasks) {
							if(!NormalPlayerTask_get_IsComplete(task, NULL))
								CompleteTask(task);
						}
					}

					ImGui::Spacing();

					for (auto task : tasks) {
						if (ImGui::Button(("Complete##Button" + std::to_string(task->fields._._Id)).c_str()) && !NormalPlayerTask_get_IsComplete(task, NULL)) {
							CompleteTask(task);
						}

						ImGui::SameLine();

						ImGui::TextColored(NormalPlayerTask_get_IsComplete(task, NULL)
							? ImVec4(0.0F, 1.0F, 0.0F, 1.0F)
							: AmongUsColorToImVec4(app::Palette__TypeInfo->static_fields->White)
							, TranslateTaskTypes(task->fields._.TaskType));
					}

					ImGui::EndTabItem();
				}
			}

			if (ImGui::BeginTabItem("Sabotage")) {
				ImGui::BeginChild("system#repair", ImVec2(200, 0));
				ImGui::Text("Auto-Repair");
				ImGui::Checkbox("Lights##repair", &State.AutoRepairLights);
				ImGui::Checkbox("Reactor##repair", &State.AutoRepairReactor);
				ImGui::Checkbox("Oxygen##repair", &State.AutoRepairOxygen);
				ImGui::Checkbox("Comms##repair", &State.AutoRepairComms);
				ImGui::EndChild();

				ImGui::SameLine();
				ImGui::BeginChild("system#sabotage");
				ImGui::Text("Sabotage");
				if (ImGui::Button("Lights##sabotage")) {
					if (!GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor) State.AutoRepairLights = false;
					State.rpcQueue.push(new SabotageRPC(SystemTypes__Enum_Electrical));
				}
				if (ImGui::Button("Reactor##sabotage")) {
					if (!GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor) State.AutoRepairReactor = false;
					if ((*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Ship || (*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Hq)
						State.rpcQueue.push(new SabotageRPC(SystemTypes__Enum_Reactor));

					if ((*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Pb)
						State.rpcQueue.push(new SabotageRPC(SystemTypes__Enum_Laboratory));
				}
				if (ImGui::Button("Oxygen##sabotage")) {
					if (!GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor) State.AutoRepairOxygen = false;
					State.rpcQueue.push(new SabotageRPC(SystemTypes__Enum_LifeSupp));
				}
				if (ImGui::Button("Comms##sabotage")) {
					if (!GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor) State.AutoRepairComms = false;
					State.rpcQueue.push(new SabotageRPC(SystemTypes__Enum_Comms));
				}
				ImGui::EndChild();
				ImGui::EndTabItem();
			}

			if (!State.mapDoors.empty()) {
				if (ImGui::BeginTabItem("Doors")) {
					ImGui::BeginChild("doors#list", ImVec2(200, 0), true);
					ImGui::ListBoxHeader("", ImVec2(200, 150));
					for (size_t i = 0; i < State.mapDoors.size(); i++) {
						auto systemType = State.mapDoors[i];
						if (ImGui::Selectable(TranslateSystemTypes(systemType), State.selectedDoor == systemType))
							State.selectedDoor = systemType;
					}
					ImGui::ListBoxFooter();
					ImGui::EndChild();

					ImGui::SameLine();
					ImGui::BeginChild("doors#options", ImVec2(200, 0));
					if (State.selectedDoor != SystemTypes__Enum_Hallway) {
						if (ImGui::Button("Close Door")) {
							app::ShipStatus_RpcCloseDoorsOfType(*Game::pShipStatus, State.selectedDoor, NULL);
						}

						if (std::find(State.pinnedDoors.begin(), State.pinnedDoors.end(), State.selectedDoor) == State.pinnedDoors.end()) {
							if (ImGui::Button("Pin Door")) {
								app::ShipStatus_RpcCloseDoorsOfType(*Game::pShipStatus, State.selectedDoor, NULL);
								State.pinnedDoors.push_back(State.selectedDoor);
							}
						}
						else {
							if (ImGui::Button("Unpin Door")) {
								State.pinnedDoors.erase(std::remove(State.pinnedDoors.begin(), State.pinnedDoors.end(), State.selectedDoor), State.pinnedDoors.end());
							}
						}
					}
					ImGui::EndChild();
					ImGui::EndTabItem();
				}
			}
		}
		ImGui::EndTabBar();

		ImGui::End();
	}

	void UpdateModifiers() {
		if (State.PlayerSpeed_Enabled) (*Game::pGameOptionsData)->fields.PlayerSpeedMod = State.PlayerSpeed;
		if (State.KillDistance_Enabled) (*Game::pGameOptionsData)->fields.KillDistance = State.KillDistance;
		if (State.NoKillTimer && (*Game::pGameOptionsData)->fields.KillCooldown > 0.1F)
			(*Game::pGameOptionsData)->fields.KillCooldown = 0.1F;
		if (State.NoClip)
			GameObject_set_layer(Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), 14, NULL);
	}

	void ResetModifiers() {
		State.PlayerSpeed_Enabled = false;
		State.KillDistance_Enabled = false;

		State.selectedPlayerId = 255;

		State.PlayerSpeed = (*Game::pGameOptionsData)->fields.PlayerSpeedMod;
		State.KillDistance = (*Game::pGameOptionsData)->fields.KillDistance;
	}
}