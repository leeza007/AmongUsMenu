#include "players_tab.h"

namespace PlayersTab {
	void Render() {
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
						State.selectedPlayer = GetPlayerControlById(playerData->fields.PlayerId);
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

					if (playerData->fields.IsDead) nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->DisabledGrey);

					ImGui::TextColored(nameColor, playerName.c_str());
				}
				ImGui::ListBoxFooter();
				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("players#actions", ImVec2(200, 0), true);
				if (IsInMultiplayerGame() && !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead && ImGui::Button("Call Meeting")) {
					PlayerControl_CmdReportDeadBody(*Game::pLocalPlayer, NULL, NULL);
				}
				if (State.selectedPlayerId > -1 && State.selectedPlayer != *Game::pLocalPlayer) {
					if (ImGui::Button("Teleport To")) {
						State.rpcQueue.push(new RpcSnapTo(PlayerControl_GetTruePosition(State.selectedPlayer, NULL)));
					}
				}
				if (IsInMultiplayerGame() && (GetPlayerData(*Game::pLocalPlayer))->fields.IsDead == false && State.selectedPlayerId > -1 && ImGui::Button("Report Body")) {
					PlayerControl_CmdReportDeadBody(*Game::pLocalPlayer, GetPlayerData(State.selectedPlayer), NULL);
				}
				// Crashes the game when used, trying to find a workaround.
				//if ((GetPlayerData(*Game::pLocalPlayer))->fields.IsImpostor && (*Game::pLocalPlayer)->fields.killTimer <= 0) {
				//	if (State.selectedPlayerId > -1) {
				//		if (ImGui::Button("Kill")) {
				//			State.rpcQueue.push(new RpcSnapTo(PlayerControl_GetTruePosition(State.selectedPlayer, NULL)));
				//			PlayerControl_MurderPlayer(*Game::pLocalPlayer, State.selectedPlayer, NULL);
				//		}
				//	}
				//	if (State.selectedPlayerId > -1) {
				//		if (ImGui::Button("Kill & Back")) {
				//			auto prevPosition = PlayerControl_GetTruePosition(*Game::pLocalPlayer, NULL);
				//			State.rpcQueue.push(new RpcSnapTo(PlayerControl_GetTruePosition(State.selectedPlayer, NULL)));
				//			PlayerControl_MurderPlayer(*Game::pLocalPlayer, State.selectedPlayer, NULL);
				//			State.rpcQueue.push(new RpcSnapTo(prevPosition));
				//		}
				//	}
				//}
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
		}
	}
}