#include <iostream>
#include "Armor.h"

Armor::Armor(int defense, int value, std::string name, std::string description, ArmorType type) : 
	Item(value, name, description)
{
	this->defense = defense;
	this->type = type;
}
Armor::~Armor() {}