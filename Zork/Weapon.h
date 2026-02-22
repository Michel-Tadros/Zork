#pragma once

#include <iostream>
#include "Item.h"


class Weapon :public Item
{
	public:
	int damage;
	Weapon(int damage, int value, std::string name, std::string description, ArsenalType type);
	~Weapon();
};