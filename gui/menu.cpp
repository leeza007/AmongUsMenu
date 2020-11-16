#include "menu.hpp"

using namespace app;

namespace Menu {
	const std::vector<const char*> KILL_DISTANCE = { "Short", "Medium", "Long" };
	const std::vector<const char*> TASKPROGRESSVISIBILITY = { "Always", "Meetings", "Never" };

	const char* strcat(std::initializer_list<const char*> strings) {
		std::string result;
		for (auto string : strings)
			result += string;
		return _strdup(result.c_str());
	}

	bool CustomListBoxInt(const char* label, int* value, const std::vector<const char*> list, ImGuiComboFlags flags) {
		ImGuiStyle& style = ImGui::GetStyle();
		float w = ImGui::CalcItemWidth();
		float spacing = style.ItemInnerSpacing.x;
		float button_sz = ImGui::GetFrameHeight();
		ImGui::PushItemWidth(w - spacing * 2.0f - button_sz * 2.0f);
		const bool response = ImGui::BeginCombo(strcat({ "##", label }), list.at(*value), flags);
		if (response) {
			for (int i = 0; i < list.size(); i++) {
				bool is_selected = (*value == i);
				if (ImGui::Selectable(list.at(i), is_selected))
					*value = i;
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::PopItemWidth();
		ImGui::SameLine(0, spacing);
		if (ImGui::ArrowButton(strcat({ "##", label, "Left" }), ImGuiDir_Left)) {
			*value -= 1;
			if (*value < 0) *value = (list.size() - 1);
		}
		ImGui::SameLine(0, spacing);
		if (ImGui::ArrowButton(strcat({ "##", label, "Right" }), ImGuiDir_Right)) {
			*value += 1;
			if (*value > (list.size() - 1)) *value = 0;
		}
		ImGui::SameLine(0, style.ItemInnerSpacing.x);
		ImGui::Text(label);

		return response;
	}

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
			//SteppedSliderFloat("Player Speed", &State.PlayerSpeed, 0.5f, 3.f, 0.25f, "%.2fx", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput);
			//CustomListBoxInt("Kill Distance", &State.KillDistance, KILL_DISTANCE, ImGuiComboFlags_NoArrowButton);
			//CustomListBoxInt("Task Bar Updates", &State.TaskProgressVisibility, TASKPROGRESSVISIBILITY, ImGuiComboFlags_NoArrowButton);
			if (ImGui::Checkbox("No Clip", &State.NoClip)) {
				if (!IsInGame()) State.NoClip = false;
				else {
					if (State.NoClip)
						app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Ghost"), NULL), NULL);
					else
						app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Players"), NULL), NULL);
				}
			}
			ImGui::Checkbox("Reveal Impostors", &State.RevealImpostors);
			ImGui::Checkbox("Unlock Vents", &State.UnlockVents);
			ImGui::Checkbox("Always show Chat Button", &State.ChatAlwaysActive);
			ImGui::Checkbox("Read Messages by Ghosts", &State.ReadGhostMessages);
			if (ImGui::Button("Edit Hotkeys")) {
				ImGui::OpenPopup("Hotkeys Editor");
			}
			ImHotKey::Edit(State.Hotkeys.data(), State.Hotkeys.size(), "Hotkeys Editor");

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
				ImGui::EndTabItem();
			}

			if (GetPlayerData(*Game::pLocalPlayer)->fields.Tasks != NULL && !GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor) {
				if (ImGui::BeginTabItem("Tasks")) {
					auto tasks = GetPlayerTasks(*Game::pLocalPlayer);

					for (auto task : tasks) {
						if (ImGui::Button(("Complete##Button" + std::to_string(task->fields._._Id_k__BackingField)).c_str()) && !NormalPlayerTask_get_IsComplete(task, NULL)) {
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
				//ImGui::Text("Auto-Repair");
				//ImGui::Checkbox("Lights##repair", &State.AutoRepairLights);
				//ImGui::Checkbox("Reactor##repair", &State.AutoRepairReactor);
				//ImGui::Checkbox("Oxygen##repair", &State.AutoRepairOxygen);
				//ImGui::Checkbox("Comms##repair", &State.AutoRepairComms);
				ImGui::EndChild();

				ImGui::SameLine();
				ImGui::BeginChild("system#sabotage");
				if (ImGui::Button("Sabotage Lights")) {
					State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_Electrical));
				}
				if (ImGui::Button("Sabotage Reactor")) {
					if ((*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Ship || (*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Hq)
						State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_Reactor));

					if ((*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Pb)
						State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_Laboratory));
				}
				if (ImGui::Button("Sabotage Oxygen")) {
					State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_LifeSupp));
				}
				if (ImGui::Button("Sabotage Comms")) {
					State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_Comms));
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
							State.rpcQueue.push(new RpcCloseDoorsOfType(State.selectedDoor, false));
						}

						if (std::find(State.pinnedDoors.begin(), State.pinnedDoors.end(), State.selectedDoor) == State.pinnedDoors.end()) {
							if (ImGui::Button("Pin Door")) {
								State.rpcQueue.push(new RpcCloseDoorsOfType(State.selectedDoor, true));
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

	}

	void ResetModifiers() {

	}
}