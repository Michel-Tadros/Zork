#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Entity.h"
#include "World.h"
#include "Player.h"
#include "Helper.h"

int main()
{
	bool game = true;
	while (game) {
		std::cout << "Welcome to Zork!" << std::endl;
		printLines();
		std::cout << "Choose your class: Knight / Mage." << std::endl;
		World world;
		world.player->displayInfo();
		printLines();
		std::cout << "You are suddenly woken up by the sound of a sinister laughter. You check your surroundings and see that your family ring is missing. In front of you is a thief squire, ready to attack!" << std::endl;
		std::cout << "You decide to attack the thief!\n";
		printLines();
		world.player->attackCreature(world.ennemyList[0]);
		printLines();
		std::cout << "You must find the thief king and retrieve your family ring!" << std::endl;
		bool start = true;
		while (start && world.player->heatlh> 0) {
			std::string input;
			std::cout << "> ";
			std::getline(std::cin, input);
			if (input == "exit")
				break;
			std::stringstream ss(input);
			std::transform(input.begin(), input.end(), input.begin(),
				[](unsigned char c) { return std::tolower(c); });
			std::vector<std::string> sentence;
			std::string word;

			while (ss >> word)
				sentence.push_back(word);

			if (sentence.empty())
				continue;
			switch (sentence.size())
			{
			case 1:
				oneWordCommands(world.player, sentence[0]);
				break;

			case 2:
				twoWordsCommands(world.player, sentence[0], sentence[1]);
				break;
			case 3:
				threeWordsCommands(world.player, sentence[0], sentence[1], sentence[2]);
				break;
			default:
				std::cout << "Invalid command!" << std::endl;
				break;
			}
		}
	}

}