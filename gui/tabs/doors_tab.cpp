#include "doors_tab.h"

namespace DoorsTab {
	void Render() {
		if (IsInGame() && !State.mapDoors.empty()) {
			if (ImGui::BeginTabItem("Doors")) {
				ImGui::BeginChild("doors#list", ImVec2(200, 0), true);
				ImGui::ListBoxHeader("", ImVec2(200, 150));
				for (size_t i = 0; i < State.mapDoors.size(); i++) {
					auto systemType = State.mapDoors[i];
					if (ImGui::Selectable(TranslateSystemTypes(systemType), State.selectedDoor == systemType))
						State.selectedDoor = systemType;
				}
				ImGui::ListBoxFooter();
				ImGui::EndChild();

				ImGui::SameLine();
				ImGui::BeginChild("doors#options", ImVec2(200, 0));
				if (ImGui::Button("Close All Doors"))
				{
					for(auto door : State.mapDoors)
					{
						State.rpcQueue.push(new RpcCloseDoorsOfType(door, false));
					}
				}
				if (State.selectedDoor != SystemTypes__Enum_Hallway) {
					if (ImGui::Button("Close Door")) {
						State.rpcQueue.push(new RpcCloseDoorsOfType(State.selectedDoor, false));
					}

					if (std::find(State.pinnedDoors.begin(), State.pinnedDoors.end(), State.selectedDoor) == State.pinnedDoors.end()) {
						if (ImGui::Button("Pin Door")) {
							State.rpcQueue.push(new RpcCloseDoorsOfType(State.selectedDoor, true));
						}
					}
					else {
						if (ImGui::Button("Unpin Door")) {
							State.pinnedDoors.erase(std::remove(State.pinnedDoors.begin(), State.pinnedDoors.end(), State.selectedDoor), State.pinnedDoors.end());
						}
					}
				}
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
		}
	}
}