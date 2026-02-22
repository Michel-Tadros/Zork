#include "Helper.h"

void printLines()
{
	std::cout << "----------------------------------------------------------------" << std::endl;
}

void printStars()
{
	std::cout << "********************************************************" << std::endl;
}

void oneWordCommands(Player* player, const std::string& cmd)
{
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
	else if (cmd == "look")
	{
		player->inTheRoom();
		printLines();
	}
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

void twoWordsCommands(Player* player, const std::string& cmd1, const std::string& cmd2)
{
	if (cmd1 == "talk")
	{
		for (auto& entity : player->location->container)
		{
			//check if cmd2 and player are in the same room, then check if cmd2 is an npc, then talk to npc
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
	else if (cmd1 == "loot"){
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

void threeWordsCommands(Player* player, const std::string& cmd1, const std::string& cmd2, const std::string& cmd3)
{
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

	else if (cmd1 == "talk")
	{
		for (auto& entity : player->location->container)
		{
			//check if cmd2 and player are in the same room, then check if cmd2 is an npc, then talk to npc
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

	else
	{
		std::cout << "Invalid command!" << std::endl;
		printLines();
	}
}