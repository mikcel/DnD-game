#include "Map.h"
#include "ConsoleLogger.h"
#include "Observer.h"

class MapElementsObserver
{
	Map& map;
	bool isShown;
	void showPlayerDirect();
	void showEnemiesDirect();
	void showChestsDirect();
public:
	MapElementsObserver(Map* map);
	void show();
	void showPlayer();
	void showEnemies();
	void showChests();
};