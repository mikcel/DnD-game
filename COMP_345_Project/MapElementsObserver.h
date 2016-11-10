#include "Map.h"
#include "ConsoleLogger.h"

class MapElementsObserver
{
	Map& map;
	CConsoleLogger secondConsole;
public:
	MapElementsObserver(Map* map);
};