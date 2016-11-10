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
	void play();
private:
	void selectCharacter();
	void selectCampaign();
	void displayMapElementsConsole();
	void launchGame();
	Map * map = nullptr;
	Character * character = nullptr;
	MapElementsObserver * mapElementsObserver;
};