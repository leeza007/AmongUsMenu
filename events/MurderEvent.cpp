#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

std::string MurderEvent::Output() {
	std::stringstream ss;
	ss << convert_from_string(GetPlayerData(source)->fields.PlayerName) 
		<< " has murdered "
		<< convert_from_string(GetPlayerData(target)->fields.PlayerName)
		<< " in "
		<< getRoomNameByVector2(position);
	return ss.str();
}