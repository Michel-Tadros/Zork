#include <iostream>
#include "Weapon.h"

Weapon::Weapon(int damage, int value, std::string name, std::string description, ArsenalType type) : 
	Item(value, name, description, itemType = WEAPON)
{
	this->damage = damage;
	this->type = type;
}

Weapon::~Weapon(){}