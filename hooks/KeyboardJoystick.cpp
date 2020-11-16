#include "_hooks.h"

void dKeyboardJoystick_Update(KeyboardJoystick* __this, MethodInfo* method) {
	if (IsInGame()) {	
		if (!State.rpcQueue.empty()) {
			auto rpc = State.rpcQueue.front();
			State.rpcQueue.pop();

			rpc->Process();
			delete rpc;
		}

		if (State.NoKillCooldown && (*Game::pGameOptionsData)->fields.KillCooldown > 0.1f) {
			(*Game::pGameOptionsData)->fields.KillCooldown = 0.1f;
		}
	}

	app::KeyboardJoystick_Update(__this, method);
}