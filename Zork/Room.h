#pragma once

#include <iostream>
#include <string>
#include "Entity.h"

//Room class represents the location that player can explore in the game. Each room has its own description, exits, items and creatures.

class Room:public Entity
{
public:
	int length;
	int width;
	Room(std::string name, std::string description, int length, int width);
	~Room();
};