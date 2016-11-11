//! @file 
//! @brief Header file for the Position class  
//!
#pragma once
#include "Campaign.h"
#include "Character.h"
#include "MapElementsObserver.h"

//! Represents a position with a x and y and an initialization state. A non initialized position counts as if the element didn't have a position.
class GameController
{
public:
	void play(); //! Starts a new game
private:
	void selectCharacter(); //! Prompts the user to select a character
	void selectCampaign(); //! Prompts the user to select his campaign
	void launchGame(); //! Launches the game
	Map * map = nullptr; //! Pointer to the map that is currently played
	Character * character = nullptr; //! The Character that the user will control on the map
	MapElementsObserver * mapElementsObserver; //! Toggles information about characters and chests
};