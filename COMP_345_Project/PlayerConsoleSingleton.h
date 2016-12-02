#pragma once

#include "ConsoleLogger.h"
#include <sstream>

class PlayerConsoleSingleton
{
	PlayerConsoleSingleton();
	CConsoleLoggerEx consoleLogger;
	std::stringstream* stringStream;

	static PlayerConsoleSingleton & instance();
public:	
	static CConsoleLoggerEx & console();	
	static std::stringstream & stream();
	static void printStream();
	static void clearConsole();
};