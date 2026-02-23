#pragma once

#include <iostream>
#include "Entity.h"
#include "Room.h"

// Exit class represents the connection between two rooms and whether that connection is locked or not.
class Exit :public Entity
{
public:
	Room* source;
	Room* destination;
	bool isLocked;
	Exit(std::string name, std::string description, bool isLocked,Room* source = nullptr, Room* destination = nullptr);
	~Exit();
};