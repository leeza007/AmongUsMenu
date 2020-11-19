#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

VentEvent::VentEvent(std::string player, app::Vector2 position, VENT_ACTION action) : EventInterface(EVENT_VENT)
{
	this->player = player;
	this->position = position;
	this->room = GetSystemTypes(position);
	this->action = action;
}

std::string VentEvent::Output() {
	std::stringstream outputStream;
	outputStream << player << ((action == VENT_ENTER) ? " entered Vent in " : " exited Vent in ") << TranslateSystemTypes(room);
	return outputStream.str();
}