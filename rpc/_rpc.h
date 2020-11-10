#pragma once
#include <cstdint>

class RPCInterface
{
public:
	virtual ~RPCInterface() {}
	virtual void Process() = 0;
};

class MurderRPC : public RPCInterface {
	uint8_t selectedPlayer;
	uint8_t targetedPlayer;
public:
	MurderRPC(uint8_t selectedPlayer, uint8_t targetedPlayer);
	virtual void Process() override;
};

class DoorRPC : public RPCInterface {
	SystemTypes__Enum selectedSystem;
	bool pinDoor;
public:
	DoorRPC(SystemTypes__Enum selectedSystem, bool pinDoor);
	virtual void Process() override;
};

class TeleportRPC : public RPCInterface {
	uint8_t selectedPlayer;
	Vector2 targetVector;
public:
	TeleportRPC(uint8_t selectedPlayer, Vector2 targetVector);
	virtual void Process() override;
};

class SabotageRPC : public RPCInterface {
	SystemTypes__Enum selectedSystem;
public:
	SabotageRPC(SystemTypes__Enum selectedSystem);
	virtual void Process() override;
};