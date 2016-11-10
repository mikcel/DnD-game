#include "MapElementsObserver.h"
#include "Map.h"
#include "ConsoleLogger.h"

MapElementsObserver::MapElementsObserver(Map* newMap) : map(*newMap)
{
	
	///secondConsole.CConsoleLoggers Information");

	/*for (Element& )
	{

	}*/
}

void MapElementsObserver::update()
{
	
}

bool MapElementsObserver::toggle()
{
	secondConsole = new CConsoleLogger();
	secondConsole->Create("Character Elemets");
	return true;
}