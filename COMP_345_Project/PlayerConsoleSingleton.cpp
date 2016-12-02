#include "PlayerConsoleSingleton.h"

PlayerConsoleSingleton::PlayerConsoleSingleton()
{
	consoleLogger.Create("Player console");
}

CConsoleLoggerEx & PlayerConsoleSingleton::console()
{
	static PlayerConsoleSingleton instance;
	return instance.consoleLogger;
}