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
};

enum ArsenalType
{
	PHYSICAL,
	MAGICAL
};


class Item:public Entity
{
public:
	int value;
	ItemType itemType;

public:
	Item(int value, std::string name, std::string description, ItemType itemType);
	~Item();
};