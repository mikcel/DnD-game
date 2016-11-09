#include "Chest.h"

Chest::Chest()
{
	ItemContainer(itemCnt::CHEST, vector<Item*>(0));
}

Chest::Chest(Chest &chest) {
	ItemContainer* it1 = dynamic_cast<ItemContainer*> (&chest);
	new ItemContainer(itemCnt::CHEST,it1->getContents());
}
Chest::Chest(vector<Item*> vectorOfItems)
{
	ItemContainer(itemCnt::CHEST, vectorOfItems);
}
Chest::~Chest()
{
}
