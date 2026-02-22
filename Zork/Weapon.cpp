#include <iostream>
#include "Weapon.h"

Weapon::Weapon(int damage, int value, std::string name, std::string description, ArsenalType arsType) : 
	Item(value, name, description, itemType = WEAPON, arsType)
{
	this->damage = damage;
}

Weapon::~Weapon(){}