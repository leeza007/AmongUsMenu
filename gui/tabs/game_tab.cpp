#include "game_tab.h"

namespace GameTab {
	void Render() {
		if (ImGui::BeginTabItem("Game")) {
			ImGui::Checkbox("Max Vision", &State.MaxVision);
			ImGui::Checkbox("Wallhack", &State.Wallhack);
			if (SteppedSliderFloat("Player Speed", &State.PlayerSpeed, 0.5f, 3.f, 0.25f, "%.2fx", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput)) {
				if (!IsInGame()) State.PlayerSpeed = State.PrevPlayerSpeed;
				else {
					(*Game::pGameOptionsData)->fields.PlayerSpeedMod = State.PlayerSpeed;
					State.PrevPlayerSpeed = State.PlayerSpeed;
				}
			}
			if (CustomListBoxInt("Kill Distance", &State.KillDistance, KILL_DISTANCE)) {
				if (!IsInGame()) State.KillDistance = State.PrevKillDistance;
				else {
					(*Game::pGameOptionsData)->fields.KillDistance = State.KillDistance;
					State.PrevKillDistance = State.KillDistance;
				}
			}
			if (CustomListBoxInt("Task Bar Updates", &State.TaskBarUpdates, TASKBARUPDATES)) {
				if (!IsInGame()) State.TaskBarUpdates = State.PrevTaskBarUpdates;
				else {
					(*Game::pGameOptionsData)->fields.TaskBarUpdates = (TaskBarUpdates__Enum)State.TaskBarUpdates;
					State.PrevTaskBarUpdates = State.TaskBarUpdates;
				}
			}
			if (ImGui::Checkbox("No Clip", &State.NoClip)) {
				if (!IsInGame()) State.NoClip = false;
				else {
					if (!(GetPlayerData(*Game::pLocalPlayer)->fields.IsDead)) {
						if (State.NoClip)
							app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Ghost"), NULL), NULL);
						else
							app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Players"), NULL), NULL);
					}
				}
			}
			ImGui::Checkbox("Reveal Impostors", &State.RevealImpostors);
			ImGui::Checkbox("Unlock Vents", &State.UnlockVents);
			ImGui::Checkbox("Always show Chat Button", &State.ChatAlwaysActive);
			ImGui::Checkbox("Read Messages by Ghosts", &State.ReadGhostMessages);
			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::Separator();
			/*if (ImGui::Button("Edit Hotkeys")) {
				ImGui::OpenPopup("Hotkeys Editor");
			}
			ImGui::SameLine();*/
			ImGui::Checkbox("Console", &State.ShowConsole);
			//ImHotKey::Edit(State.Hotkeys.data(), State.Hotkeys.size(), "Hotkeys Editor");

			ImGui::EndTabItem();
		}
	}
}