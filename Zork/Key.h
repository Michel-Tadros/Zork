#pragma once
#include <iostream>
#include <string>
#include "Item.h"
#include "Exit.h"

// Key class represents the key item that can be used to unlock locked exits.

class Key :public Item
{
public:
	Exit* exit;
	Key(Exit* exit, int value, std::string name, std::string description);
	~Key();
	bool unlockExit(Exit* exit);
};