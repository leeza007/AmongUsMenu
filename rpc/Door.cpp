#include "il2cpp-appdata.h"
#include "_rpc.h"
#include "utility.h"
#include "state.hpp"

DoorRPC::DoorRPC(SystemTypes__Enum selectedSystem, bool pinDoor)
{
	this->selectedSystem = selectedSystem;
	this->pinDoor = pinDoor;
}

void DoorRPC::Process()
{
	app::ShipStatus_RpcCloseDoorsOfType(*Game::pShipStatus, this->selectedSystem, NULL);
	if (this->pinDoor)
		State.pinnedDoors.push_back(this->selectedSystem);
}