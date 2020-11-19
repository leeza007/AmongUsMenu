#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

std::string VentEvent::Output() {
	std::stringstream ss;
	ss << convert_from_string(GetPlayerData(source)->fields.PlayerName);
	if (VentEvent::action == VENT_ENTER) ss << " entered Vent in ";
	else ss << " exited Vent in ";

	Vector2 vec;
	vec.x = vent->fields.Offset.x;
	vec.y = vent->fields.Offset.y;
	ss << getRoomNameByVector2(vec);

	return ss.str();
}