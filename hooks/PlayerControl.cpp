#include "_hooks.hpp"

using namespace app;

void dPlayerControl_CompleteTask(PlayerControl* __this, uint32_t idx, MethodInfo* method) {
	auto player = convert_from_string(__this->fields._cachedData->fields.PlayerName);
	TaskTypes__Enum taskType = (TaskTypes__Enum )-1;
	auto position = PlayerControl_GetTruePosition(__this, NULL);

	auto normalPlayerTasks = GetNormalPlayerTasks(__this);
	for (auto normalPlayerTask : normalPlayerTasks)
		if (normalPlayerTask->fields._._Id_k__BackingField == idx) taskType = normalPlayerTask->fields._.TaskType;

	State.events.push_back(new TaskCompletedEvent(player, taskType, position));
	PlayerControl_CompleteTask(__this, idx, method);
}

void dPlayerControl_FixedUpdate(PlayerControl* __this, MethodInfo* method) {
	if (IsInGame()) {
		auto playerData = GetPlayerData(__this);
		auto localData = GetPlayerData(*Game::pLocalPlayer);
		TextRenderer* nameText = (TextRenderer*)(__this->fields.nameText);

		if (!playerData || !localData)
			return;

		if (State.RevealImpostors || localData->fields.IsImpostor)
			nameText->fields.Color = playerData->fields.IsImpostor
			? Palette__TypeInfo->static_fields->ImpostorRed
			: Palette__TypeInfo->static_fields->White;
		else
			nameText->fields.Color = Palette__TypeInfo->static_fields->White;
	}
	PlayerControl_FixedUpdate(__this, method);
}

void dPlayerControl_RpcSyncSettings(PlayerControl* __this, GameOptionsData* gameOptions, MethodInfo* method) {
	State.PrevPlayerSpeed = gameOptions->fields.PlayerSpeedMod;
	State.PlayerSpeed = gameOptions->fields.PlayerSpeedMod;
	State.PrevKillDistance = gameOptions->fields.KillDistance;
	State.KillDistance = gameOptions->fields.KillDistance;
	State.PrevTaskBarUpdates = gameOptions->fields.TaskBarUpdates;
	State.TaskBarUpdates = gameOptions->fields.TaskBarUpdates;

	PlayerControl_RpcSyncSettings(__this, gameOptions, method);
}

void dPlayerControl_MurderPlayer(PlayerControl* __this, PlayerControl* target, MethodInfo* method) {
	auto murderer = convert_from_string(__this->fields._cachedData->fields.PlayerName);
	auto victim = convert_from_string(target->fields._cachedData->fields.PlayerName);
	auto position = PlayerControl_GetTruePosition(__this, NULL);

	State.events.push_back(new MurderEvent(murderer, victim, position));
	PlayerControl_MurderPlayer(__this, target, method);
}