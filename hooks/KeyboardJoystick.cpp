#include "_hooks.h"

using namespace app;

void dKeyboardJoystick_Update(KeyboardJoystick* __this, MethodInfo* method) {
	if (IsInGame()) {
		Menu::UpdateModifiers();
		
		if (!State.rpcQueue.empty()) {
			auto rpc = State.rpcQueue.front();
			State.rpcQueue.pop();

			rpc->Process();
			delete rpc;
		}
	}

	KeyboardJoystick_Update(__this, method);
}