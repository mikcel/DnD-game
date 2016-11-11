#include "Map.h"
#include "ConsoleLogger.h"
#include "Observer.h"

class MapElementsObserver
{
	Map& map;
	bool isShown;
public:
	MapElementsObserver(Map* map);
	void show();
};