#pragma once
#include <iostream>
#include "Entity.h"
#include <string>

class Item:public Entity
{
public:
	int value;

public:
	Item(int value, std::string name, std::string description);
	~Item();
};