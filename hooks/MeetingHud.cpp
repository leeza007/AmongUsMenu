#include "_hooks.hpp"

using namespace app;

void dMeetingHud_Update(MeetingHud* __this, MethodInfo* method) {
	if (IsInGame()) {
		PlayerVoteArea__Array* playerStates = __this->fields.playerStates;
		for (il2cpp_array_size_t i = 0; i < playerStates->max_length; i++) {
			PlayerVoteArea* playerVoteArea = playerStates->vector[i];
			auto playerData = GetPlayerDataById(playerVoteArea->fields._TargetPlayerId_k__BackingField);
			auto localData = GetPlayerData(*Game::pLocalPlayer);
			if (playerData && localData) {
				if (State.RevealImpostors || localData->fields.IsImpostor)
					playerVoteArea->fields.NameText->fields.Color = playerData->fields.IsImpostor
					? Palette__TypeInfo->static_fields->ImpostorRed
					: Palette__TypeInfo->static_fields->White;
				else
					playerVoteArea->fields.NameText->fields.Color = Palette__TypeInfo->static_fields->White;
			}
		}
	}
	MeetingHud_Update(__this, method);
}