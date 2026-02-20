#pragma once
#include <iostream>
#include "Item.h"

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
	Potion(PotionType type, int value, std::string name, std::string description);
	~Potion();
};