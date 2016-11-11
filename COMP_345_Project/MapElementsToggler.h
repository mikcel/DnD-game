#include "Map.h"
#include "Observer.h"

class MapElementsObserver
{
	Map& map; //! Reference to the map
	void showPlayerDirect(); //! Shows directly the info about the player
	void showEnemiesDirect(); //! Shows directly the info about the enemies
	void showChestsDirect(); //! Shows directly the info about the chests
public:
	MapElementsObserver(Map* map);
	void show(); //! Shows the info about the player, enemies and chests
	void showPlayer(); //! Shows the info about the player
	void showEnemies(); //! Shows the info about the enemies
	void showChests(); //! Shows the info about the chests
};