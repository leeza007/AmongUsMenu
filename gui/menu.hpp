#pragma once
#include "il2cpp-appdata.h"
#define _USE_MATH_DEFINES
#include <imgui/imgui.h>
#include "imgui/imgui_internal.h"
#include <math.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include "state.hpp"
#include "game.hpp"
#include "utility.h"

namespace Menu
{
	void Init();
	void Render();
	void UpdateModifiers();
	void ResetModifiers();
}