#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

MurderEvent::MurderEvent(PlayerControl* murderer, PlayerControl* victim, app::Vector2 position) : EventInterface(murderer, EVENT_MURDER) {
	this->victim = victim;
	this->position = position;
	this->systemType = GetSystemTypes(position);
}

std::string MurderEvent::Output() {
	std::stringstream outputStream;
	outputStream << convert_from_string(getSource()->fields._cachedData->fields.PlayerName)
		<< " has murdered "
		<< convert_from_string(victim->fields._cachedData->fields.PlayerName)
		<< " in "
		<< TranslateSystemTypes(systemType);
	return outputStream.str();
}