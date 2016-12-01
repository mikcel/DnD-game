#pragma once

#include "ConsoleLogger.h"

class PlayerConsoleSingleton
{
	PlayerConsoleSingleton();
	CConsoleLoggerEx consoleLogger;

public:
	static CConsoleLoggerEx & console();
};