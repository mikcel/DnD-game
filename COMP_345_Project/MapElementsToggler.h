#pragma once

#include "Map.h"
#include "Observer.h"

class Map;
class Observer;

class MapElementsToggler
{
	enum class MapElementsTogglerShowType
	{
		NONE,
		ALL,
		PLAYER,
		ENEMIES,
		CHESTS,
	};

	MapElementsTogglerShowType currentShowType = MapElementsTogglerShowType::NONE;

	Map* map; //! Reference to the map
	void showPlayerDirect(); //! Shows directly the info about the player
	void showEnemiesDirect(); //! Shows directly the info about the enemies
	void showChestsDirect(); //! Shows directly the info about the chests
public:
	MapElementsToggler();
	void setMap(Map* map);
	void show(); //! Shows the info about the player, enemies and chests
	void showDirect();
	void showPlayer(); //! Shows the info about the player
	void showEnemies(); //! Shows the info about the enemies
	void showChests(); //! Shows the info about the chests
	void showPrevious();
};