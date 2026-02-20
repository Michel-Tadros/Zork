#include <iostream>
#include "Entity.h"
#include "Item.h"
#include <string>

int main()
{
	Entity* e1 = new Entity("name", "desc");
    e1->displayInfo();
    Item* i1 = new Item(1,1,1,"item", "item_desc",GOLD);
    e1->container.push_back(i1);
}