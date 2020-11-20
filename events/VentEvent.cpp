#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

VentEvent::VentEvent(PlayerControl* player, app::Vector2 position, VENT_ACTION action) : EventInterface(player, EVENT_VENT) {
	this->position = position;
	this->systemType = GetSystemTypes(position);
	this->action = action;
}

void VentEvent::Output() {
	std::stringstream outputStream;
	outputStream << "(" << TranslateSystemTypes(systemType) << ")";
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(GetPlayerData(getSource())->fields.ColorId)),
		convert_from_string(getSource()->fields._cachedData->fields.PlayerName).c_str());
	ImGui::SameLine();
	ImGui::Text(outputStream.str().c_str());
}

void VentEvent::ColoredEventOutput() {
	ImGui::Text("[ VENT");
	ImGui::SameLine();

	ImVec4 color;
	((action == VENT_ENTER) ? color = ImVec4(0, 255, 0, 255) : color = ImVec4(255, 0, 0, 255));

	ImGui::TextColored(color, ((action == VENT_ENTER) ? "IN" : "OUT"));
	ImGui::SameLine();
	ImGui::Text("]");
}