#include <iostream>
#include <string>
#include "Exit.h"


Exit::Exit(std::string name, std::string description, Room* source, Room* destination, Direction direction)
	: Entity(name, description)
{
	entityType = EXIT;
	this->source = source;
	this->destination = destination;
	this->direction = direction;
	this->isLocked = false;
}

Exit::~Exit(){}