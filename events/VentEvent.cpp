#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

VentEvent::VentEvent(PlayerControl* player, app::Vector2 position, VENT_ACTION action) : EventInterface(player, EVENT_VENT) {
	this->position = position;
	this->systemType = GetSystemTypes(position);
	this->action = action;
}

std::string VentEvent::Output() {
	std::stringstream outputStream;
	outputStream << convert_from_string(getSource()->fields._cachedData->fields.PlayerName)
		<< ((action == VENT_ENTER) ? " entered Vent in " : " exited Vent in ")
		<< TranslateSystemTypes(systemType);
	return outputStream.str();
}