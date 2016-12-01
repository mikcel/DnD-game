//! @file 
//! @brief Header file for the Game class 
//!

//!
//! Implements all the functions to run a game given a character and a campaign
//! Loads the multiple maps on the campaign and logs the multiple events taking place during the game procedure.
//!

#pragma once
#include "Map.h"
#include "CharacterElement.h"
#include "Loggable.h"

class CharacterElement;

class Game : public Loggable
{
public:
	Game(Map* m); //! Constructor of the Game class
	bool play(Character* player); // Starts a new game
	Map* getMap();
private:
	Map* map; // A pointer to the mapo used in the curretn game
	bool isGameOver(); // Checks if the game has finished
	bool run(CharacterElement*); // Is executed while that game hasn't finished running
	void perfomEndGame(); // Is executed at the end of the game	

	virtual std::string provider();//! Returns the Loggable provider.
};