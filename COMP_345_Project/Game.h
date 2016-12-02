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
#include "Campaign.h"

class CharacterElement;
class GameLogger;

class Game : public Loggable
{
public:
	Game(Campaign* m); //! Constructor of the Game class
	void play(Character* player); // Starts a new game
private:
	Campaign* campaign; // A pointer to the campaign used in the curretn game
	bool isGameOver(Map&); // Checks if the game has finished
	bool run(Map&, MapElementsToggler&); // Is executed while that game hasn't finished running
	void perfomEndGame(Character**, Map&); // Is executed at the end of the game
	bool gameContinues(bool wantToquit, int nextMapName, vector<string>& mapNames); //Determines if the player wants to continue the game

	virtual std::string provider();//! Returns the Loggable provider.
};