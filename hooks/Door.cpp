#include "_hooks.h"

using namespace app;

void dPlainDoor_SetDoorway(PlainDoor* __this, bool open, MethodInfo* method) {
	if (open && (std::find(State.pinnedDoors.begin(), State.pinnedDoors.end(), __this->fields.Room) != State.pinnedDoors.end())) {
		ShipStatus_RpcCloseDoorsOfType(*Game::pShipStatus, __this->fields.Room, NULL);
	}
	PlainDoor_SetDoorway(__this, open, method);
}

bool dAutoOpenDoor_DoUpdate(AutoOpenDoor* __this, float dt, MethodInfo* method) {
	if ((std::find(State.pinnedDoors.begin(), State.pinnedDoors.end(), __this->fields._.Room) != State.pinnedDoors.end()) && __this->fields.ClosedTimer < 1) {
		ShipStatus_RpcCloseDoorsOfType(*Game::pShipStatus, __this->fields._.Room, NULL);
	}
	return AutoOpenDoor_DoUpdate(__this, dt, method);
}
