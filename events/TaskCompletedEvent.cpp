#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

TaskCompletedEvent::TaskCompletedEvent(PlayerControl* player, app::TaskTypes__Enum taskType, app::Vector2 position) : EventInterface(player, EVENT_TASK_COMPLETED) {
	this->taskType = taskType;
	this->position = position;
	this->systemType = GetSystemTypes(position);
}

void TaskCompletedEvent::Output() {
	std::stringstream outputStream;
	outputStream
		<< "> "
		<< ((taskType == -1) ? "UNKNOWN" : TranslateTaskTypes(taskType))
		<< " (" << TranslateSystemTypes(systemType) << ")";
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(GetPlayerData(getSource())->fields.ColorId)),
		convert_from_string(getSource()->fields._cachedData->fields.PlayerName).c_str());
	ImGui::SameLine();
	ImGui::Text(outputStream.str().c_str());
}

void TaskCompletedEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0, 255, 0, 255), "TASK");
	ImGui::SameLine();
	ImGui::Text("]");
}