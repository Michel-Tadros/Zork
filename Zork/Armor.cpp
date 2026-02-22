#include <iostream>
#include "Armor.h"

Armor::Armor(int defense, int value, std::string name, std::string description, ArsenalType arsType) : 
	Item(value, name, description, itemType = ARMOR, arsType)
{
	this->defense = defense;
}
Armor::~Armor() {}