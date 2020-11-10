#include "_hooks.h"

using namespace app;

void dAmongUsClient_OnStartGame(AmongUsClient* __this, MethodInfo* method) {
	Menu::ResetModifiers();
	AmongUsClient_OnStartGame(__this, method);
}