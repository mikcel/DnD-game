//! 
//! @file
//! @brief Header file for the tank builder
//! 

//!
//! The tank builder has only one method. The set ability scores set the ability scores randomly generated in a particular
//! order for the tank. 
//!

#pragma once

#include "FighterBuilder.h"

//! Class for the tank builder
class TankBuilder: public FighterBuilder{
public:
	virtual void setType(); //! Method to set the type to tank
	virtual void setAbilityScores(int abilityScrs[Character::NO_ABILITY]); //! The method to set the ability scores
};