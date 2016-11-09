#include "Chest.h"

Chest::Chest()
{
	ItemContainer(ContainerType::CHEST, vector<Item*>(0));
}

Chest::Chest(Chest &chest) {
	ItemContainer* it1 = dynamic_cast<ItemContainer*> (&chest);
	new ItemContainer(ContainerType::CHEST, it1->getContents());
}
Chest::Chest(vector<Item*> vectorOfItems)
{
	ItemContainer(ContainerType::CHEST, vectorOfItems);
}
Chest::~Chest()
{
}
