#include "il2cpp-appdata.h"
#include "_rpc.h"
#include "utility.h"

SabotageRPC::SabotageRPC(SystemTypes__Enum selectedSystem)
{
	this->selectedSystem = selectedSystem;
}

void SabotageRPC::Process()
{
	ShipStatus_RpcRepairSystem(*Game::pShipStatus, app::SystemTypes__Enum_Sabotage, this->selectedSystem, NULL);
}