#pragma once

#include <iostream>
#include <string>
#include "Entity.h"

class Room:public Entity
{
public:
	int length;
	int width;
	Room(std::string name, std::string description, int length, int width);
	~Room();
};