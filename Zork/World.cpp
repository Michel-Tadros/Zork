#include<iostream>
#include "Player.h"
#include "Npc.h"
#include "Weapon.h"
#include "Armor.h"
#include "Item.h"
#include "Exit.h"
#include "Key.h"
#include <vector>
#include<algorithm>
#include "World.h"

World::World()
{
	Room* room1 = new Room("House", "A small, humble house that holds your favorite memories.", 4, 4);
	Room* room2 = new Room("Forest", "The old forest, where adventures are born.", 7, 7);
	Room* room3 = new Room("Castle Plaza", "The shrouded castle, where the thief king and his followers live.", 8, 8);
	Room* room4 = new Room("Knights' training ground", "The thief king and his followers train", 6, 6);
	Room* room5 = new Room("Knight's headquarters", "The thief king's most powerful knight resides here.", 5, 5);
	Room* room6 = new Room("Mage's library", "The thief king and his followers create new powerful spells.", 6, 6);
	Room* room7 = new Room("Mage's headquarters", "The thief king most powerful mage resides here.", 5, 5);
	Room* room8 = new Room("Thief's king throne", "The thief king commands his forces from this throne.", 6, 6);

	roomsList.push_back(room1);
	roomsList.push_back(room2);
	roomsList.push_back(room3);
	roomsList.push_back(room4);
	roomsList.push_back(room5);
	roomsList.push_back(room6);
	roomsList.push_back(room7);
	roomsList.push_back(room8);

	Exit* house_forest = new Exit("Forest","",true, room1, room2);
	Exit* forest_house = new Exit("House","",false, room2, room1);
	Exit* forest_plaza = new Exit("Path","",false, room2, room3);
	Exit* exit3 = new Exit("Path","",false, room3, room4);
	Exit* exit4 = new Exit("Path","",false, room4, room5);
	Exit* exit5 = new Exit("Door","",true, room5, room8);
	Exit* exit6 = new Exit("Path","",false, room3, room6);
	Exit* exit7 = new Exit("Path","",false, room6, room7);
	Exit* exit8 = new Exit("Door","",true, room7, room8);

	/*entities.push_back(house_forest);
	entities.push_back(exit2);
	entities.push_back(exit3);
	entities.push_back(exit4);
	entities.push_back(exit5);
	entities.push_back(exit6);
	entities.push_back(exit7);
	entities.push_back(exit8);*/

	//Weapons
	Weapon* rustyDagger = new Weapon(10, 5, "Rusty Dagger", "A worn-out dagger that has seen better days.", PHYSICAL);
	Weapon* shortSword = new Weapon(12, 15, "Short Sword", "A common sword used in battle.", PHYSICAL);
	Weapon* knightSword = new Weapon(15, 20, "Knight Sword", "Sword forged for the knights of the kingdom.", PHYSICAL);
	Weapon* kingSword = new Weapon(20, 30, "King Sword", "The legendary sword of the king.", PHYSICAL);
	Weapon* fireBurst = new Weapon(10,15,"Fire Burst","A small burst of fire.", MAGICAL);
	Weapon* fireBall = new Weapon(15, 20, "Fire Ball", "A devastating ball of fire.", MAGICAL);
	Weapon* lightningStorm = new Weapon(20, 30, "Lightning Storm", "Only the most powerful mage can master this spell.", MAGICAL);
	
	//Armors
	Armor* shield = new Armor(15, 10, "Shield", "A sturdy shield offers protection from Physical attacks", PHYSICAL);
	Armor* magicShield = new Armor(15, 10, "Magic Shield", "Spell used to protect oneself from Magical attacks", MAGICAL);

	//Potions
	Potion* healthPotion = new Potion(HEATLTH, 5, 30, "Health", "Potion to restore health");
	Potion* magicPotion = new Potion(MAGIC, 5, 30, "Magic Potion", "Potion to restore magic");
	Potion* staminaPotion = new Potion(STAMINA, 5, 30, "Stamina Potion", "Potion to restore stamina");

	//Keys
	Key* houseKey = new Key(house_forest, 0, "House", "Key that opens your house door, leading to the forest.");
	Key* knightsToThroneKey = new Key(exit5, 0, "Throne Key", "Key that opens the throne room from the knights headquarters.");
	Key* magesToThroneKey = new Key(exit8, 0, "Throne Key", "Key that opens the throne room from the mages headquarters.");

	//Ring
	Item* familyRing = new Item(100, "Family Ring", "Family heirloom passed down from generation to generation", ARMOR);




	//Ennemies
	Creature* ennemySquire1 = new Creature("Thief Squire", "A squire of the thief king.", 40, 40, 60, 5, room1);
	Creature* ennemySquire2 = new Creature("Thief Squire", "A squire of the thief king.", 40, 40, 60, 5, room4);
	Creature* ennemySquire3 = new Creature("Thief Squire", "A squire of the thief king.", 40, 40, 60, 5, room4);
	Creature* ennemySquire4 = new Creature("Thief Squire", "A squire of the thief king.", 40, 40, 60, 5, room5);
	Creature* ennemyKnight = new Creature("Thief Knight", "A knight of the thief king and one of his most trusted companions.", 70, 40, 80, 10, room5);
	Creature* ennemyApprentice1 = new Creature("Thief Apprentice", "A magic apprentice of the thief king.", 40, 60, 40, 5, room2);
	Creature* ennemyApprentice2 = new Creature("Thief Apprentice", "A magic apprentice of the thief king.", 40, 60, 40, 5, room6);
	Creature* ennemyApprentice3 = new Creature("Thief Apprentice", "A magic apprentice of the thief king.", 40, 60, 40, 5, room6);
	Creature* ennemyApprentice4 = new Creature("Thief Apprentice", "A magic apprentice of the thief king.", 40, 60, 40, 5, room7);
	Creature* ennemyMage = new Creature("Thief Mage", "A mage of the thief king and one of his most trusted companions.", 70, 80, 40, 10, room7);
	Creature* ennemyKing = new Creature("Thief King", "The thief king, Powerful and Fearsome Leader.", 120, 100, 100, 50,room8);
	
	ennemySquire1->addItem(rustyDagger);
	ennemySquire1->equipItem(rustyDagger);
	ennemySquire1->addItem(houseKey);
	ennemyList.push_back(ennemySquire1);
	ennemySquire2->addItem(rustyDagger);
	ennemySquire2->equipItem(rustyDagger);
	ennemyList.push_back(ennemySquire2);
	ennemySquire3->addItem(rustyDagger);
	ennemySquire3->equipItem(rustyDagger);
	ennemyList.push_back(ennemySquire3);
	ennemySquire4->addItem(rustyDagger);
	ennemySquire4->equipItem(rustyDagger);
	ennemyList.push_back(ennemySquire4);

	ennemyApprentice1->addItem(fireBurst);
	ennemyApprentice1->equipItem(fireBurst);
	ennemyList.push_back(ennemyApprentice1);
	ennemyApprentice2->addItem(fireBurst);
	ennemyApprentice2->equipItem(fireBurst);
	ennemyList.push_back(ennemyApprentice2);
	ennemyApprentice3->addItem(fireBurst);
	ennemyApprentice3->equipItem(fireBurst);
	ennemyList.push_back(ennemyApprentice3);
	ennemyApprentice4->addItem(fireBurst);
	ennemyApprentice4->equipItem(fireBurst);
	ennemyList.push_back(ennemyApprentice4);

	ennemyKnight->addItem(knightSword);
	ennemyKnight->equipItem(knightSword);
	ennemyKnight->addItem(knightsToThroneKey);
	ennemyList.push_back(ennemyKnight);

	ennemyMage->addItem(fireBall);
	ennemyMage->equipItem(fireBall);
	ennemyMage->addItem(magesToThroneKey);
	ennemyList.push_back(ennemyMage);

	ennemyKing->addItem(kingSword);
	ennemyKing->equipItem(kingSword);
	ennemyKing->addItem(lightningStorm);
	ennemyKing->addItem(shield);
	ennemyKing->addItem(magicShield);
	ennemyKing->addItem(familyRing);
	ennemyList.push_back(ennemyKing);

	//NPCs
	Npc* hinter1 = new Npc("Villager", "A villager who can provide you with useful information.", 50, 30, 40, 10, room1, "The thief king has been terrorizing the kingdom for years. He resides in the castle and has many followers.", HINTER);
	Npc* hinter2 = new Npc("Knight", "A knight who can provide you with useful information.", 70, 40, 60, 20, room3, "The thief king's knights are powerful and dangerous. They train in the training ground. One of them holds the key to the king's throne.", HINTER);
	Npc* hinter3 = new Npc("Mage", "A mage who can provide you with useful information.", 50, 70, 30, 10, room3, "The thief king's mages are powerful and dangerous. They create new spells in the library. One of them holds the key to the king's throne.", HINTER);
	Npc* merchant = new Npc("Merchant", "A merchant who can sell you useful items.", 50, 30, 40, 10, room3, "Have a look at my wares.", MERCHANT);
	Npc* helper1 = new Npc("Helper", "A helpful NPC who can assist you in your quest.", 50, 30, 40, 10, room4, "Here take this shield.", HELPER);
	Npc* helper2 = new Npc("Helper", "A helpful NPC who can assist you in your quest.", 50, 30, 40, 10, room6, "Here take this potion.", HELPER);


	helper1->addItem(shield);
	helper1->equipItem(shield);

	//Chests
	Creature* chest1 = new Creature("Chest", "A chest that contains useful items.", 1000, 0, 0, 10, room1);
	chest1->addItem(familyRing);

	//Fill rooms with items and ennemies
	//room1
	room1->container.push_back(ennemySquire1);
	room1->container.push_back(helper1);
	room1->container.push_back(house_forest);
	room1->container.push_back(chest1);

	//room2
	room2->container.push_back(ennemyApprentice1);
	room2->container.push_back(forest_house);
	room2->container.push_back(forest_plaza);
	
	
	std::string playerClass;
	std::cout << "> ";
	std::getline(std::cin, playerClass);
	std::transform(playerClass.begin(), playerClass.end(), playerClass.begin(),
		[](unsigned char c) { return std::tolower(c); });
	bool finishClass = false;
	while (!finishClass) {
		if (playerClass == "knight")
		{
			player = new Player("Lothric", "You are knight Lothric, descendant of the great king Lorian.", 100, 60, 100, 50,
				room1, KNIGHT);
			player->addItem(knightSword);
			//player->addItem(shield);
			player->addItem(fireBurst);
			player->addItem(magicShield);
			player->addItem(healthPotion);
			player->addItem(magicPotion);
			player->addItem(staminaPotion);
			player->equipItem(knightSword);
			finishClass = true;
		}
		else if (playerClass == "mage")
		{
			player = new Player("", "You are mage Marlon, student of the powerful mage Merlin.", 100, 100, 60, 50,
				room1, MAGE);
			player->addItem(shortSword);
			player->addItem(shield);
			player->addItem(fireBall);
			player->addItem(magicShield);
			player->equipItem(fireBall);
			player->addItem(healthPotion);
			player->addItem(magicPotion);
			player->addItem(staminaPotion);
			finishClass = true;
		}
		else
		{
			std::cout << "Invalid class!" << std::endl;
			std::cout << "> ";
			std::getline(std::cin, playerClass);
			std::transform(playerClass.begin(), playerClass.end(), playerClass.begin(),
				[](unsigned char c) { return std::tolower(c); });
		}
	}
	entities.push_back(room1);
	entities.push_back(room2);
	entities.push_back(room3);
	entities.push_back(room4);
	entities.push_back(room5);
	entities.push_back(room6);
	entities.push_back(room7);
	entities.push_back(room8);
	entities.push_back(rustyDagger);
	entities.push_back(shortSword);
	entities.push_back(knightSword);
	entities.push_back(kingSword);
	entities.push_back(fireBurst);
	entities.push_back(fireBall);
	entities.push_back(lightningStorm);
	entities.push_back(shield);
	entities.push_back(magicShield);
	entities.push_back(healthPotion);
	entities.push_back(magicPotion);
	entities.push_back(staminaPotion);
	entities.push_back(houseKey);
	entities.push_back(knightsToThroneKey);
	entities.push_back(magesToThroneKey);
	entities.push_back(familyRing);
	entities.push_back(hinter1);
	entities.push_back(hinter2);
	entities.push_back(hinter3);
	entities.push_back(merchant);
	entities.push_back(helper1);
	entities.push_back(helper2);




}

World::~World() 
{
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete* it;

	entities.clear();
}