#include<iostream>
#include "Room.h"

Room::Room(std::string name, std::string description, int length, int width) : Entity(name, description)
{
	entityType = ROOM;
	this->length = length;
	this->width = width;
}

Room::~Room(){}