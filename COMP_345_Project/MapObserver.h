//! @file 
//! @brief Header file for the MapObserver class  
//!

#pragma once
#include "Observer.h"
#include "Map.h"

//! Represents a map observer.
//! Any time a map is updated, it prints it.
class MapObserver : public Observer
{
public:
	MapObserver(const Map&); //! Map Observer constructor
	virtual void update(); //! Called when an observed  object send a notification
	void printMap(); //! Amount of times the update() function was called
private:
	const Map& map; //! Reference to the observed map
	long long timesUpdated; //! Amount of times the update() function was called
};