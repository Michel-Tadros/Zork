#include<iostream>
#include "Entity.h"
#include <string>

Entity::Entity(std::string name, std::string description)
{
	this->name = name;
	this->description = description;
	entityType = ENTITY;
}

Entity::~Entity() {}

void Entity::displayInfo()
{
	std::cout << name << std::endl;
	std::cout << description << std::endl;
}

void Entity::update(){}