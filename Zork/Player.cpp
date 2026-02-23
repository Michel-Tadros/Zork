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

//Talk to NPC.
void Player::talkToNpc(Npc* npc)
{
	switch (npc->npcType)
	{
	case HELPER:
		if (npc->isInventoryEmpty()) std::cout << "You can do it!" << std::endl;
		else 
		{
			Item* receivedItem = npc->inventory.begin()->first;
			std::cout << npc->dialogue << std::endl;
			std::cout << "You received " << receivedItem->name << " from " << npc->name << "!" << std::endl;
			this->addItem(receivedItem);
			npc->removeItem(receivedItem);
		}
		break;

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

//Initiate trade with NPC of type MERCHANT.
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
		//Buy from Merchant.
		else if(action == "buy")
		{
			bool available = false;
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
						available = true;
					}
					else
					{
						std::cout << "You don't have enough gold to buy " << item.first->name << "!" << std::endl;
						printLines();
						available = true;
					}
					break;
				}
			}
			if (!available) 
			{ 
				std::cout << "Sorry I don't have " << target << std::endl; 
				printLines();
			}
		}
		//Sell to Merchant.
		else if (action == "sell")
		{
			bool available = false;
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
						available = true;
						break;
					}
					else
					{
						std::cout << "Sorry I can't afford " << item.first->name << "!" << std::endl;
						printLines();
						available = true;
						break;
					}
				}
			}
			if (!available) {
				std::cout << "You don't have " << target << " in your inventory!" << std::endl;
				printLines();
			}
		}
		else
		{
			std::cout<<"I'm sorry what was that?" << std::endl;
			printLines();
		}
	}
}
//Initiate battle with Creature.
void Player::attackCreature(Creature* creature)
{
	if (creature->heatlh<=0)
	{
		std::cout << creature->name << " is already defeated!" << std::endl;
		return;
	}
	std::cout << creature->name << " has challenged you to a battle!" << std::endl;
	std::cout<<creature->name<<" is using " << creature->equippedItem->name << "!" << std::endl;
	bool battle = true;

	int creatureHealth = creature->heatlh;
	while (battle)
	{
		std::cout << "What will you do?" << std::endl;
		std::cout << "> ";
		std::string input;
		std::getline(std::cin, input);
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
		//Final boss extra dialogue.
		if (creature->name == "Thief King" && creature->heatlh <= creatureHealth/2)
		{
			std::cout << "Thief King: You are stronger than I expected! But that ring is mine!" << std::endl;
			std::cout << "Thief King has changed weapons!" << std::endl;
			std::cout << "Thief King is now using " << creature->otherWeapon->name << "!" << std::endl;
			creature->equipItem(creature->otherWeapon);
		}
		//Check player stats inventory equip and unequip item in battle.
		if (action == "stats") {
			this->statsInfo();
		}
		else if (action == "inventory") {
			this->inventoryInfo();
		}
		else if (action == "equip") {
			int count = 0;
			for (auto& item : this->inventory)
			{
				count++;
				if (item.first->name == target && item.second > 0)
				{
					this->equipItem(item.first);
					count--;
					break;
				}
			}
			if (count == this->inventory.size()) {
				std::cout << "You don't have " << target << " in your inventory!" << std::endl;
				printLines();
			}
		}
		else if (action == "unequip") {
			this->unequipItem();
		}
		//Check enemy stats and info in battle.
		else if (action == "enemy" && target == "info")
		{
			creature->displayInfo();
		}
		//Drink potion in battle.
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
					count--;
					printLines();
					break;
				}
			}
			if (count == this->inventory.size()) {
				std::cout << "You don't have " << target << " in your inventory!" << std::endl;
				printLines();
			}
		}
		//Player and Creature perform an attack and damage is based on weapon and/or armor equipped.
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
		//End battle.
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
//Show currently equipped weapon
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

//Equip new item
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
//Check if item is in inventory.
bool Player::isItemInInvetory(Item* item)
{
	for (auto& it : inventory)
	{
		if (it.first == item && it.second > 0)
			return true;
	}
	return false;
	
}
//Unequip item.
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
//Calculate Player attack damage and stamina or magic consumption.
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
//Calculate Player defense and stamina or magic consumption.
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
//Pick item from Room and add to inventory.
void Player::pickItem(Item* item)
{
	for (auto& entity : this->location->container)
	{
		if (entity == item && entity->entityType == ITEM)
		{
			std::cout << "You picked up " << item->name << "!" << std::endl;
			this->addItem(item);
			auto elem = std::find(this->location->container.begin(), this->location->container.end(), item);
			if (elem != this->location->container.end()) {
				this->location->container.erase(elem);
			}
			return;
		}
	}
}
//Discard item from inventory. Item cannot be picked up again.
void Player::dropItem(Item* item)
{
	if (inventory[item] > 0)
	{
		std::cout << "You dropped " << item->name << "!" << std::endl;
		this->removeItem(item);
		this->location->container.push_back(item);
	}
}