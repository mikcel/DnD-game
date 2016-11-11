//!
//! @file 
//! @brief Header file of the Player class.
//!

#pragma once
#include "Character.h"
#include "CharacterElement.h"

//! Class that represents a player that is situated on the map
//! and that can be controlled by the user of the application
class Player : public CharacterElement
{
	virtual const std::string print() const; //! Print the map representation of the player
public:
	Player::Player(Character& newCharacter); //! Constructor to create a new Player instance by passing a Character reference
	virtual Player* Player::clone(); //! Create a copy of the current Player instance
	friend class Map; //! Allow the map to use the internal members of the Player class
};