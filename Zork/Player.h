#pragma once
#include <iostream>
#include "Creature.h"

enum PlayerType
{
	KNIGHT,
	MAGE,
};

class Player :public Creature
{
public:
	PlayerType playerType;
	Player(std::string name, std::string description, int health, int magic, int stamina, Room* location, PlayerType playerType);
	~Player();
};