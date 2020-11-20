#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

MurderEvent::MurderEvent(PlayerControl* murderer, PlayerControl* victim, app::Vector2 position) : EventInterface(murderer, EVENT_MURDER) {
	this->victim = victim;
	this->position = position;
	this->systemType = GetSystemTypes(position);
}

void MurderEvent::Output() {
	std::stringstream outputStream;
	outputStream
		<< "("
		<< TranslateSystemTypes(systemType)
		<< ")";
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(GetPlayerData(getSource())->fields.ColorId)),
		convert_from_string(getSource()->fields._cachedData->fields.PlayerName).c_str());
	ImGui::SameLine();
	ImGui::Text(">");
	ImGui::SameLine();
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(GetPlayerData(victim)->fields.ColorId)),
		convert_from_string(victim->fields._cachedData->fields.PlayerName).c_str());
	ImGui::SameLine();
	ImGui::Text(outputStream.str().c_str());
}

void MurderEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(255, 0, 0, 255), "KILL");
	ImGui::SameLine();
	ImGui::Text("]");
}