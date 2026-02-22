#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Weapon.h"
#include "Armor.h"
#include "Player.h"
#include "Helper.h"

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
		if (npc->isInventoryEmpty()) std::cout << "You can do it!" << std::endl;
		else 
		{
			std::cout << npc->dialogue << std::endl;
			std::cout << "You received " << npc->equippedItem->name << " from " << npc->name << "!" << std::endl;
			npc->unequipItem();
			this->addItem(npc->equippedItem);
			npc->removeItem(npc->equippedItem);
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
	printLines();
	//check npc inventory and player inventory, then allow player to buy or sell items
	bool trade = true;
	while (trade) {
		std::cout << "Your Inventory: " << std::endl;
		inventoryInfo();
		printStars();
		std::cout << npc->name << "'s Inventory: " << std::endl;
		npc->inventoryInfo();
		printStars();
		std::cout << "Something caught your eyes?"<<std::endl;
		std::cout << "> ";
		std::string input;
		std::getline(std::cin, input);
		//std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
		std::string action;
		std::string product;
		std::string next;
		std::istringstream iss(input);
		iss >> action;
		iss >> product;
		iss >> next;
		std::string target;
		if (next.empty()) target = product;
		else target = product + " " + next;
		if (action == "exit") 
		{
			std::cout << "Thank you see you soon!" << std::endl;
			trade = false;
		}
		else if(action == "buy")
		{
			for (auto& item : npc->inventory)
			{
				if (item.first->name == target && item.second > 0)
				{
					if (this->gold >= item.first->value)
					{
						std::cout << "You bought " << item.first->name << " for " << item.first->value << " gold!" << std::endl;
						printLines();
						this->removeGold(item.first->value);
						npc->addGold(item.first->value);
						this->addItem(item.first);
						npc->removeItem(item.first);
					}
					else
					{
						std::cout << "You don't have enough gold to buy " << item.first->name << "!" << std::endl;
						printLines();
					}
					break;
				}
			}
		}
		else if (action == "sell")
		{
			for (auto& item : this->inventory)
			{
				if (item.first->name == target && item.second > 0)
				{
					if (npc->gold >= item.first->value)
					{
					std::cout << "You sold " << item.first->name << " for " << item.first->value << " gold!" << std::endl;
					printLines();
					this->addGold(item.first->value);
					npc->removeGold(item.first->value);
					this->removeItem(item.first);
					npc->addItem(item.first);
					break;
					}
					else
					{
						std::cout << "Sorry I can't afford " << item.first->name << "!" << std::endl;
						printLines();
						break;
					}
				}
			}

		}
		else
		{
			std::cout<<"I'm sorry what was that?" << std::endl;
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
		std::string target;
		if (after.empty()) target = next;
		else target = next + " " + after;
		if (action == "stats") {
			this->statsInfo();
		}
		else if (action == "inventory") {
			this->inventoryInfo();
		}
		else if (action == "equip") {
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
		else if (action == "enemy" && target == "info")
		{
			creature->displayInfo();
		}

		else if (action == "drink")
		{
			int count = 0;
			for (auto& item : this->inventory)
			{
				count++;
				if (item.first->name == target && item.second > 0 && item.first->itemType == POTION)
				{
					Potion* potion = dynamic_cast<Potion*>(item.first);
					this->drinkPotion(potion);
					printLines();
					break;
				}
			}
			if (count == this->inventory.size()) {
				std::cout << "You don't have " << target << " in your inventory!" << std::endl;
				printLines();
			}
		}

		else if (action == "attack") 
		{
			int playerDamage = this->attack();
			int playerDefense = this->defense();
			int enemyDamage = creature->attack();
			int enemyDefense = creature->defense();
			if (this->equippedItem != nullptr && creature->equippedItem != nullptr 
				&& this->equippedItem->arsenalType == creature->equippedItem->arsenalType)
			{
				playerDamage = std::max(0, playerDamage - enemyDefense);
				enemyDamage = std::max(0, enemyDamage - playerDefense);
			}
			
			creature->heatlh -= playerDamage;
			this->heatlh -= enemyDamage;
			std::cout << "You dealt " << playerDamage << " damage to " << creature->name << "!" << std::endl;
			std::cout << creature->name << " dealt " << enemyDamage << " damage to you!" << std::endl;
			if (creature->heatlh <= 0)
			{
				std::cout << "You defeated " << creature->name << "!" << std::endl;
				this->lootCreature(creature);
				creature->removeCreature();
				battle = false;
			}
			else if (this->heatlh <= 0)
			{
				std::cout << "You were defeated by " << creature->name << "!" << std::endl;
				battle = false;
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

int Player::attack()
{
	int damage = 5;
	if (equippedItem != nullptr && equippedItem->itemType == WEAPON) {
		Weapon* weapon = dynamic_cast<Weapon*>(equippedItem);
		if (weapon->arsenalType == PHYSICAL)
		{
			this->stamina -= 20;
			if (this->stamina < 0)
			{
				this->stamina = 0;
				std::cout << "You don't have enough stamina to use " << weapon->name << "!" << std::endl;
			}
			else damage = weapon->damage;
		}
		if (weapon->arsenalType == MAGICAL)
		{
			this->magic -= 20;
			if (this->magic < 0)
			{
				this->magic = 0;
				std::cout << "You don't have enough magic to use " << weapon->name << "!" << std::endl;
			}
			else damage = weapon->damage;
		}

	}
	return damage;
}

int Player::defense()
{
	int defense = 0;
	if (equippedItem != nullptr && equippedItem->itemType == ARMOR) {
		Armor* armor = dynamic_cast<Armor*>(equippedItem);
		if (armor->arsenalType == PHYSICAL)
		{
			this->stamina -= 10;
			if (this->stamina < 0)
			{
				this->stamina = 0;
				std::cout << "You don't have enough stamina to use " << armor->name << "!" << std::endl;

			}
			else defense = armor->defense;
		}
		if (armor->arsenalType == MAGICAL)
		{
			this->magic -= 10;
			if (this->magic < 0)
			{
				this->magic = 0;
				std::cout << "You don't have enough magic to use " << armor->name << "!" << std::endl;

			}
			else defense = armor->defense;
		}
	}
	return defense;
}

void Player::pickItem(Item* item)
{
	for (auto& entity : this->location->container)
	{
		if (entity == item && entity->entityType == ITEM)
		{
			std::cout << "You picked up " << item->name << "!" << std::endl;
			this->addItem(item);
			this->location->container.remove(entity);
			return;
		}
	}
}

void Player::dropItem(Item* item)
{
	if (inventory[item] > 0)
	{
		std::cout << "You dropped " << item->name << "!" << std::endl;
		this->removeItem(item);
		this->location->container.push_back(item);
	}
}