#include "il2cpp-appdata.h"
#include "_rpc.h"
#include "utility.h"

RpcMurderPlayer::RpcMurderPlayer(PlayerControl* target)
{
	this->target = target;
}

void RpcMurderPlayer::Process()
{
	PlayerControl_RpcMurderPlayer(*Game::pLocalPlayer, this->target, NULL);
}