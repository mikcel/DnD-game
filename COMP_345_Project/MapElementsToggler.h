//! 
//! @file 
//! @brief Header file for the MapElementsToggler Class.  
//! 

#pragma once

#include "Map.h"
#include "Observer.h"

class Map;
class Observer;

class MapElementsToggler
{
	// Enum that represents all the types of information that can be shown by the toggler
	enum class MapElementsTogglerShowType
	{
		NONE,
		ALL,
		PLAYER,
		ENEMIES,
		CHESTS,
	};

	// Keeps track of the type of information that was selected before
	MapElementsTogglerShowType currentShowType = MapElementsTogglerShowType::NONE; 

	Map* map; //! Reference to the map
	void showPlayerDirect(); //! Shows directly the info about the player
	void showEnemiesDirect(); //! Shows directly the info about the enemies
	void showChestsDirect(); //! Shows directly the info about the chests
public:
	MapElementsToggler(); //! Default constructor
	void setMap(Map* map); //! Sets the map pointer on which the infromation would be taken
	void show(); //! Shows the info about the player, enemies and chests
	void showDirect();
	void showPlayer(); //! Shows the info about the player
	void showEnemies(); //! Shows the info about the enemies
	void showChests(); //! Shows the info about the chests
	void showPrevious(); //! Shows the same type of info as previously
};