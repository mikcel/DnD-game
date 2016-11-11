//! @file 
//! @brief Implementation file for the MapObserver class
//!

#include "MapObserver.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

/**
* Intializes a MapObserver with a map
* @param m Map observed (for the printing during the update)
*/
MapObserver::MapObserver(const Map& m) : map(m), timesUpdated(0){}

/**
* When notified, clears the console and prints the map
*/
void MapObserver::update()
{
	printMap();
}

void MapObserver::printMap()
{
	if (system("CLS")) system("clear");

	cout << "========= " << map.getName() << " =========" << endl << endl;
	cout << map.print() << endl;
}