//! @file 
//! @brief Implementation file for the Observable class
//!

#include "Observable.h"

using namespace std;

/**
* Attaches an observer to the observable
* @param o Reference to the observer to attach
*/
void Observable::attach(Observer& o)
{
	observers.push_back(&o);
}

/**
* Detaches an observer from the observable
* @param o Reference to the observer to detach
*/
void Observable::detach(Observer& o)
{
	observers.remove(&o);
}

/**
* Notifies all the Observable's observers that Observable was updated
*/
void Observable::notify()
{
	for (Observer* o : observers)
	{
		o->update();
	}
}

/**
* Get a readonly list of the observers
* @return Read-only list of the observers
*/
const list<Observer*> & Observable::getObservers() const
{
	return observers;
}