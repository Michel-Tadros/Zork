#pragma once
#include <iostream>
#include "Item.h"


class Armor :public Item
{
public:
	int defense;
	ArsenalType type;
	Armor(int defense, int value, std::string name, std::string description, ArsenalType type);
	~Armor();
};