#include "PlayerConsoleSingleton.h"
#include <vector>

using namespace std;

PlayerConsoleSingleton::PlayerConsoleSingleton() : stringStream(new std::stringstream)
{
	consoleLogger.Create("Player console");
}

PlayerConsoleSingleton & PlayerConsoleSingleton::instance()
{
	static PlayerConsoleSingleton instance;
	return instance;
}

CConsoleLoggerEx & PlayerConsoleSingleton::console()
{
	return instance().consoleLogger;
}

void PlayerConsoleSingleton::clearConsole()
{
	console().cls();
}

stringstream & PlayerConsoleSingleton::stream()
{
	return *instance().stringStream;
}

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