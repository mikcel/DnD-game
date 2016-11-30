//!
//! @file 
//! @brief Header file for the Bully Builder
//!

//! 
//! This file contains the definition of the bully builder class. It inherits from the fighter builder class and hence implement
//! the set ability scores method. 
//!

#pragma once

#include "FighterBuilder.h"

//! Class bully builder 
class BullyBuilder:public FighterBuilder{
public:
	virtual void setType(); //! Method to set the fighter's type to bully
	virtual void setAbilityScores(int abilityScrs[Character::NO_ABILITY]); //! Method to set the ability scores of the fighter
};