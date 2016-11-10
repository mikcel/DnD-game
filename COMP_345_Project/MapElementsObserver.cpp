#include "MapElementsObserver.h"
#include "Map.h"
#include "ConsoleLogger.h"

MapElementsObserver::MapElementsObserver(Map* newMap) : map(*newMap)
{
	
	///secondConsole.CConsoleLoggers Information");

	for (Element* element : map.getElements())
	{
		element->attach(*this);
	}
}

void MapElementsObserver::update()
{
	
}

bool MapElementsObserver::toggle()
{
	if (secondConsole == nullptr)
	{
		secondConsole = new CConsoleLogger();
		secondConsole->Create("Character Elemets");
		return true;
	}

	delete secondConsole;
	return false;
}