#pragma once
#include <vector>
#include <string>

struct KLASS {
	std::string namespaze;
	std::string klass_name;

	friend bool operator==(const KLASS& lhs, const KLASS& rhs) {
		return (lhs.namespaze.compare(rhs.namespaze) == 0 && lhs.klass_name.compare(rhs.klass_name) == 0);
	}
};

struct KLASS_PAIR {
	KLASS deobfuscated_klass;
	KLASS obfuscated_klass;
};

const std::vector<KLASS_PAIR> KLASS_TRANSLATIONS = {
	{ {"", "AmongUsClient"}, {"", "JNFEHNLGIFF"} },
	{ {"InnerNet", "InnerNetClient"}, {"", "DNAFMCDBMCI"} },
	{ {"", "AutoOpenDoor"}, {"", "DKLABMEOEGK"} },
	{ {"", "PlainDoor"}, {"", "EEPJNHOLGOO"} },
	{ {"", "SomeKindaDoor"}, {"", "EMHAIPHEIFC"} },
	{ {"", "ChatBubble"}, {"", "NLMPPBGEPNL"} },
	{ {"", "TextRenderer"}, {"", "FELHHOEBHMA"} },
	{ {"", "ChatController"}, {"", "MLINJDBIIEC"} },
	{ {"", "CustomNetworkTransform"}, {"", "HLNNOIPCILF"} },
	{ {"InnerNet", "InnerNetObject"}, {"", "PEIOEODMCCN"} },
	{ {"", "Deadbody"}, {"", "FIGNMAOINPA"} },
	{ {"", "GameData"}, {"", "BAGGGBBOHOH"} },
	{ {"", "PlayerControl"}, {"", "GLHCHLEDNBA"} },
	{ {"", "PlayerTask"}, {"", "LOBBAHDOFGE"} },
	{ {"", "HatManager"}, {"", "JCEGHLBFDKF"} }
};

const std::vector<std::pair<std::string, std::string>> METHOD_TRANSLATIONS = {
	{ "get_BanMinutesLeft", "NEAALMKPALO" },
	{ "get_AmBanned", "DNOKMILAMAE" },
	{ "get_BanPoints", "MGKFDDLCGIE" },
	{ "OnStartGame", "OOCKKGOMIEB" }
};

const std::vector<std::pair<std::string, std::string>> TYPE_TRANSLATIONS = {
	{ "GameData.PlayerInfo", "BAGGGBBOHOH.FGMBFCIIILC" },
	{ "GameData.TaskInfo", "BAGGGBBOHOH.ALLADIFCEHO" },
	{ "SystemTypes", "JBPEMAACAEP" },
	{ "PetBehaviour", "LMKHONEJHGP" },
	{ "MapBehaviour", "EFAGMLJDPOA" },
	{ "PlayerControl", "GLHCHLEDNBA" },
	{ "DeadBody", "FIGNMAOINPA" },
	{ "NormalPlayerTask", "NOMAHIKEKPJ" },
	{ "PlayerTask", "LOBBAHDOFGE" }
};