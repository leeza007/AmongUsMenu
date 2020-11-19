#include "sabotage_tab.h"

namespace SabotageTab {
	void Render() {
		if (IsInGame()) {
			if (ImGui::BeginTabItem("Sabotage")) {
				if (ImGui::Button("Sabotage Lights")) {
					State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_Electrical));
				}
				if (ImGui::Button("Sabotage Reactor")) {
					if ((*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Ship || (*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Hq)
						State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_Reactor));

					if ((*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Pb)
						State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_Laboratory));
				}
				if (ImGui::Button("Sabotage Oxygen")) {
					State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_LifeSupp));
				}
				if (ImGui::Button("Sabotage Comms")) {
					State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_Comms));
				}
				if (ImGui::Button("Repair Sabotage")) {
					RepairSabotage(*Game::pLocalPlayer);
				}
				ImGui::EndTabItem();
			}
		}
	}
}