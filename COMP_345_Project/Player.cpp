//! 
//! @file 
//! @brief Implementation file for the Player Class.  
//! 

#include "Player.h"
#include <string>

/**
* Returns a string representation of the Player on the map
* @return string representing the player
*/
const std::string Player::print() const
{
	return "\xFE";
}

/**
* Create a new instance of the Player class
* @param newCharacter a reference of the Character is related to this Player
*/
Player::Player(Character& newCharacter) : CharacterElement(newCharacter)
{ 
	
}

/**
* Create a copy of this Player
* @return a pointer to a dynamically allocated copy of the current Player instance
*/
Player* Player::clone()
{
	return new Player(*this);
}