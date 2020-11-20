#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

KillEvent::KillEvent(PlayerControl* murderer, PlayerControl* victim, app::Vector2 position) : EventInterface(murderer, EVENT_KILL) {
	this->victim = victim;
	this->position = position;
	this->systemType = GetSystemTypes(position);
}

void KillEvent::Output() {
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

void KillEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "KILL");
	ImGui::SameLine();
	ImGui::Text("]");
}