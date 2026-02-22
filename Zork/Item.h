#pragma once
#include <iostream>
#include "Entity.h"
#include <string>

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