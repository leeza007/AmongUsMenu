#include "utility.h"

using namespace app;

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

int randi(int lo, int hi) {
	int n = hi - lo + 1;
	int i = rand() % n;
	if (i < 0) i = -i;
	return lo + i;
}

ImVec4 AmongUsColorToImVec4(Color color) {
	return ImVec4(color.r, color.g, color.b, color.a);
}

ImVec4 AmongUsColorToImVec4(CorrectedColor32 color) {
	return ImVec4(color.r / 255.0F, color.g / 255.0F, color.b / 255.0F, color.a / 255.0F);
}

#define LocalInGame (((*Game::pAmongUsClient)->fields.GameMode == GameModes__Enum_LocalGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum_Started))
#define OnlineInGame (((*Game::pAmongUsClient)->fields.GameMode == GameModes__Enum_OnlineGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum_Started))
#define TutorialScene (State.CurrentScene.compare("Tutorial") == 0)

bool IsInGame() {
	return (LocalInGame || OnlineInGame || TutorialScene) && (*Game::pShipStatus) && (*Game::pLocalPlayer);
}

GameData_PlayerInfo* GetPlayerData(PlayerControl* player) {
	if (player) return app::PlayerControl_get_Data(player, NULL);
	return NULL;
}

GameData_PlayerInfo* GetPlayerDataById(uint8_t id) {
	return app::GameData_GetPlayerById((*Game::pGameData), id, NULL);
}

PlayerControl* GetPlayerControlById(uint8_t id) {
	for (auto player : GetAllPlayerControl()) {
		if (player->fields.PlayerId == id) return player;
	}

	return NULL;
}

std::vector<PlayerControl*> GetAllPlayerControl() {
	static PlayerControl* (*getItem)(List_1_PlayerControl_*, int32_t, MethodInfo*);
	static int32_t (*getCount)(List_1_PlayerControl_*, MethodInfo*);
	if (getItem == NULL) getItem = decltype(getItem)(find_method((Il2CppClass*)(*Game::pAllPlayerControls)->klass, "PlayerControl", "get_Item", "System.Int32"));
	if (getCount == NULL) getCount = decltype(getCount)(find_method((Il2CppClass*)(*Game::pAllPlayerControls)->klass, "System.Int32", "get_Count", ""));

	std::vector<PlayerControl*> players = std::vector<PlayerControl*>();

	if (getItem != NULL && getCount != NULL) {
		for (int i = 0; i < getCount((*Game::pAllPlayerControls), NULL); i++)
			players.push_back(getItem((*Game::pAllPlayerControls), i, NULL));
	}

	return players;
}

std::vector<GameData_PlayerInfo*> GetAllPlayerData() {
	static GameData_PlayerInfo* (*getItem)(List_1_GameData_PlayerInfo_*, int32_t, MethodInfo*);
	static int32_t(*getCount)(List_1_GameData_PlayerInfo_*, MethodInfo*);
	if (getItem == NULL) getItem = decltype(getItem)(find_method((Il2CppClass*)(Il2CppClass*)(*Game::pGameData)->fields.AllPlayers->klass, "GameData.PlayerInfo", "get_Item", "System.Int32"));
	if (getCount == NULL) getCount = decltype(getCount)(find_method((Il2CppClass*)(Il2CppClass*)(*Game::pGameData)->fields.AllPlayers->klass, "System.Int32", "get_Count", ""));

	std::vector<GameData_PlayerInfo*> players = std::vector<GameData_PlayerInfo*>();

	if (getItem != NULL && getCount != NULL) {
		for (int i = 0; i < getCount((*Game::pGameData)->fields.AllPlayers, NULL); i++)
			players.push_back(getItem((*Game::pGameData)->fields.AllPlayers, i, NULL));
	}

	return players;
}

std::vector<DeadBody*> GetAllDeadBodies() {
	std::vector<DeadBody*> deadBodies = std::vector<DeadBody*>();

	Type* deadBody_Type = app::Type_GetType(convert_to_string(translate_type_name("DeadBody, Assembly-CSharp")), NULL);
	DeadBody__Array* deadBodyArray = (DeadBody__Array*)app::Object_1_FindObjectsOfType(deadBody_Type, NULL);

	for (il2cpp_array_size_t i = 0; i < deadBodyArray->max_length; i++)
		deadBodies.push_back(deadBodyArray->vector[i]);

	return deadBodies;
}

std::vector<GameData_TaskInfo*> GetPlayerInfoTasks(GameData_PlayerInfo* playerInfo) {
	static GameData_TaskInfo* (*getItem)(List_1_GameData_TaskInfo_*, int32_t, MethodInfo*);
	static int32_t(*getCount)(List_1_GameData_TaskInfo_*, MethodInfo*);
	if (getItem == NULL) getItem = decltype(getItem)(find_method((Il2CppClass*)(Il2CppClass*)playerInfo->fields.Tasks->klass, "GameData.TaskInfo", "get_Item", "System.Int32"));
	if (getCount == NULL) getCount = decltype(getCount)(find_method((Il2CppClass*)(Il2CppClass*)playerInfo->fields.Tasks->klass, "System.Int32", "get_Count", ""));

	auto tasks = std::vector<GameData_TaskInfo*>();
	 
	if (getItem != NULL && getCount != NULL)
		for (int i = 0; i < getCount(playerInfo->fields.Tasks, NULL); i++)
			tasks.push_back(getItem(playerInfo->fields.Tasks, i, NULL));

	return tasks;
}

std::vector<NormalPlayerTask*> GetPlayerTasks(PlayerControl* player) {
	static PlayerTask* (*getItem)(List_1_PlayerTask_*, int32_t, MethodInfo*);
	static int32_t(*getCount)(List_1_PlayerTask_*, MethodInfo*);
	static std::string normalPlayerTask;
	if (getItem == NULL) getItem = decltype(getItem)(find_method((Il2CppClass*)(Il2CppClass*)player->fields.myTasks->klass, "PlayerTask", "get_Item", "System.Int32"));
	if (getCount == NULL) getCount = decltype(getCount)(find_method((Il2CppClass*)(Il2CppClass*)player->fields.myTasks->klass, "System.Int32", "get_Count", ""));
	if (normalPlayerTask.empty()) normalPlayerTask = translate_type_name("NormalPlayerTask");

	std::vector<PlayerTask*> playerTasks = std::vector<PlayerTask*>();
	std::vector<NormalPlayerTask*> normalPlayerTasks = std::vector<NormalPlayerTask*>();

	if (getItem != NULL && getCount != NULL)
		for (int i = 0; i < getCount(player->fields.myTasks, NULL); i++)
			playerTasks.push_back(getItem(player->fields.myTasks, i, NULL));

	for (auto playerTask : playerTasks)
		if (strcmp(playerTask->klass->_0.name, normalPlayerTask.c_str()) == 0 || strcmp(playerTask->klass->_0.parent->name, normalPlayerTask.c_str()) == 0)
			normalPlayerTasks.push_back((NormalPlayerTask*)playerTask);

	return normalPlayerTasks;
}

void CompleteTask(NormalPlayerTask* playerTask) {
	if (playerTask->fields._._Owner == (*Game::pLocalPlayer)) {
		while (playerTask->fields.taskStep < playerTask->fields.MaxStep)
			app::NormalPlayerTask_NextStep(playerTask, NULL);
	}
}

#pragma warning(suppress:26812)
const char* TranslateTaskTypes(TaskTypes__Enum taskType) {
	static const char* const TASK_TRANSLATIONS[] = { "Submit Scan", "Prime Shields", "Fuel Engines", "Chart Course", "Start Reactor", "Swipe Card", "Clear Asteroids", "Upload Data",
		"Inspect Sample", "Empty Chute", "Empty Garbage", "Align Engine Output", "Fix Wiring", "Calibrate Distributor", "Divert Power", "Unlock Manifolds", "Reset Reactor",
		"Fix Lights", "Clean O2 Filter", "Fix Communications", "Restore Oxygen", "Stabilize Steering", "Assemble Artifact", "Sort Samples", "Measure Weather", "Enter ID Code",
		"Buy Beverage", "Process Data", "Run Diagnostics", "Water Plants", "Monitor Oxygen", "Store Artifacts", "Fill Canisters", "Activate Weather Nodes", "Insert Keys",
		"Reset Seismic Stabilizers", "Scan Boarding Pass", "Open Waterways", "Replace Water Jug", "Repair Drill", "Align Telecopse", "Record Temperature", "Reboot Wifi" };
	return TASK_TRANSLATIONS[taskType];
}

#pragma warning(suppress:26812)
const char* TranslateSystemTypes(SystemTypes__Enum systemType) {
	static const char* const SYSTEM_TRANSLATIONS[] = { "Hallway", "Storage", "Cafeteria", "Reactor", "Upper Engine", "Navigation", "Admin", "Electrical", "Oxygen", "Shields",
		"MedBay", "Security", "Weapons", "Lower Engine", "Communications", "Ship Tasks", "Doors", "Sabotage", "Decontamination", "Launchpad", "Locker Room", "Laboratory",
		"Balcony", "Office", "Greenhouse", "Dropship", "Decontamination", "Outside", "Specimen Room", "Boiler Room" };
	return SYSTEM_TRANSLATIONS[systemType];
}

CorrectedColor32 GetPlayerColor(uint8_t colorId) {
	CorrectedColor32* colorArray = (CorrectedColor32*)app::Palette__TypeInfo->static_fields->PlayerColors->vector;
	return colorArray[colorId];
}

std::string getModulePath() {
	TCHAR buff[MAX_PATH];
	GetModuleFileName((HINSTANCE)&__ImageBase, buff, _countof(buff));
	std::wstring ws(buff);
	std::string path(ws.begin(), ws.end());
	return path.substr(0, path.find_last_of("\\")).append("\\");
}