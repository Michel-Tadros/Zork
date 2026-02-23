#pragma once
#include <iostream>
#include "Entity.h"
#include <string>

// Item class represents the items that player can interact with, such as armor, weapon, potion, key and common items.

enum ItemType
{
	ARMOR,
	WEAPON,
	POTION,
	KEY,
	COMMON
};

enum ArsenalType
{
	PHYSICAL,
	MAGICAL,
	OTHER
};


class Item:public Entity
{
public:
	int value;
	ItemType itemType;
	ArsenalType arsenalType;

public:
	Item(int value, std::string name, std::string description, ItemType itemType);
	Item(int value, std::string name, std::string description, ItemType itemType, ArsenalType arsenalType);
	~Item();
};