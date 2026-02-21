#include <iostream>
#include <string>
#include "Exit.h"


Exit::Exit(std::string name, std::string description, bool isLocked, Room* source, Room* destination)
	: Entity(name, description)
{
	entityType = EXIT;
	this->source = source;
	this->destination = destination;
	this->isLocked = isLocked;
}

Exit::Exit(bool isLocked,Room* source, Room* destination) :
	Entity("Unnamed Exit", "An exit with no name or description.")
{
	entityType = EXIT;
	this->source = source;
	this->destination = destination;
	this->isLocked = isLocked;
}

Exit::~Exit(){}