#include "console.hpp"

namespace ConsoleGui {
	void Init() {
		ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(1.F);
	}

	bool init = false;
	void Render() {
		if (!init)
			ConsoleGui::Init();

		ImGui::Begin("Console", &State.ShowConsole, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
		ImGui::BeginChild("console#scroll", ImVec2(490, 225), true);
		for (int i = State.events.size() - 1; i >= 0; i--) {
			State.events[i]->ColoredEventOutput();
			ImGui::SameLine();
			State.events[i]->Output();
		}
		ImGui::EndChild();
		ImGui::End();
	}
}