#include "MapElementsObserver.h"
#include "Map.h"
#include "ConsoleLogger.h"

MapElementsObserver::MapElementsObserver(Map* newMap) : map(*newMap)
{
	secondConsole = nullptr;
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

	secondConsole->Close();
	delete secondConsole;
	secondConsole = nullptr;
	return false;
}