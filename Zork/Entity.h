#pragma once
#include <iostream>
#include<string>
#include <list>

//Base class for all entities in the game
enum Type
{
	ENTITY,
	ITEM,
	ROOM,
	EXIT,
	CREATURE,
	CHEST
};

class Entity 
{
public:
	std::string name;
	std::string description;
	std::list<Entity*> container;
	Type entityType;

public:
	Entity(std::string name, std::string description);
	~Entity();
	virtual void displayInfo();
};
