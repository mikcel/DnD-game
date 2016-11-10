//! @file MapController.h
//! @brief Class to create a Map controller that wraps a Map object
#pragma once
#include "Map.h"
#include <iostream>
using namespace std;
//! Class to create MapControllers that points to a Map object
class MapController
{
public:
	//! Default Constructor
	MapController();
	//! Copy Constructor
	MapController(Map* currentMap);
	//! Destructor
	~MapController();
	//! method that gets the pointer of the current map
	//! @return: pointer to map object
	Map* getCurrentMap();
	//! method that sets a copy of the passing map object to current map
	//! @param newMap:pointer to a map object
	void setCurrentMap(Map* newMap);
	//! method that prompt the user for parameters to create a map.
	void createMap();
	//! method prompts the user for parameters to edit a map
	//! @param creatingNewMap: boolean that decides whether to treat the object as a new map or not
	void editMap(bool creatingNewMap);
	//! method that saves the map to a map file
	void saveMap();
	//! method that reads a mapfile and returns a new map object
	//! @param mapFileLocation: string of the file path
	//! @param mapName: string of the map name;
	//! @return: pointer to the newly read map.
	Map* readMapFile(string mapFileLocation, string mapName);

	void quit();

private:
	//! method that prompts the user to find the right map that they want to edit and caches it
	//! @return: boolean if the cahce was successful
	bool cacheMap();
	//! current Map pointer to a map object.
	Map* currentMap;
};

