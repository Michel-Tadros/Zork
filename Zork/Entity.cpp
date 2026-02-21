#include<iostream>
#include "Entity.h"
#include <string>
#include <list>

Entity::Entity(std::string name, std::string description)
{
	this->name = name;
	this->description = description;
	entityType = ENTITY;
}

Entity::~Entity() {}

void Entity::displayInfo()
{
	std::cout << name << ", " << description << std::endl;
}