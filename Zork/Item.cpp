#include<iostream>
#include "Item.h"
#include <list>

Item::Item(int value, int damage, int defense, std::string name, std::string description, ItemType itemType) : 
	Entity(name, description)
{
	entityType = ITEM;
	this->value = value;
	this->damage = damage;
	this->defense = defense;
	this->itemType = itemType;
}

Item::~Item(){}


void Item::displayInfo(){
	Entity::displayInfo();
}