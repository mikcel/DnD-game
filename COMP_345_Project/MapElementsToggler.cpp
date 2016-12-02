//! 
//! @file 
//! @brief Implementation file for the MapElementsToggler Class.  
//! 

#include "MapElementsToggler.h"
#include "Chest.h"
#include "Fighter.h"
#include <string>
#include <iomanip>
#include <iostream>
#include "PlayerConsoleSingleton.h"

MapElementsToggler::MapElementsToggler(){}

//! Shows the info about the player, enemies and chests
void MapElementsToggler::show()
{
	if(currentShowType == MapElementsTogglerShowType::ALL)
	{
		currentShowType = MapElementsTogglerShowType::NONE;
		PlayerConsoleSingleton::clearConsole();
		return;
	}

	currentShowType = MapElementsTogglerShowType::ALL;
	//PlayerConsoleSingleton::console().printf("asd");

	//PlayerConsoleSingleton::console().SetAsDefaultOutput();
	//if (system("CLS")) system("clear");
	
	PlayerConsoleSingleton::clearConsole();

	showPlayerDirect();
	showEnemiesDirect();
	showChestsDirect();
	//PlayerConsoleSingleton::console().ResetDefaultOutput();
}

//! Shows the info about the player
void MapElementsToggler::showPlayerDirect()
{
	CharacterElement & player = map->getPlayer();
	PlayerConsoleSingleton::stream() << endl << "Position: (" << player.getPosition().x << ", " << player.getPosition().y << ")" << endl;
	PlayerConsoleSingleton::stream() << dynamic_cast<Fighter&>(player.getCharacter());
	PlayerConsoleSingleton::printStream();
}

//! Shows the info about the enemies
void MapElementsToggler::showEnemiesDirect()
{
	PlayerConsoleSingleton::stream() << "-------------------------------------------------------------------------------------------------------\n";
	PlayerConsoleSingleton::stream() << setw(60) << right << "All Enemies" << endl;
	PlayerConsoleSingleton::stream() << "-------------------------------------------------------------------------------------------------------\n";
	PlayerConsoleSingleton::stream() << endl;

	CharacterElement & player = map->getPlayer();
	bool atLeastOnce = false;
	// Show other characters' stats
	for (Element* element : map->getElements())
	{
		CharacterElement* characterElement = dynamic_cast<CharacterElement*>(element);
		if (characterElement && &player != characterElement)
		{
			atLeastOnce = true;
			PlayerConsoleSingleton::stream() << endl << "Position: (" << characterElement->getPosition().x << ", " << characterElement->getPosition().y << ")" << endl;
			PlayerConsoleSingleton::stream() << dynamic_cast<Fighter&>(characterElement->getCharacter());
		}
	}

	if (!atLeastOnce)
	{
		PlayerConsoleSingleton::stream() << "No enemies present on this map" << endl;
	}

	PlayerConsoleSingleton::printStream();
}

//! Shows the info about the chests
void MapElementsToggler::showChestsDirect()
{
	PlayerConsoleSingleton::stream() << "-------------------------------------------------------------------------------------------------------\n";
	PlayerConsoleSingleton::stream() << setw(60) << right << "All Chests" << endl;
	PlayerConsoleSingleton::stream() << "-------------------------------------------------------------------------------------------------------\n";
	PlayerConsoleSingleton::stream() << endl;

	bool atLeastOnce = false;
	// Show chests' info
	for (Element* element : map->getElements())
	{
		Chest* chest = dynamic_cast<Chest*>(element);
		if (chest)
		{
			atLeastOnce = true;
			PlayerConsoleSingleton::stream() << endl << "Position: (" << chest->getPosition().x << ", " << chest->getPosition().y << ")" << endl;
			PlayerConsoleSingleton::stream() << *chest;
		}
	}

	if (!atLeastOnce)
	{
		PlayerConsoleSingleton::stream() << "No chests present on this map" << endl;
	}

	PlayerConsoleSingleton::printStream();
}

//! Clears the console and shows the info about the player
void MapElementsToggler::showPlayer()
{
	if (currentShowType == MapElementsTogglerShowType::PLAYER)
	{
		currentShowType = MapElementsTogglerShowType::NONE;
		PlayerConsoleSingleton::clearConsole();
		return;
	}
	currentShowType = MapElementsTogglerShowType::PLAYER;
	PlayerConsoleSingleton::clearConsole();
	showPlayerDirect();
}

//! Clears the console and shows the info about the enemies
void MapElementsToggler::showEnemies()
{
	if (currentShowType == MapElementsTogglerShowType::ENEMIES)
	{
		currentShowType = MapElementsTogglerShowType::NONE;
		PlayerConsoleSingleton::clearConsole();
		return;
	}
	currentShowType = MapElementsTogglerShowType::ENEMIES;
	PlayerConsoleSingleton::clearConsole();
	showEnemiesDirect();
}

//! Clears the console and shows the info about the chests
void MapElementsToggler::showChests()
{
	if (currentShowType == MapElementsTogglerShowType::CHESTS)
	{
		currentShowType = MapElementsTogglerShowType::NONE;
		PlayerConsoleSingleton::clearConsole();
		return;
	}
	currentShowType = MapElementsTogglerShowType::CHESTS;
	PlayerConsoleSingleton::clearConsole();
	showChestsDirect();
}

//! Shows the same type information as before
void MapElementsToggler::showPrevious()
{
	PlayerConsoleSingleton::clearConsole();
	switch (currentShowType)
	{
	case MapElementsTogglerShowType::ALL:
		showDirect();
		break;
	case MapElementsTogglerShowType::PLAYER:
		showPlayerDirect();
		break;
	case MapElementsTogglerShowType::ENEMIES:
		showEnemiesDirect();
		break;
	case MapElementsTogglerShowType::CHESTS:
		showChestsDirect();
		break;
	case MapElementsTogglerShowType::NONE:
		PlayerConsoleSingleton::clearConsole();
		break;
	}
}

//! Shows the information about the the player, enemies and chest directly without any checking
void MapElementsToggler::showDirect()
{
	currentShowType = MapElementsTogglerShowType::ALL;
	PlayerConsoleSingleton::clearConsole();

	showPlayerDirect();
	showEnemiesDirect();
	showChestsDirect();
}

//! Sets the pointer to the map from which the infromation is taken
void MapElementsToggler::setMap(Map* map)
{
	this->map = map;
}

