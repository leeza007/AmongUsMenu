#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

ReportDeadBodyEvent::ReportDeadBodyEvent(PlayerControl* player, GameData_PlayerInfo* target, app::Vector2 position) : EventInterface(player, EVENT_REPORT_DEADBODY) {
	this->target = target;
	this->position = position;
	this->systemType = GetSystemTypes(position);
}

std::string ReportDeadBodyEvent::Output() {
	std::stringstream outputStream;
	outputStream << convert_from_string(getSource()->fields._cachedData->fields.PlayerName)
		<< " has found "
		<< convert_from_string(target->fields.PlayerName)
		<< "'s Dead Body in "
		<< TranslateSystemTypes(systemType);
	return outputStream.str();
}