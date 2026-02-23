#pragma once

#include <iostream>
#include "Item.h"

// Weapon class represents the weapon item that player can equip to attack creatures.

class Weapon :public Item
{
	public:
	int damage;
	Weapon(int damage, int value, std::string name, std::string description, ArsenalType type);
	~Weapon();
};