//! 
//! @file 
//! @brief Header file for the CharacterStrategy class
//! 

#include "CharacterStrategy.h" 

/**
* Executes a game turn using the current strategy
* @param map the map on which the game is played
* @param mo the map observer
* @param meo the map elements toggler
* @return true if the players wants to continue to play, false otherwise.
*/
bool CharacterStrategy::executeTurn(Map& map, MapObserver& mo, MapElementsToggler& meo)
{
	if (executeMovementTurn(map, mo, meo))
	{
		return executeAttack(map, mo, meo);
	}

	return false;
}

/**
* Sets the CharacterElement of the current strategy
* @param newCharacterElement a pointer to the CharacterElement to be set
*/
void CharacterStrategy::setCharacterElement(CharacterElement* newCharacterElement)
{
	characterElement = newCharacterElement;
}