#include "MapElementsObserver.h"
#include "Map.h"
#include "ConsoleLogger.h"
#include <iostream>

MapElementsObserver::MapElementsObserver(Map* newMap) : map(*newMap)
{
	secondConsole = nullptr;
	///secondConsole.CConsoleLoggers Information");

	for (Element* element : map.getElements())
	{
		CharacterElement* characterElement = dynamic_cast<CharacterElement*>(element);
		if (characterElement)
		{
			//characterElement->
			//characterElement->attach(*this);
		}
		
	}
}

void MapElementsObserver::update()
{
	secondConsole->printf("asd");
}

bool MapElementsObserver::toggle()
{
	if (secondConsole == nullptr)
	{
		//system("start \"Help\" cmd /C \"echo off & echo Help text 1 & echo Help text 2 & echo Help text 3 & pause\"");

		secondConsole = new CConsoleLogger();
		secondConsole->Create("Character Elemets");
		secondConsole->printf("asd");
		secondConsole->SetAsDefaultOutput();
		std::cout << "\nstd cout";
		secondConsole->ResetDefaultOutput();
		//secondConsole->
		return true;
	}

	secondConsole->Close();
	secondConsole->Close();
	delete secondConsole;
	secondConsole = nullptr;
	return false;
}