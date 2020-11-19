#include "menu.hpp"

using namespace app;

namespace Menu {
	void Init() {
		ImGui::SetNextWindowSize(ImVec2(400, 250), ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(1.F);
	}

	bool init = false;
	void Render() {
		if (!init)
			Menu::Init();

		ImGui::Begin("AmongUsMenu", &State.ShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::BeginTabBar("AmongUs#TopBar", ImGuiTabBarFlags_NoTabListScrollingButtons);

		GameTab::Render();
		RadarTab::Render();
		PlayersTab::Render();
		TasksTab::Render();
		SabotageTab::Render();
		DoorsTab::Render();
		
		ImGui::EndTabBar();
		//ImGui::Checkbox("Console", &State.ShowConsole);
		ImGui::End();
	}
}