#pragma once
#include <iostream>
#include <string>
#include "Player.h"

//Process user input and execute the corresponding command.

void printLines();
void printStars();
void oneWordCommands(Player* player, const std::string& cmd);
void twoWordsCommands(Player* player, const std::string& cmd, const std::string& cmd2);
void threeWordsCommands(Player* player, const std::string& cmd, const std::string& cmd2, const std::string& cmd3);