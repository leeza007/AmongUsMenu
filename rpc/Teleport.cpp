#include "il2cpp-appdata.h"
#include "_rpc.h"
#include "utility.h"

TeleportRPC::TeleportRPC(uint8_t selectedPlayer, Vector2 targetVector)
{
	this->selectedPlayer = selectedPlayer;
	this->targetVector = targetVector;
}

void TeleportRPC::Process()
{
	auto selectedPlayerData = GetPlayerDataById(this->selectedPlayer);
	if (selectedPlayerData && !selectedPlayerData->fields.Disconnected) {
		CustomNetworkTransform_RpcSnapTo(selectedPlayerData->fields._object->fields.NetTransform, this->targetVector, NULL);
	}
}