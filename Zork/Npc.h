#pragma once
#include <iostream>
#include "Creature.h"
#include <string>

/** Npc class represents the non-player characters that player can interact with.
*Helper: provides items to the player.
*Merchant: trade items with the player.
*Hinter: gives information to the player.
*/

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
	Npc(std::string name, std::string description, int health, int magic, int stamina, int gold, Room* location, std::string dialogue, NPCType npcType);
	~Npc();
};