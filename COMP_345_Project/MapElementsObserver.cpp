#include "MapElementsObserver.h"
#include "Map.h"
#include "ConsoleLogger.h"
#include <iostream>

MapElementsObserver::MapElementsObserver(Map* newMap) : map(*newMap)
{
	isShown = false;
	///secondConsole.CConsoleLoggers Information");

	
}

bool MapElementsObserver::toggle()
{
	if (!isShown)
	{
		isShown = true;

		Player& player = map.getPlayer();
		std::cout << player.getCharacter();
		
		//for (Element* element : map.getElements())
		//{
		//	CharacterElement* characterElement = dynamic_cast<CharacterElement*>(element);
		//	if (characterElement)
		//	{
		//		characterElement->getCharacter().attach(*this);
		//		//characterElement->attach(*this);
		//	}

		//}

		return true;
	}

	isShown = false;



	return false;
}