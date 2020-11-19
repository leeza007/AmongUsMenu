#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

TaskCompletedEvent::TaskCompletedEvent(PlayerControl* player, app::TaskTypes__Enum taskType, app::Vector2 position) : EventInterface(player, EVENT_TASK_COMPLETED) {
	this->taskType = taskType;
	this->position = position;
	this->systemType = GetSystemTypes(position);
}

std::string TaskCompletedEvent::Output() {
	std::stringstream outputStream;
	outputStream << convert_from_string(getSource()->fields._cachedData->fields.PlayerName)
		<< " completed their task "
		<< ((taskType == -1) ? "UNKNOWN" : TranslateTaskTypes(taskType))
		<< " in " << TranslateSystemTypes(systemType);
	return outputStream.str();
}