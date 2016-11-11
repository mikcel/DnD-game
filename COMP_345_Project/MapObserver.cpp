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

/**
* Print map instructions and a view of the map
*/
void MapObserver::printMap()
{
	if (system("CLS")) system("clear");
	cout << "========= " << map.getName() << " =========" << endl << endl;
	cout << map.print() << endl;
	
	cout << endl << "---- Instructions ----" << endl;
	cout << "Move : Arrows" << endl;
	cout << "T : Display all map information" << endl;
	cout << "P : Display player information" << endl;
	cout << "E : Display ennemies information" << endl;
	cout << "C : Display chests information" << endl;

}