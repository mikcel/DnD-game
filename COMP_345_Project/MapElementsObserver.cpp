#include "MapElementsObserver.h"
#include "Map.h"
#include "ConsoleLogger.h"
#include "Chest.h"
#include <iostream>

MapElementsObserver::MapElementsObserver(Map* newMap) : map(*newMap){}

void MapElementsObserver::show()
{
	if (system("CLS")) system("clear");
	
	showPlayerDirect();
	showEnemiesDirect();
	showChestsDirect();	
}

void MapElementsObserver::showPlayerDirect()
{
	Player& player = map.getPlayer();
	std::cout << player.getCharacter();
}

void MapElementsObserver::showEnemiesDirect()
{
	Player& player = map.getPlayer();

	// Show other characters' stats
	for (Element* element : map.getElements())
	{
		CharacterElement* characterElement = dynamic_cast<CharacterElement*>(element);
		if (characterElement && &player != characterElement)
		{
			std::cout << characterElement->getCharacter();
		}
	}
}

void MapElementsObserver::showChestsDirect()
{
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

void MapElementsObserver::showPlayer()
{
	if (system("CLS")) system("clear");
	showPlayerDirect();
}

void MapElementsObserver::showEnemies()
{
	if (system("CLS")) system("clear");
	showEnemiesDirect();
}

void MapElementsObserver::showChests()
{
	if (system("CLS")) system("clear");
	showChestsDirect();
}