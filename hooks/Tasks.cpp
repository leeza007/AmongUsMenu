#include "_hooks.h"

using namespace app;

void dElectricTask_FixedUpdate(ElectricTask* __this, MethodInfo* method) {
	if (State.AutoRepairLights && !GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor) {
		auto switchSystem = __this->fields.system;
		auto actualSwitches = switchSystem->fields.ActualSwitches;
		auto expectedSwitches = switchSystem->fields.ExpectedSwitches;

		if (actualSwitches != expectedSwitches) {
			for (auto i = 0; i < 5; i++) {
				auto mask = 1 << (i & 0x1F);

				if ((actualSwitches & mask) != (expectedSwitches & mask)) {
					ShipStatus_RpcRepairSystem(*Game::pShipStatus, SystemTypes__Enum_Electrical, i, NULL);
					break;
				}
			}
		}
	}

	ElectricTask_FixedUpdate(__this, method);
}

void dNoOxyTask_FixedUpdate(NoOxyTask* __this, MethodInfo* method) {
	if (State.AutoRepairOxygen && !GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor) {
		ShipStatus_RpcRepairSystem(*Game::pShipStatus, SystemTypes__Enum_LifeSupp, 64, NULL);
		ShipStatus_RpcRepairSystem(*Game::pShipStatus, SystemTypes__Enum_LifeSupp, 65, NULL);
	}

	NoOxyTask_FixedUpdate(__this, method);
}

void dReactorTask_FixedUpdate(ReactorTask* __this, MethodInfo* method) {
	if (State.AutoRepairReactor && !GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor) {
		if ((*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Ship || (*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Hq) {
			ShipStatus_RpcRepairSystem(*Game::pShipStatus, SystemTypes__Enum_Reactor, 64, NULL);
			ShipStatus_RpcRepairSystem(*Game::pShipStatus, SystemTypes__Enum_Reactor, 65, NULL);
		}

		if ((*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Pb) {
			ShipStatus_RpcRepairSystem(*Game::pShipStatus, SystemTypes__Enum_Laboratory, 64, NULL);
			ShipStatus_RpcRepairSystem(*Game::pShipStatus, SystemTypes__Enum_Laboratory, 65, NULL);
		}
	}

	ReactorTask_FixedUpdate(__this, method);
}

void dHudOverrideTask_FixedUpdate(HudOverrideTask* __this, MethodInfo* method) {
	if (State.AutoRepairComms && !GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor) {
		ShipStatus_RpcRepairSystem(*Game::pShipStatus, SystemTypes__Enum_Comms, 0, NULL);
	}

	HudOverrideTask_FixedUpdate(__this, method);
}

void dHqHudOverrideTask_FixedUpdate(HqHudOverrideTask* __this, MethodInfo* method) {
	if (State.AutoRepairComms && !GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor) {
		ShipStatus_RpcRepairSystem(*Game::pShipStatus, SystemTypes__Enum_Comms, 16, NULL);
		ShipStatus_RpcRepairSystem(*Game::pShipStatus, SystemTypes__Enum_Comms, 17, NULL);
	}

	HqHudOverrideTask_FixedUpdate(__this, method);
}