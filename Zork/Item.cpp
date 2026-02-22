#include<iostream>
#include "Item.h"
#include <list>

Item::Item(int value, std::string name, std::string description, ItemType itemType) :
	Entity(name, description)
{
	entityType = ITEM;
	this->value = value;
	this->itemType = itemType;
	arsenalType = OTHER;
}

Item::Item(int value, std::string name, std::string description, ItemType itemType, ArsenalType arsenalType) : 
	Entity(name, description)
{
	entityType = ITEM;
	this->value = value;
	this->itemType = itemType;
	this->arsenalType = arsenalType;
}

Item::~Item(){}