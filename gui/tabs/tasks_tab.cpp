#include "tasks_tab.h"

namespace TasksTab {
	void Render() {
		if (IsInGame() && GetPlayerData(*Game::pLocalPlayer)->fields.Tasks != NULL && !GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor) {
			if (ImGui::BeginTabItem("Tasks")) {
				auto tasks = GetNormalPlayerTasks(*Game::pLocalPlayer);

				for (auto task : tasks) {
					if (ImGui::Button(("Complete##Button" + std::to_string(task->fields._._Id_k__BackingField)).c_str()) && !NormalPlayerTask_get_IsComplete(task, NULL)) {
						CompleteTask(task);
					}

					ImGui::SameLine();

					ImGui::TextColored(NormalPlayerTask_get_IsComplete(task, NULL)
						? ImVec4(0.0F, 1.0F, 0.0F, 1.0F)
						: AmongUsColorToImVec4(app::Palette__TypeInfo->static_fields->White)
						, TranslateTaskTypes(task->fields._.TaskType));
				}

				ImGui::EndTabItem();
			}
		}
	}
}