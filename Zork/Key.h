#pragma once
#include <iostream>
#include <string>
#include "Item.h"
#include "Exit.h"

class Key :public Item
{
public:
	Exit* exit;
	Key(Exit* exit, int value, std::string name, std::string description);
	~Key();
	bool unlockExit(Exit* exit);
};