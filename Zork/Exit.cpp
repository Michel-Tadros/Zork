#include <iostream>
#include <string>
#include "Exit.h"


Exit::Exit(std::string name, std::string description, Room* source, Room* destination, Direction direction)
	: Entity(name, description)
{
	entityType = EXIT;
	source = source;
	destination = destination;
	direction = direction;
}

Exit::~Exit(){}