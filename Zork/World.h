#pragma once

#include <iostream>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Room.h"
#include "Creature.h"
#include "Item.h"

// World class represents the game world that contains all the entities, including player, rooms, creatures and items.

class World
{
public:
	std::vector<Entity*> entities;
	Player* player;
	Creature* ennemyKing;
	Item* familyRing;
	World();
	~World();
};