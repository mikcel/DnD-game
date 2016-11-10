#include "Map.h"
#include "ConsoleLogger.h"
#include "Observer.h"

class MapElementsObserver : public Observer
{
	Map& map;
	CConsoleLogger * secondConsole;
public:
	MapElementsObserver(Map* map);
	virtual void update();
	bool toggle();
};