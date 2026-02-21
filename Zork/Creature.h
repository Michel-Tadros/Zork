#pragma once
#include <iostream>
#include "Entity.h"
#include "Room.h"
#include "Item.h"
#include "Potion.h"
#include "Exit.h"
#include "Key.h"
#include <string>
#include <map>

class Creature :public Entity
{
public:
	int heatlh;
	int magic;
	int stamina;
	int gold;
	int postionX = 0;
	int postionY = 0;
	Room* location;
	Item* equippedItem;
	std::map<Item*, int> inventory;

	Creature(std::string name, std::string description, int health, int magic, int stamina, int gold, Room* location);
	~Creature();
	void statsInfo();
	void inventoryInfo();
	void addGold(int amount);
	void removeGold(int amount);
	void addItem(Item* item);
	void removeItem(Item* item);
	bool isInventoryEmpty();
	virtual void equipItem(Item* item);
	virtual void unequipItem();
	void drinkPotion(Potion* potion);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void inTheRoom();
	void exitRoom(Exit* exit);
	void lootCreature(Creature* creature);
	void removeCreature();
	void openLockedDoor(Key* key, Exit* exit);
};
