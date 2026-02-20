#pragma once

#include <iostream>
#include "Entity.h"
#include "Room.h"

enum Direction
{
	UP,
	DOWN, 
	LEFT,
	RIGHT
};

class Exit :public Entity
{
public:
	Room* source;
	Room* destination;
	Direction direction;
	Exit(std::string name, std::string description, Room* source=nullptr, Room* destination=nullptr, Direction direction);
	~Exit();
};