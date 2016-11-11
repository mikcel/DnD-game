#include "MapElementsObserver.h"
#include "Map.h"
#include "Chest.h"
#include <string>
#include <iomanip>
#include <iostream>


MapElementsObserver::MapElementsObserver(Map* newMap) : map(*newMap){}

//! Shows the info about the player, enemies and chests
void MapElementsObserver::show()
{
	if (system("CLS")) system("clear");
	
	showPlayerDirect();
	showEnemiesDirect();
	showChestsDirect();	
}

//! Shows the info about the player
void MapElementsObserver::showPlayerDirect()
{
	Player& player = map.getPlayer();
	cout << endl << "Position: (" << player.getPosition().x << ", " << player.getPosition().y << ")" << endl;
	std::cout << player.getCharacter();

}

//! Shows the info about the enemies
void MapElementsObserver::showEnemiesDirect()
{
	Player& player = map.getPlayer();

	// Show other characters' stats
	for (Element* element : map.getElements())
	{
		CharacterElement* characterElement = dynamic_cast<CharacterElement*>(element);
		if (characterElement && &player != characterElement)
		{
			cout << endl << "Position: (" << characterElement->getPosition().x << ", " << characterElement->getPosition().y << ")" << endl;
			std::cout << characterElement->getCharacter();			
		}
	}
}

//! Shows the info about the chests
void MapElementsObserver::showChestsDirect()
{
	cout << "-------------------------------------------------------------------------------------------------------\n";
	cout << setw(60) << right << "All Chests" << endl;
	cout << "-------------------------------------------------------------------------------------------------------\n";
	cout << endl;

	bool atLeastOnce = false;
	// Show chests' info
	for (Element* element : map.getElements())
	{
		Chest* chest = dynamic_cast<Chest*>(element);
		if (chest)
		{
			atLeastOnce = true;
			cout << endl << "Position: (" << chest->getPosition().x << ", " << chest->getPosition().y << ")" << endl;
			std::cout << *chest;
		}
	}

	if (!atLeastOnce)
	{
		cout << "No chests present on this map" << endl;
	}
}

//! Clears the console and shows the info about the player
void MapElementsObserver::showPlayer()
{
	if (system("CLS")) system("clear");
	showPlayerDirect();
}

//! Clears the console and shows the info about the enemies
void MapElementsObserver::showEnemies()
{
	if (system("CLS")) system("clear");
	showEnemiesDirect();
}

//! Clears the console and shows the info about the chests
void MapElementsObserver::showChests()
{
	if (system("CLS")) system("clear");
	showChestsDirect();
}