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
	{ {"", "AmongUsClient"}, {"", "JNFEHNLGIFF"} },
	{ {"", "AutoOpenDoor"}, {"", "DKLABMEOEGK"} },
	{ {"", "ChatBubble"}, {"", "NLMPPBGEPNL"} },
	{ {"", "ChatController"}, {"", "MLINJDBIIEC"} },
	{ {"", "CustomNetworkTransform"}, {"", "HLNNOIPCILF"} },
	{ {"", "DeadBody"}, {"", "FIGNMAOINPA"} },
	{ {"", "GameData"}, {"", "BAGGGBBOHOH"} },
	{ {"", "GameData.PlayerInfo"}, {"", "BAGGGBBOHOH.FGMBFCIIILC"} },
	{ {"", "GameData.TaskInfo"}, {"", "BAGGGBBOHOH.ALLADIFCEHO"} },
	{ {"", "GameOptionsData"}, {"", "OEFJGMAEENB"} },
	{ {"", "HatManager"}, {"", "JCEGHLBFDKF"} },
	{ {"", "KeyboardJoystick"}, {"", "IOCAEJCPCKG"} },
	{ {"", "MapBehaviour"}, {"", "EFAGMLJDPOA"} },
	{ {"", "MeetingHud"}, {"", "GPOHFPAIEMA"} },
	{ {"", "NormalPlayerTask"}, {"", "NOMAHIKEKPJ"} },
	{ {"", "Palette"}, {"", "KPNJLIGHOEI"} },
	{ {"", "PetBehaviour"}, {"", "LMKHONEJHGP"} },
	{ {"", "PlainDoor"}, {"", "EEPJNHOLGOO"} },
	{ {"", "PlayerControl"}, {"", "GLHCHLEDNBA"} },
	{ {"", "PlayerTask"}, {"", "LOBBAHDOFGE"} },
	{ {"", "ShipStatus"}, {"", "DAFPFFMKPJJ"} },
	{ {"", "SomeKindaDoor"}, {"", "EMHAIPHEIFC"} },
	{ {"", "StatsManager"}, {"", "PPNOJOGJGFL"} },
	{ {"", "SystemTypes"}, {"", "JBPEMAACAEP"} },
	{ {"", "TextRenderer"}, {"", "FELHHOEBHMA"} },
	{ {"", "Vent"}, {"", "FBDDMHFBCPD"} },
	{ {"", "HudManager"}, {"", "KLEKBPLEDOA"}},
	{ {"InnerNet", "InnerNetClient"}, {"", "DNAFMCDBMCI"} },
	{ {"InnerNet", "InnerNetObject"}, {"", "PEIOEODMCCN"} },
};

const std::vector<std::pair<std::string, std::string>> METHOD_TRANSLATIONS = {
	{ "get_BanMinutesLeft", "NEAALMKPALO" },
	{ "get_AmBanned", "DNOKMILAMAE" },
	{ "get_BanPoints", "MGKFDDLCGIE" }
};