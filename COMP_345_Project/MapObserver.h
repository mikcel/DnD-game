//! @file 
//! @brief Header file for the MapObserver class  
//!

#pragma once
#include "Observer.h"
#include "Map.h"

enum class TurnType
{
	HUMAN_PLAYER_MOVE,
	HUMAN_PLAYER_ATTACK,
	AI_MOVE,
	AI_ATTACK,
};

//! Represents a map observer.
//! Any time a map is updated, it prints it.
class MapObserver : public Observer
{
	std::string typeOfcharacter;
	std::string characterName;
	TurnType turnType;
	int stepsRemnaining;
public:
	MapObserver(const Map&); //! Map Observer constructor
	virtual void update(); //! Called when an observed  object send a notification
	void printMap(); //! Amount of times the update() function was called
	void setPrintCharacterInfo(std::string typeOfcharacter, std::string characterName); //! Sets the info about the character that currently has teh turn
	void setPrintTurnInfo(TurnType turnType); //! Sets the current type of turn
	void setPrintMovementInfo(int stepsRemnaining); //! Sets the remaining number of steps for teh character
private:
	const Map& map; //! Reference to the observed map
	long long timesUpdated; //! Amount of times the update() function was called
};