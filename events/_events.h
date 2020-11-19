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
	PlayerControl* source;
	PlayerControl* target;
	Vector2 position;
public:
	MurderEvent(PlayerControl* source, PlayerControl* target) : EventInterface(EVENT_MURDER) {
		MurderEvent::source = source;
		MurderEvent::target = target;
		MurderEvent::position = PlayerControl_GetTruePosition(target, 0);
	}
	virtual std::string Output() override;
};

class VentEvent : public EventInterface {
private:
	Vent* vent;
	PlayerControl* source;
	VENT_ACTION action;
public:
	VentEvent(Vent* vent, PlayerControl* source, VENT_ACTION action) : EventInterface(EVENT_VENT) {
		VentEvent::vent = vent;
		VentEvent::source = source;
		VentEvent::action;
	}
	virtual std::string Output() override;
};