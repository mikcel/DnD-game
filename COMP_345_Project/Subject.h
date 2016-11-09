//! 
//! @file
//! @brief Header file for the subject class

#pragma once
#include "Observer.h"
#include <list>
using namespace std;

//! Class that implements the Subject
class Subject{

public:
	virtual void Attach(Observer* o); //! Abstract method to attach an observer
	virtual void Detach(Observer* o); //! Abstract method to detach an observer
	virtual void Notify(); //! Abstract method to update each observer
	Subject(); //! Constructor
	~Subject(); //! Destructor
private:
	list<Observer*> *_observers; //! List of observers
};