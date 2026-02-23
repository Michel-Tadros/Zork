#pragma once
#include <iostream>
#include "Item.h"

//Armor class represents the armor item that player can equip to protect themselves.
class Armor :public Item
{
public:
	int defense;
	Armor(int defense, int value, std::string name, std::string description, ArsenalType type);
	~Armor();
};