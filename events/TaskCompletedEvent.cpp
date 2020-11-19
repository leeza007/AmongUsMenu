#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

TaskCompletedEvent::TaskCompletedEvent(std::string player, app::TaskTypes__Enum taskType, app::Vector2 position) : EventInterface(EVENT_TASK_COMPLETED)
{
	this->player = player;
	this->taskType = taskType;
	this->position = position;
	this->systemType = GetSystemTypes(position);
}

std::string TaskCompletedEvent::Output()
{
	std::stringstream outputStream;
	outputStream << player << " completed their task " << ((taskType == -1) ? "UNKNOWN" : TranslateTaskTypes(taskType)) << " in " << TranslateSystemTypes(systemType);
	return outputStream.str();
}