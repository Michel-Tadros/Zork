#pragma once
#include <iostream>
#include "Entity.h"
#include "Room.h"
#include "Item.h"
#include <string>
#include <vector>

class Creature :public Entity
{
public:
	int heatlh;
	int magic;
	int stamina;
	Room* location;
	std::vector<Item*> inventory;

	Creature(std::string name, std::string description, int health, int magic, int stamina, Room* location);
	~Creature();
};
