//! 
//! @file 
//! @brief Header file for the Nimble builder
//!

//! 
//! In this file, the nimble builder class is defined. It contains only the set ability method that will set the ability scores
//! the a corresponding order for the nimble.
//! 

#pragma once

#include "FighterBuilder.h"

//! Class for the nimble builder
class NimbleBuilder:public FighterBuilder{
public:
	virtual void setType(); //! Method to set the fighter's type to nimble
	virtual void setAbilityScores(int abilityScrs[Character::NO_ABILITY]); //! Method to set the ability scores in a particular order
};