#pragma once
#include <iostream>
#include <string>
#include "Player.h"

void printLines();
void oneWordCommands(Player* player, const std::string& cmd);
void twoWordsCommands(Player* player, const std::string& action, const std::string& target);
void threeWordsCommands(Player* player, const std::string& action, const std::string& target, const std::string& object);