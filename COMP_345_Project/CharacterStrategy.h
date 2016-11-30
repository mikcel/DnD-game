//! @file 
//! @brief Header file the CharacterStrategy class
//!

#pragma once

#include <string>
#include "Map.h"
#include "CharacterElement.h"
#include "MapObserver.h"
#include "MapElementsToggler.h"
#include <conio.h>
#include "MathHelper.h"

class CharacterElement;
class MapObserver;
class Map;
class MapElementsToggler;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER '\r'

//! Abstract character strategy
class CharacterStrategy
{	
protected:
	CharacterElement* characterElement; //! Pointer to the CharacterElement of the strategy
	virtual bool executeMovementTurn(Map& map, MapObserver& mo, MapElementsToggler& meo) = 0; //! Executes the movement phase of the turn
	virtual bool executeAttack(Map& map, MapObserver& mo, MapElementsToggler& meo) = 0; //! Executes the attack phase of the turn
public:
	const int NUMBER_OF_STEPS = 4; //! The number of steps that a character has per turn

	void setCharacterElement(CharacterElement* newCharacterElement); //! Sets the CharacterElement of the current strategy
	virtual std::string print() const = 0; //! Obtains the map representation of the CharacterElement
	bool executeTurn(Map& map, MapObserver& mo, MapElementsToggler& meo); // Executes a game turn on the CharacterStrategy
	virtual std::string getStrategyName() = 0; //! Obtains human-readble the name of the CharacterStrategy
};