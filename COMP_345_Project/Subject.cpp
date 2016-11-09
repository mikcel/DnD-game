//! 
//! @file
//! @brief Implementation file for the Subject class

#include "Subject.h"
#include "Observer.h"
#include <iostream>
using namespace std;

//! Default Cosntructor
Subject::Subject(){
	_observers = new list<Observer*>; //! Make a new list of Observers
}

//! Destructor
Subject::~Subject(){
	delete _observers; //! Delete the list of observers
}

//! Method to attach an observer to the subject
//! @param Observer pointer to an observer object
void Subject::Attach(Observer *o){
	_observers->push_back(o); //! Put the passed observer to the list
}

//! Method to detach an observer from the Subject
//! @param Observer pointer to remove from the list
void Subject::Detach(Observer *o){
	_observers->remove(o); //! Remove the observer from the list
}

//! Method to notify all observer about a change in the Subject's state
void Subject::Notify(){
	list<Observer *>::iterator i = _observers->begin(); //! Iterator to loop through the Observer list
	for (; i != _observers->end(); i++){
		(*i)->Update(); //! Call the update method of each observer
	}
}
