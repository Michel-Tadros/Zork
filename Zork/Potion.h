#pragma once
#include <iostream>
#include <string>
#include "Item.h"

// Potion class represents the potion item that player can use to restore health, magic or stamina.

enum PotionType
{
	HEATLTH,
	MAGIC,
	STAMINA
};

class Potion : public Item
{
public:
	PotionType type;
	int restoreValue;
	Potion(PotionType type, int value, int restoreValue, std::string name, std::string description);
	~Potion();
};