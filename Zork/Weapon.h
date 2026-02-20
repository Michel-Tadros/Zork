#pragma once

#include <iostream>
#include "Item.h"

enum WeaponType
{
	PHYSICAL,
	MAGICAL
};

class Weapon :public Item
{
	public:
	int damage;
	WeaponType type;
	Weapon(int damage, int value, std::string name, std::string description, WeaponType type);
	~Weapon();
};