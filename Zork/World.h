#pragma once

#include <iostream>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Room.h"
#include "Creature.h"
#include "Item.h"

class World
{
public:
	std::vector<Entity*> entities;
	std::vector<Room*> roomsList;
	std::vector<Creature*> ennemyList;
	Player* player;
	Creature* ennemyKing;
	Item* familyRing;
	World();
	~World();
};