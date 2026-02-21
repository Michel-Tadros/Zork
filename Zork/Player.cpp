#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Weapon.h"
#include "Armor.h"
#include "Player.h"

Player::Player(std::string name, std::string description, int health, int magic, int stamina, int gold, 
	Room* location, PlayerType playerType) : Creature(name, description, health, magic, stamina, gold, location)
{
	this->playerType = playerType;
}
Player::~Player() {}


void Player::displayInfo()
{
	std::cout << description << std::endl;
}

void Player::talkToNpc(Npc* npc)
{
	switch (npc->npcType)
	{
	case HELPER:
		if (npc->inventory.empty()) std::cout << "You can do it!" << std::endl;
		else 
		{
			std::cout << npc->dialogue << std::endl;
			std::cout << "You received " << npc->equippedItem->name << " from " << npc->name << "!" << std::endl;
			npc->removeItem(npc->equippedItem);
			this->addItem(npc->equippedItem);
			npc->unequipItem();
			break;
		}

		case HINTER:
			std::cout << npc->dialogue << std::endl;
			break;

		case MERCHANT:
			std::cout << npc->dialogue << std::endl;
			startTrade(npc);
			break;
	default:
		break;
	}
}

void Player::startTrade(Npc* npc)
{
	std::cout << "Trading with " << npc->name << "..." << std::endl;
	//check npc inventory and player inventory, then allow player to buy or sell items
	bool trade = true;
	while (trade) {
		std::cout << "Your Inventory: " << std::endl;
		inventoryInfo();
		std::cout << npc->name << "'s Inventory: " << std::endl;
		npc->inventoryInfo();
		std::cout << "Something caught your eyes?"<<std::endl;
		std::string input;
		std::getline(std::cin, input);
		std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
		std::string action;
		std::string product;
		std::istringstream iss(input);
		iss >> action;
		iss >> product;
		if (action == "exit") 
		{
			std::cout << "Thank you see you soon!" << std::endl;
			trade = false;
		}
		else if(input == "buy")
		{
			for (auto& item : npc->inventory)
			{
				if (item.first->name == product && item.second > 0)
				{
					if (this->gold >= item.first->value)
					{
						this->removeGold(item.first->value);
						npc->addGold(item.first->value);
						this->addItem(item.first);
						npc->removeItem(item.first);
						std::cout << "You bought " << item.first->name << " for " << item.first->value << " gold!" << std::endl;
					}
					else
					{
						std::cout << "You don't have enough gold to buy " << item.first->name << "!" << std::endl;
					}
					break;
				}
			}
		}
		else if (action == "sell")
		{
			for (auto& item : this->inventory)
			{
				if (item.first->name == product && item.second > 0)
				{
					this->addGold(item.first->value);
					npc->removeGold(item.first->value);
					this->removeItem(item.first);
					npc->addItem(item.first);
					std::cout << "You sold " << item.first->name << " for " << item.first->value << " gold!" << std::endl;
					break;
				}
			}

		}
	}
}

void Player::attackCreature(Creature* creature)
{
	if (creature->heatlh<=0)
	{
		std::cout << creature->name << " is already defeated!" << std::endl;
		return;
	}
	std::cout << creature->name << " has challenged you to a battle!" << std::endl;
	bool battle = true;

	while (battle)
	{
		std::cout << "What will you do?" << std::endl;
		std::cout << "> ";
		std::string input;
		std::getline(std::cin, input);
		//std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
		std::istringstream iss(input);
		std::string action;
		std::string next;
		std::string after;
		iss >> action;
		iss >> next;
		iss >> after;
		if (action == "stats") {
			this->statsInfo();
		}
		else if (action == "inventory") {
			this->inventoryInfo();
		}
		else if (action == "equip") {
			std::string target = next + " " + after;
			for (auto& item : this->inventory)
			{
				if (item.first->name == target && item.second > 0)
				{
					this->equipItem(item.first);
					break;
				}
			}
		}
		else if (action == "unequip") {
			this->unequipItem();
		}
		else if (action == "enemy" && next == "info")
		{
			creature->displayInfo();
		}

		else if (action == "attack") {
			int damage = 10; // if no weapon are equipped
			if (equippedItem != nullptr && equippedItem->itemType == WEAPON) {
				Weapon* weapon = dynamic_cast<Weapon*>(equippedItem);
				damage = weapon->damage;
				if(creature->equippedItem != nullptr && creature->equippedItem->itemType == ARMOR)
				{
					Armor* armor = dynamic_cast<Armor*>(creature->equippedItem);
					if (armor->type == weapon->type) damage -= armor->defense;
				}
			}
			creature->heatlh -= damage;
			std::cout << "You attacked " << creature->name << " for " << damage << " damage!" << std::endl;
			if (creature->heatlh <= 0) {
				std::cout << "You defeated " << creature->name << "!" << std::endl;
				this->lootCreature(creature);
				creature->removeCreature();
				battle = false;
			}
			else {
				int counterDamage = 5; // damage if creature has no weapon
				if (creature->equippedItem != nullptr && creature->equippedItem->itemType == WEAPON) {
					Weapon* weapon = dynamic_cast<Weapon*>(creature->equippedItem);
					counterDamage = weapon->damage;
					if(equippedItem != nullptr && this->equippedItem->itemType == ARMOR)
					{
						Armor* armor = dynamic_cast<Armor*>(this->equippedItem);
						if (armor->type == weapon->type) counterDamage -= armor->defense;
					}
				}
				this->heatlh -= counterDamage;
				std::cout << creature->name << " attacked you for " << counterDamage << " damage!" << std::endl;
				if (this->heatlh <= 0) {
					std::cout << "You were defeated by " << creature->name << "!" << std::endl;
					battle = false;
				}
			}
		}
		else if (action == "run")
		{
			std::cout << "You ran away from " << creature->name << "!" << std::endl;
			battle = false;
		}
		else {
			std::cout << "Invalid action. Please try again." << std::endl;
		}
	}	
}

void Player::showEquippedItem()
{
	if (equippedItem != nullptr)
	{
		std::cout <<"Equipped Item: " << equippedItem->name << std::endl;
	}
	else
	{
		std::cout <<"You have no item equipped." << std::endl;
	}
}

void Player::equipItem(Item* item)
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


void Player::unequipItem()
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