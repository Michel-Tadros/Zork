#include <iostream>
#include <string>
#include "Potion.h"

Potion::Potion(PotionType type, int value, int restoreValue, std::string name, std::string description) :
	Item(value, name, description, itemType = POTION)
{
	this->type = type;
	this->restoreValue = restoreValue;
}

Potion::~Potion() {}