#include<iostream>
#include<string>
#include "Creature.h"


Creature::Creature(std::string name, std::string description, int health, int magic, int stamina,int gold, Room* location) : 
	Entity(name, description)
{
	entityType = CREATURE;
	this->heatlh = health;
	this->magic = magic;
	this->gold = gold;
	this->stamina = stamina;
	this->location = location;
	this->equippedItem = nullptr;
}
Creature::~Creature() {}

void Creature::statsInfo()
{
	std::cout << "Health: " << heatlh << std::endl;
	std::cout << "Magic: " << magic << std::endl;
	std::cout << "Stamina: " << stamina << std::endl;
}

void Creature::inventoryInfo()
{
	std::cout << "Gold: " << gold << std::endl;
	std::cout << "Inventory: " << std::endl;
	for (auto& item : inventory)
	{
		if (item.second > 0)
		std::cout << item.first->name << " x" << item.second << std::endl;
	}
}

void Creature::addGold(int amount)
{
	this->gold += amount;
}

void Creature::removeGold(int amount)
{
	if (this->gold >= amount)
		this->gold -= amount;
}

void Creature::addItem(Item* item)
{
	this->inventory[item]++;
}

void Creature::removeItem(Item* item)
{
	if (this->inventory[item] > 0)
		this->inventory[item]--;
}

void Creature::equipItem(Item* item)
{
	if (item->itemType == ARMOR || item->itemType == WEAPON) {
		if (inventory[item] > 0)
		{
			equippedItem = item;
			std::cout << "Equipped " << item->name << std::endl;
		}
		else
		{
			std::cout << "You don't have " << item->name << " in your inventory." << std::endl;
		}
	}
	else
	{
		std::cout << "You can't equip " << item->name << "!" << std::endl;
	}
}


void Creature::unequipItem()
{
	if (equippedItem != nullptr)
	{
		std::cout << "Unequipped " << equippedItem->name << std::endl;
		equippedItem = nullptr;
	}
	else
	{
		std::cout << "No item is currently equipped." << std::endl;
	}
}

void Creature::drinkPotion(Potion* potion)
{
	if (inventory[potion] > 0)
	{
		switch (potion->type)
		{
			case HEATLTH:
				heatlh += potion->restoreValue;
				break;
			case MAGIC:
				magic += potion->restoreValue;
				break;
			case STAMINA:
				stamina += potion->restoreValue;
				break;
			default:
			break;
		}
		removeItem(potion);
		std::cout << "You drank " << potion->name <<"!"<< std::endl;
	}
	else
	{
		std::cout << "You don't have " << potion->name << " in your inventory!" << std::endl;
	}
}

void Creature::moveUp()
{
	if(location->width > postionY + 1)
		postionY++;
	else
	{
		std::cout << "You can't go there." << std::endl;
	}
}

void Creature::moveDown()
{
	if (postionY - 1 >= 0)
		postionY--;
	else
	{
		std::cout << "You can't go there." << std::endl;
	}
}

void Creature::moveLeft()
{
	if (postionX - 1 >= 0)
		postionX--;
	else
	{
		std::cout << "You can't go there." << std::endl;
	}
}

void Creature::moveRight()
{
	if (location->width > postionX + 1)
		postionX++;
	else
	{
		std::cout << "You can't go there." << std::endl;
	}
}

void Creature::inTheRoom()
{
	std::cout << "You see in this room: " << std::endl;
	for (auto& entity : location->container)
	{
		if (entity != this)
			std::cout << entity->name << std::endl;
	}
}

void Creature::exitRoom(Exit* exit)
{
	if(this->location == exit->source)
	{
		if (!exit->isLocked)
		{
			this->location = exit->destination;
			postionX = 0;
			postionY = 0;
			std::cout << "You have entered " << location->name << "!" << std::endl;
			inTheRoom();
		}
		else
		{
			std::cout << "The exit is locked." << std::endl;
		}
	}
	else
	{
		std::cout << "You are not currently in this room." << std::endl;
	}
}

void Creature::lootCreature(Creature* creature)
{
	for (auto& item : creature->inventory)
	{
		if (item.second > 0)
		{
			this->addItem(item.first);
			creature->removeItem(item.first);
			std::cout << "You acquired " << item.first->name << " from " << creature->name << "!" << std::endl;
		}
	}
	if (creature->gold > 0) 
	{
		this->addGold(creature->gold);
		creature->removeGold(creature->gold);
		std::cout << "You gained " << creature->gold << " gold from " << creature->name << "!" << std::endl;
	}
}