#pragma once

#include <iostream>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Room.h"
#include "Creature.h"

class World
{
public:
	std::vector<Entity*> entities;
	std::vector<Room*> roomsList;
	std::vector<Creature*> ennemyList;
	Player* player;
	World();
	~World();
};