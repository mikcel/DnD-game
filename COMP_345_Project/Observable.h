//! @file 
//! @brief Header file for the Observable class 
//!

#pragma once
#include "Observer.h"
#include <list>

//! Abstract representation of an observable object (also called subject)
class Observable {
public:
	void attach(Observer&); //! Adds an observer to the observers list
	void detach(Observer&); //! Removes an observer from the observers list
	void notify(); //! Notifies the observers of a modification
	const std::list<Observer*> & getObservers() const; //! Returns a readonly list of the observers
private:
	std::list<Observer*> observers; //! List of observers
};