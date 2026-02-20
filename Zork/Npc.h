#pragma once
#include <iostream>
#include "Creature.h"
#include <string>

enum NPCType
{
	HELPER,
	MERCHANT,
	HINTER
};

class Npc :public Creature
{
public:
	std::string dialogue;
	NPCType npcType;
	Npc(std::string name, std::string description, int health, int magic, int stamina, Room* location, std::string dialogue, NPCType npcType);
	~Npc();
};