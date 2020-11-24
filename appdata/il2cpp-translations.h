#pragma once
#include <vector>
#include <string>

struct KLASS {
	std::string namespaze;
	std::string klass_name;

	size_t contains_type(std::string type_input) {
		size_t position;

		if ((position = type_input.find(klass_name, 0)) != std::string::npos)
			return klass_name.length();

		return 0;
	}

	friend bool operator==(const KLASS& lhs, const KLASS& rhs) {
		return (lhs.namespaze.compare(rhs.namespaze) == 0 && lhs.klass_name.compare(rhs.klass_name) == 0);
	}
};

struct KLASS_PAIR {
	KLASS deobfuscated_klass;
	KLASS obfuscated_klass;
};

const std::vector<KLASS_PAIR> KLASS_TRANSLATIONS = {
	{ {"", "AmongUsClient"}, {"", "NJGFKJNAEMN"} },
	{ {"", "AutoOpenDoor"}, {"", "OJCFOBDOAEC"} },
	{ {"", "ChatBubble"}, {"", "HKJFCJOBLAI"} },
	{ {"", "ChatController"}, {"", "KLDOCKJFNJL"} },
	{ {"", "CustomNetworkTransform"}, {"", "MOLMNEIJOFA"} },
	{ {"", "DeadBody"}, {"", "GOMCPALKOAA"} },
	{ {"", "ElectricTask"}, {"", "PFFLFOHGJBJ"} },
	{ {"", "GameData"}, {"", "CDJOAAHOKAO"} },
	{ {"", "GameData.PlayerInfo"}, {"", "CDJOAAHOKAO.EEMLMBDEDII"} },
	{ {"", "GameData.TaskInfo"}, {"", "CDJOAAHOKAO.AKLHIBOPPDA"} },
	{ {"", "GameOptionsData"}, {"", "AJLBJFPAMND"} },
	{ {"", "HatManager"}, {"", "HPGBJEBNEEJ"} },
	{ {"", "HqHudOverrideTask"}, {"", "NPILPHBNAIC"} },
	{ {"", "HudManager"}, {"", "CHADMJBBIGF"}},
	{ {"", "HudOverrideTask"}, {"", "OGOEIBLEPKK"} },
	{ {"", "ImportantTextTask"}, {"", "HDEJDMNEOHB"} },
	{ {"", "KeyboardJoystick"}, {"", "EMLKIPBCHLM"} },
	{ {"", "MapBehaviour"}, {"", "NDNOJIAFBNP"} },
	{ {"", "MeetingHud"}, {"", "ILMBELNBDMA"} },
	{ {"", "NoOxyTask"}, {"", "KNODDFDEECC"} },
	{ {"", "NormalPlayerTask"}, {"", "APBFLKENJIG"} },
	{ {"", "Palette"}, {"", "NKLLDECAPNO"} },
	{ {"", "PetBehaviour"}, {"", "FODGPCIOFDL"} },
	{ {"", "PlainDoor"}, {"", "IKMBDAGIBPO"} },
	{ {"", "PlayerControl"}, {"", "PPHGCHMFMLI"} },
	{ {"", "PlayerTask"}, {"", "DLIDGCFBEAL"} },
	{ {"", "ReactorTask"}, {"", "LJCHIMKJAMB"} },
	{ {"", "SabotageTask"}, {"", "ENABMDLKEDH"} },
	{ {"", "ShipStatus"}, {"", "FLBAJEHOPDP"} },
	{ {"", "SomeKindaDoor"}, {"", "DKCJBMHDHFJ"} },
	{ {"", "StatsManager"}, {"", "AEIJCGDOCPI"} },
	{ {"", "SystemTypes"}, {"", "KIFILPGIGAK"} },
	{ {"", "TextRenderer"}, {"", "EOPGIOHKIEC"} },
	{ {"", "Vent"}, {"", "CJLCLKCGOIO"} },
	{ {"InnerNet", "InnerNetClient"}, {"", "FIMOOCIGOAO"} },
	{ {"InnerNet", "InnerNetObject"}, {"", "PANNCEFNLMC"} },
};

const std::vector<std::pair<std::string, std::string>> METHOD_TRANSLATIONS = {
	{ "get_BanMinutesLeft", "NIGEMOAPPAC" },
	{ "get_AmBanned", "LOKCPGEEHON" },
	{ "get_BanPoints", "KCKBKOIELCG" },
	{ "Deserialize", "DLEKBBIGMDB" },
	{ "EnterVent", "AINJJDFHPML" },
	{ "ExitVent", "LJOCIBNMAGG" },
	{ "ReportDeadBody", "FDNNDOOPBKN" }
};