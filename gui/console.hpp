#pragma once
#include <imgui/imgui.h>
#include "imgui/imgui_internal.h"
#include "imgui/imHotKey.h"
#include "state.hpp"
#include "utility.h"
#include "gui-helpers.hpp"

namespace ConsoleGui {
	const std::vector<const char*> BY_TYPE = { "", "Murder", "Vent", "Task", "Report", "Meeting", "Sabotage", "Repair" };
	extern int selectedType;

	void Init();
	void Render();
};