#include "MapElementsObserver.h"
#include "Map.h"
#include "ConsoleLogger.h"

MapElementsObserver::MapElementsObserver(Map* newMap) : map(*newMap)
{
	secondConsole.Create("Elements Information");
}