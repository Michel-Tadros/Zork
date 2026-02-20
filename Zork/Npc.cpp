#include <iostream>
#include "Npc.h"

Npc::Npc(std::string name, std::string description, int health, int magic, int stamina, Room* location, 
	std::string dialogue, NPCType npcType) : Creature(name, description, health, magic, stamina, location)
{
	entityType = CREATURE;
	this->dialogue = dialogue;
	this->npcType = npcType;
}

Npc::~Npc(){}