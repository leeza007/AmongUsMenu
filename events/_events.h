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
	PlayerControl* source;
public:
	EventInterface(PlayerControl* source, EVENT_TYPES type) {
		EventInterface::source = source;
		EventInterface::type = type;
	}
	virtual ~EventInterface() {}
	virtual std::string Output() = 0;
	EVENT_TYPES getType() { return EventInterface::type; }
	PlayerControl* getSource() { return EventInterface::source; }
};

class MurderEvent : public EventInterface {
private:
	PlayerControl* victim;
	app::Vector2 position;
	app::SystemTypes__Enum systemType;
public:
	MurderEvent(PlayerControl* murderer, PlayerControl* victim, app::Vector2 position);
	virtual std::string Output() override;
};

class VentEvent : public EventInterface {
private:
	app::Vector2 position;
	app::SystemTypes__Enum systemType;
	VENT_ACTION action;
public:
	VentEvent(PlayerControl* player, app::Vector2 position, VENT_ACTION action);
	virtual std::string Output() override;
};

class TaskCompletedEvent : public EventInterface {
private:
	app::TaskTypes__Enum taskType;
	app::Vector2 position;
	app::SystemTypes__Enum systemType;
public:
	TaskCompletedEvent(PlayerControl* player, app::TaskTypes__Enum taskType, app::Vector2 position);
	virtual std::string Output() override;
};