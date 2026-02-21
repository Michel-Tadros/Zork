#pragma once
#include <iostream>
#include "Creature.h"
#include "Npc.h"

enum PlayerType
{
	KNIGHT,
	MAGE,
};

class Player :public Creature
{
public:
	PlayerType playerType;
	Player(std::string name, std::string description, int health, int magic, int stamina, int gold, Room* location, PlayerType playerType);
	~Player();
	void talkToNpc(Npc* npc);
	void startTrade(Npc* npc);
	void attackCreature(Creature* creature);
	virtual void equipItem(Item* Item);
	virtual void unequipItem();
	void itemEquipped();
};