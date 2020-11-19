#pragma once
#include <iostream>

enum EVENT_TYPES {
	EVENT_WALK = 0x0,
	EVENT_MURDER = 0x1,
	EVENT_VENT = 0x2,
	EVENT_TASK_COMPLETED = 0x3,
	EVENT_DEADBODY_FOUND = 0x4
};

enum VENT_ACTION {
	VENT_ENTER = 0x0,
	VENT_EXIT = 0x1
};

class EventInterface {
private:
	EVENT_TYPES type;
public:
	EventInterface(EVENT_TYPES type) { EventInterface::type = type; }
	virtual ~EventInterface() {}
	virtual std::string Output() = 0;
	EVENT_TYPES getType() { return EventInterface::type; }
};

class MurderEvent : public EventInterface {
private:
	std::string murderer;
	std::string victim;
	app::Vector2 position;
	app::SystemTypes__Enum room;
public:
	MurderEvent(std::string murderer, std::string victim, app::Vector2 position);
	virtual std::string Output() override;
};

class VentEvent : public EventInterface {
private:
	std::string player;
	app::Vector2 position;
	app::SystemTypes__Enum room;
	VENT_ACTION action;
public:
	VentEvent(std::string player, app::Vector2 position, VENT_ACTION action);
	virtual std::string Output() override;
};