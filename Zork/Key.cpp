#include <iostream>
#include "Key.h"

Key::Key(Exit* exit, int value, std::string name, std::string description) : 
	Item(value, name, description)
{
	this->exit = exit;
}
Key::~Key() {}