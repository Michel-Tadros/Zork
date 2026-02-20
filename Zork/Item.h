#pragma once
#include<iostream>
#include "Entity.h"
#include <string>
#include<list>


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
	std::list<Item*> content;

public:
	Item(int value, int damage, int defense, std::string name, std::string description, ItemType itemType);
	~Item();
	
	void displayInfo();

};