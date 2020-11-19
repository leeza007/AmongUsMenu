#include "console.hpp"

namespace ConsoleGui {
	void Init() {
		ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(1.F);
	}

	bool init = false;
	void Render() {
		if (!init)
			ConsoleGui::Init();

		ImGui::Begin("Console", &State.ShowConsole, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
		ImGui::BeginChild("console#scroll", ImVec2(490, 225), true);
		for (int i = State.events.size() - 1; i >= 0; i--) {
			auto playerData = GetPlayerData(State.events[i]->getSource());
			std::string playerName = convert_from_string(playerData->fields.PlayerName);
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			ImGui::ColorButton(std::string("console##" + playerName + "_ColorButton").c_str(), AmongUsColorToImVec4(GetPlayerColor(playerData->fields.ColorId)), ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip);
			ImGui::SameLine();
			ImGui::PopStyleVar(2);
			ImGui::Dummy(ImVec2(0, 0));
			ImGui::SameLine();
			ImGui::TextWrapped(State.events[i]->Output().c_str());
		}
		ImGui::EndChild();
		ImGui::End();
	}
}