#include <iostream>
#include "Player.h"

Player::Player(std::string name, std::string description, int health, int magic, int stamina, int gold, 
	Room* location, PlayerType playerType) : Creature(name, description, health, magic, stamina, gold, location)
{
	this->playerType = playerType;
}
Player::~Player() {}