#include <iostream>
#include "Armor.h"

Armor::Armor(int defense, int value, std::string name, std::string description, ArsenalType type) : 
	Item(value, name, description, itemType = ARMOR)
{
	this->defense = defense;
	this->type = type;
}
Armor::~Armor() {}