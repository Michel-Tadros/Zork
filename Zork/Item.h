#pragma once
#include<iostream>
#include "Entity.h"
#include <string>


enum ItemType
{
	GOLD,
	WEAPON,
	ARMOUR,
	POTION,
	CHEST,
	KEY
};

class Item:public Entity
{
public:
	int value;
	int damage;
	int defense;
	ItemType itemType;

public:
	Item(int value, int damage, int defense, std::string name, std::string description, ItemType itemType);
	~Item();
	
	Item* findInContainer(ItemType type);
	void addItem(Entity* item);
	void removeItem(Entity* item);
	void displayInfo();

};