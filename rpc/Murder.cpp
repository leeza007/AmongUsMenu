#include "il2cpp-appdata.h"
#include "_rpc.h"
#include "utility.h"

MurderRPC::MurderRPC(uint8_t selectedPlayer, uint8_t targetedPlayer)
{
	this->selectedPlayer = selectedPlayer;
	this->targetedPlayer = targetedPlayer;
}

void MurderRPC::Process()
{
	auto selectedPlayerData = GetPlayerDataById(this->selectedPlayer);
	auto targetedPlayerData = GetPlayerDataById(this->targetedPlayer);
	if (selectedPlayerData && targetedPlayerData
		&& !selectedPlayerData->fields.Disconnected && !targetedPlayerData->fields.Disconnected
		&& !selectedPlayerData->fields.IsDead && !targetedPlayerData->fields.IsDead
		&& selectedPlayerData->fields.IsImpostor) {
		app::PlayerControl_RpcMurderPlayer(selectedPlayerData->fields._object, targetedPlayerData->fields._object, NULL);
	}
}
