#include "MapElementsObserver.h"
#include "Map.h"
#include "ConsoleLogger.h"
#include "Chest.h"
#include <iostream>

MapElementsObserver::MapElementsObserver(Map* newMap) : map(*newMap){}

void MapElementsObserver::show()
{
	if (system("CLS")) system("clear");
	Player& player = map.getPlayer();
	std::cout << player.getCharacter();
		
	// Show other characters' stats
	for (Element* element : map.getElements())
	{
		CharacterElement* characterElement = dynamic_cast<CharacterElement*>(element);
		if (characterElement && &player != characterElement)
		{
			std::cout << characterElement->getCharacter();
		}
	}

	// Show chests' info
	for (Element* element : map.getElements())
	{
		Chest* chest = dynamic_cast<Chest*>(element);
		if (chest)
		{
			std::cout << *chest;
		}
	}
}