#include<iostream>
#include "Item.h"
#include <list>

Item::Item(int value, std::string name, std::string description) : 
	Entity(name, description)
{
	entityType = ITEM;
	this->value = value;
}

Item::~Item(){}