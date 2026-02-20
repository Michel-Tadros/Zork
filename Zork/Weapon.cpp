#include <iostream>
#include "Weapon.h"

Weapon::Weapon(int damage, int value, std::string name, std::string description, WeaponType type) : 
	Item(value, name, description)
{
	this->damage = damage;
	this->type = type;
}

Weapon::~Weapon(){}