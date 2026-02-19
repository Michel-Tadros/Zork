#pragma once
#include <iostream>
#include<string>
#include <list>


enum Type
{
	ENTITY,
	ITEM,
	ROOM,
	EXIT,
	CREATURE
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
	virtual void update();
	virtual void displayInfo();
};
