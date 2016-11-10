#include "Map.h"
#include "ConsoleLogger.h"
#include "Observer.h"

class MapElementsObserver : public Observer
{
	Map& map;
	CConsoleLogger secondConsole;
	virtual void update();
public:
	MapElementsObserver(Map* map);
};