#include "MapElementsToggler.h"
#include "Chest.h"
#include "Fighter.h"
#include <string>
#include <iomanip>
#include <iostream>


MapElementsToggler::MapElementsToggler(Map* newMap) : map(*newMap){}

//! Shows the info about the player, enemies and chests
void MapElementsToggler::show()
{
	if (system("CLS")) system("clear");

	showPlayerDirect();
	showEnemiesDirect();
	showChestsDirect();
}

//! Shows the info about the player
void MapElementsToggler::showPlayerDirect()
{
	CharacterElement & player = map.getPlayer();
	cout << endl << "Position: (" << player.getPosition().x << ", " << player.getPosition().y << ")" << endl;
	std::cout << dynamic_cast<Fighter&>(player.getCharacter());

}

//! Shows the info about the enemies
void MapElementsToggler::showEnemiesDirect()
{
	cout << "-------------------------------------------------------------------------------------------------------\n";
	cout << setw(60) << right << "All Enemies" << endl;
	cout << "-------------------------------------------------------------------------------------------------------\n";
	cout << endl;

	CharacterElement & player = map.getPlayer();
	bool atLeastOnce = false;
	// Show other characters' stats
	for (Element* element : map.getElements())
	{
		CharacterElement* characterElement = dynamic_cast<CharacterElement*>(element);
		if (characterElement && &player != characterElement)
		{
			atLeastOnce = true;
			cout << endl << "Position: (" << characterElement->getPosition().x << ", " << characterElement->getPosition().y << ")" << endl;
			std::cout << dynamic_cast<Fighter&>(characterElement->getCharacter());
		}
	}

	if (!atLeastOnce)
	{
		cout << "No enemies present on this map" << endl;
	}
}

//! Shows the info about the chests
void MapElementsToggler::showChestsDirect()
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
void MapElementsToggler::showPlayer()
{
	if (system("CLS")) system("clear");
	showPlayerDirect();
}

//! Clears the console and shows the info about the enemies
void MapElementsToggler::showEnemies()
{
	if (system("CLS")) system("clear");
	showEnemiesDirect();
}

//! Clears the console and shows the info about the chests
void MapElementsToggler::showChests()
{
	if (system("CLS")) system("clear");
	showChestsDirect();
}


