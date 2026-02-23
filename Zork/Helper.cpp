#include "Helper.h"

void printLines()
{
	std::cout << "----------------------------------------------------------------" << std::endl;
}

void printStars()
{
	std::cout << "********************************************************" << std::endl;
}

//Logic when user inputs 1 word.
void oneWordCommands(Player* player, const std::string& cmd)
{
	//Move player up, down, left or right in the room.
	if (cmd == "up" || cmd == "north")
	{
		player->moveUp();
		printLines();
	}
	else if (cmd == "down" || cmd == "south")
	{
		player->moveDown();
		printLines();
	}
	else if (cmd == "left" || cmd == "west")
	{
		player->moveLeft();
		printLines();
	}
	else if (cmd == "right" || cmd == "east")
	{
		player->moveRight();
		printLines();
	}
	//Check stats and info
	else if (cmd == "stats")
	{
		player->statsInfo();
		printLines();
	}
	else if (cmd == "inventory")
	{
		player->inventoryInfo();
		printLines();
	}
	//List all entities in the room.
	else if (cmd == "look")
	{
		player->inTheRoom();
		printLines();
	}
	//Check equipped item.
	else if (cmd == "equipped")
	{
		player->showEquippedItem();
		printLines();
	}
	else
	{
		std::cout << "Invalid command!" << std::endl;
		printLines();
	}
}

//Logic when user inputs 2 words.
void twoWordsCommands(Player* player, const std::string& cmd1, const std::string& cmd2)
{
	//Talk to NPC and performing action depending on NPC type.
	if (cmd1 == "talk")
	{
		for (auto& entity : player->location->container)
		{
			if (entity->name == cmd2 && entity->entityType == CREATURE)
			{
				Npc* npc = dynamic_cast<Npc*>(entity);
				if (npc != nullptr && npc->entityType == CREATURE)
				{
					player->talkToNpc(npc);
					printLines();
					return;
				}
			}
		}
		std::cout << "There is no " << cmd2 << " to talk to!" << std::endl;
		printLines();
	}
	//Initiate battle with creature.
	else if (cmd1 == "attack")
	{
		for (auto& entity : player->location->container)
		{
			if (entity->name == cmd2 && entity->entityType == CREATURE)
			{
				Creature* creature = dynamic_cast<Creature*>(entity);
				if (creature != nullptr && creature->entityType == CREATURE)
				{
					player->attackCreature(creature);
					printLines();
					return;
				}
			}
		}
		std::cout << "There is no " << cmd2 << " to attack!" << std::endl;
		printLines();
	}
	//Go to next room
	else if (cmd1 == "go")
	{
		for (auto& entity : player->location->container)
		{
			if (entity->name == cmd2 && entity->entityType == EXIT)
			{
				Exit* exit = dynamic_cast<Exit*>(entity);
				if (exit != nullptr && exit->entityType == EXIT)
				{
					player->exitRoom(exit);
					printLines();
					return;
				}
			}
		}
		std::cout << "There is no exit named " << cmd2 << "!" << std::endl;
		printLines();
	}

	//Equip new item.
	else if (cmd1 == "equip")
	{
		for (auto& item : player->inventory)
		{
			if (item.first->name == cmd2 && item.second > 0)
			{
				player->equipItem(item.first);
				printLines();
				return;
			}
		}
		std::cout << "You don't have " << cmd2 << " in your inventory!" << std::endl;
		printLines();
	}

	//Loot chests.
	else if (cmd1 == "open"){
		for (auto& entity : player->location->container)
		{
			if (entity->name == cmd2 && entity->entityType == CHEST)
			{
				Creature* chest = dynamic_cast<Creature*>(entity);
				if (chest != nullptr && chest->entityType == CHEST)
				{
					player->lootCreature(chest);
					printLines();
					return;
				}
			}
		}
		std::cout << "You can't loot " << cmd2 << "!" << std::endl;
		printLines();
	}

	//Pick item in room.
	else if (cmd1 == "pick")
	{
		for (auto& entity : player->location->container)
		{
			if (entity->name == cmd2 && entity->entityType == ITEM)
			{
				Item* item = dynamic_cast<Item*>(entity);
				if (item != nullptr && item->itemType == COMMON)
				{
					player->pickItem(item);
					printLines();
					return;
				}
			}
		}
		std::cout << "There is no " << cmd2 << " to pick up!" << std::endl;
		printLines();
	}

	//Drop item. Item cannot be picked up again.
	else if (cmd1 == "drop")
	{
		for (auto& item : player->inventory)
		{
			if (item.first->name == cmd2 && item.second > 0)
			{
				player->dropItem(item.first);
				printLines();
				return;
			}
		}
		std::cout << "You don't have " << cmd2 << " in your inventory!" << std::endl;
		printLines();
	}

	else
	{
		std::cout << "Invalid command!" << std::endl;
		printLines();
		
	}
}

//Logic when user inputs 3 words.
void threeWordsCommands(Player* player, const std::string& cmd1, const std::string& cmd2, const std::string& cmd3)
{
	//Drink potion.s
	std::string target = cmd2 + " " + cmd3;
	if (cmd1 == "drink")
	{
		for (auto& item : player->inventory)
		{
			if (item.first->name == target && item.second > 0 && item.first->itemType == POTION)
			{
				Potion* potion = dynamic_cast<Potion*>(item.first);
				player->drinkPotion(potion);
				printLines();
				return;
			}
		}
		std::cout << "You don't have " << cmd2 << " in your inventory!" << std::endl;
		printLines();
	}
	else if (cmd1 == "use")
	{
		//Open locked exit with corresponding key.
		for (auto& item : player->inventory)
		{
			if (item.first->name == target && item.second > 0 && item.first->itemType == KEY)
			{
				Key* key = dynamic_cast<Key*>(item.first);
				for (auto& entity : player->location->container)
				{
					if (entity->entityType == EXIT)
					{
						Exit* exit = dynamic_cast<Exit*>(entity);
						if (exit != nullptr && exit->isLocked)
						{
							player->openLockedDoor(key, exit);
							printLines();
							return;
						}
					}
				}
				printLines();
				return;
			}
		}
		std::cout << "You don't have " << cmd2 << " in your inventory!" << std::endl;
		printLines();
	}
	//Initiate battle with creature.
	else if (cmd1 == "attack")
	{
		for (auto& entity : player->location->container)
		{
			if (entity->name == target && entity->entityType == CREATURE)
			{
				Creature* creature = dynamic_cast<Creature*>(entity);
				if (creature != nullptr && creature->entityType == CREATURE)
				{
					player->attackCreature(creature);
					printLines();
					return;
				}
			}
		}
	}
	//Equip item.
	else if (cmd1 == "equip")
	{
		for (auto& item : player->inventory)
		{
			if (item.first->name == target && item.second > 0)
			{
				player->equipItem(item.first);
				printLines();
				return;
			}
		}
		std::cout << "You don't have " << target << " in your inventory!" << std::endl;
		printLines();
	}
	//Pick item in room.
	else if (cmd1 == "pick")
	{
		for (auto& entity : player->location->container)
		{
			if (entity->name == target && entity->entityType == ITEM)
			{
				Item* item = dynamic_cast<Item*>(entity);
				if (item != nullptr && item->itemType == COMMON)
				{
					player->pickItem(item);
					printLines();
					return;
				}
			}
		}
		std::cout << "There is no " << target << " to pick up!" << std::endl;
		printLines();
	}
	//Drop item. Item cannot be picked up again.
	else if (cmd1 == "drop")
	{
		for (auto& item : player->inventory)
		{
			if (item.first->name == target && item.second > 0)
			{
				player->dropItem(item.first);
				printLines();
				return;
			}
		}
		std::cout << "You don't have " << target << " in your inventory!" << std::endl;
		printLines();
	}
	//Talk to NPC and performing action depending on NPC type.
	else if (cmd1 == "talk")
	{
		for (auto& entity : player->location->container)
		{
			if (entity->name == target && entity->entityType == CREATURE)
			{
				Npc* npc = dynamic_cast<Npc*>(entity);
				if (npc != nullptr && npc->entityType == CREATURE)
				{
					player->talkToNpc(npc);
					printLines();
					return;
				}
			}
		}
		std::cout << "There is no " << target << " to talk to!" << std::endl;
		printLines();
	}
	//Go to next room if exit is unlocked.
	else if (cmd1 == "go")
	{
		for (auto& entity : player->location->container)
		{
			if (entity->name == target && entity->entityType == EXIT)
			{
				Exit* exit = dynamic_cast<Exit*>(entity);
				if (exit != nullptr && exit->entityType == EXIT)
				{
					player->exitRoom(exit);
					printLines();
					return;
				}
			}
		}
		std::cout << "There is no exit named " << target << "!" << std::endl;
		printLines();
	}
	else
	{
		std::cout << "Invalid command!" << std::endl;
		printLines();
	}
}