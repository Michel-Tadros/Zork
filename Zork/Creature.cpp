#include<iostream>
#include<string>
#include "Creature.h"


Creature::Creature(std::string name, std::string description, int health, int magic, int stamina,int gold, Room* location) : 
	Entity(name, description)
{
	entityType = CREATURE;
	this->heatlh = health;
	this->magic = magic;
	this->gold = gold;
	this->stamina = stamina;
	this->location = location;
}
Creature::~Creature() {}