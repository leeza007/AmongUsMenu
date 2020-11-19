#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

MurderEvent::MurderEvent(std::string murderer, std::string victim, app::Vector2 position) : EventInterface(EVENT_MURDER)
{
	this->murderer = murderer;
	this->victim = victim;
	this->position = position;
	this->room = GetSystemTypes(position);
}

std::string MurderEvent::Output() {
	std::stringstream outputStream;
	outputStream << murderer << " has murdered " << victim << " in " << TranslateSystemTypes(room);
	return outputStream.str();
}