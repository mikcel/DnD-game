#include "PlayerConsoleSingleton.h"
#include <vector>

using namespace std;

/**
* Private constructor of the singleton that creates a new inbstace of the string stream
*/
PlayerConsoleSingleton::PlayerConsoleSingleton() : stringStream(new std::stringstream)
{
	consoleLogger.Create("Player console");
}

/**
* Obtains the instance of the singleton
* @return the instance of the singleton
*/
PlayerConsoleSingleton & PlayerConsoleSingleton::instance()
{
	static PlayerConsoleSingleton instance;
	return instance;
}

/**
* Obtains a reference to the second console object
* @return reference to the second console object
*/
CConsoleLoggerEx & PlayerConsoleSingleton::console()
{
	return instance().consoleLogger;
}

/**
* Clears all the text inside the second console
*/
void PlayerConsoleSingleton::clearConsole()
{
	console().cls();
}

/**
* Obtains the string stream of the second console
* @return string stream of the console
*/
stringstream & PlayerConsoleSingleton::stream()
{
	return *instance().stringStream;
}

/**
* Prints everything that is currently in the string stream into the console,
* then deletes the old stream and creates a new instance of the stream
*/
void PlayerConsoleSingleton::printStream()
{
	string stringFromStream = (*instance().stringStream).str();

	const int sizeOfChunk = 100;

	for (unsigned i = 0; i < stringFromStream.length(); i += sizeOfChunk) {

		instance().console().printf(stringFromStream.substr(i, sizeOfChunk).c_str());
	}

	delete instance().stringStream;

	instance().stringStream = new std::stringstream();
}