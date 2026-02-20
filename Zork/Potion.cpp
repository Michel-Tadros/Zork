#include <iostream>
#include "Potion.h"

Potion::Potion(PotionType type, int value, std::string name, std::string description) :
	Item(value, name, description)
{
	this->type = type;
}

Potion::~Potion() {}