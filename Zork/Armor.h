#pragma once
#include <iostream>
#include "Item.h"

enum ArmorType
{
	PHYSICAL,
	MAGICAL
};

class Armor :public Item
{
public:
	int defense;
	ArmorType type;
	Armor(int defense, int value, std::string name, std::string description, ArmorType type);
	~Armor();
};