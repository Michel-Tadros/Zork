#include <iostream>
#include "Key.h"

Key::Key(Exit* exit, int value, std::string name, std::string description) : 
	Item(value, name, description, itemType = KEY)
{
	this->exit = exit;
}
Key::~Key() {}

bool Key::unlockExit(Exit* exit)
{
	if(this->exit == exit)
	{
		exit->isLocked = false;
		std::cout << "You opened the door: " << exit->name << "!" << std::endl;
		return true;
	}
	else
	{
		std::cout << "This key cannot open the door: " << exit->name << "!" << std::endl;
		return false;
	}
}