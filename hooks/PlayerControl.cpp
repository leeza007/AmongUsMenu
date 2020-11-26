#include "_hooks.hpp"

using namespace app;

void dPlayerControl_CompleteTask(PlayerControl* __this, uint32_t idx, MethodInfo* method) {
	std::optional<TaskTypes__Enum> taskType = std::nullopt;

	auto normalPlayerTasks = GetNormalPlayerTasks(__this);
	for (auto normalPlayerTask : normalPlayerTasks)
		if (normalPlayerTask->fields._._Id_k__BackingField == idx) taskType = normalPlayerTask->fields._.TaskType;

	State.events.push_back(new TaskCompletedEvent(GetEventPlayer(__this), taskType, PlayerControl_GetTruePosition(__this, NULL)));
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

		if (State.Wallhack) {
			Camera__Array* allCameras = (Camera__Array*)il2cpp_array_new((Il2CppClass*)app::Camera__TypeInfo, 32);
			Camera_GetAllCameras(allCameras, NULL);
			for (Camera* cam : allCameras->vector) {
				if (cam) {
					Transform* camTransform = Component_get_transform((Component*)cam, NULL);
					Vector3 camPosition = Transform_get_position(camTransform, NULL);
					camPosition.z = 100;
					Transform_set_position(camTransform, camPosition, NULL);
				}
			}
		}

		// TODO: Improve performance
		/*Vector2 position = PlayerControl_GetTruePosition(__this, NULL);
		std::optional<Vector2> lastPosition = GetLastWalkEventPosition(__this->fields.PlayerId);
		if (!lastPosition.has_value() ||(lastPosition.has_value() && position.x != lastPosition->x && position.y != lastPosition->y))
			State.events.push_back(new WalkEvent(GetEventPlayer(__this), position));*/
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
	State.events.push_back(new KillEvent(GetEventPlayer(__this), GetEventPlayer(target), PlayerControl_GetTruePosition(__this, NULL)));
	PlayerControl_MurderPlayer(__this, target, method);
}

void dPlayerControl_ReportDeadBody(PlayerControl*__this, GameData_PlayerInfo* target, MethodInfo *method) {
	State.events.push_back(new ReportDeadBodyEvent(GetEventPlayer(__this), GetEventPlayer(target), PlayerControl_GetTruePosition(__this, NULL)));
	PlayerControl_ReportDeadBody(__this, target, method);
}

void dPlayerControl_RpcSetInfected(PlayerControl* __this, GameData_PlayerInfo__Array* infected, MethodInfo* method) {
	for (int i = 0; i < (*Game::pGameOptionsData)->fields.NumImpostors; i++) {
		if (State.impostors[i] != nullptr) {
			infected->vector[i] = GetPlayerData(State.impostors[i]);
		}
	}
	PlayerControl_RpcSetInfected(__this, infected, method);
}