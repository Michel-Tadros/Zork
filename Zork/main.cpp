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
		printLines();
		std::cout << "You are suddenly woken up by the sound of a sinister laughter. You check your surroundings and see that your family ring is missing!" << std::endl;
		std::cout << "You look around you and see a thief guarding your door!"<<std::endl;
		printLines();
		std::cout << "Thief Squire: HAHAHAHA! We took your precious family ring while you were sleeping and our King has taken it to his castle! You will never walk outside this house as long as I breath!"<<std::endl;
		printLines();
		world.player->inTheRoom();
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
				if (sentence[0] == "quit")
				{
					std::cout << "Thank you for playing Zork!" << std::endl;
					printLines();
					return 0;
				}
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