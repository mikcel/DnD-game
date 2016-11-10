//!
//! @file 
//! @brief Header file for the Character Observer

#pragma once
#include "Observer.h"
#include "Character.h"

//! Class that implements the Character Observer. Inherits from the observer class
class CharacterObserver :public Observer{

public:
	CharacterObserver(); //! Default constructor
	CharacterObserver(Character& chr); //! Parametrized constructor
	~CharacterObserver(); //! Destructor
	void Update(); //! Method to update the observer
	void display(); //! Method to display new stats
private:
	Character* _subject; //! Pointer to the Character subject
};