#include<iostream>
#include<string>
#include "Creature.h"


Creature::Creature(std::string name, std::string description, int health, int magic, int stamina, Room* location) : 
	Entity(name, description)
{
	entityType = CREATURE;
	this->heatlh = health;
	this->magic = magic;
	this->stamina = stamina;
	this->location = location;
}
Creature::~Creature() {}