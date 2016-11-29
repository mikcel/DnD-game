//!
//! @file 
//! @brief Header file for Fighter Builder

//! 
//! This is the Builder class of the Builder Pattern
//! The Fighter Builder is an abstract class that will create a fighter given the required statistics (Level, size, etc...)
//! It contains a virtual method that all builder will implement, the setter for ability scores since all buider will have a 
//! different order of importance for the ability scores. All other methods are generic and stay the same for all fighters created.
//! It continas a pointer to a Fighter object that will then be given to the director for the final result.
//!

#pragma once

#include "Fighter.h"

class FighterBuilder{
public:
	Fighter* getBuiltFighter(); //! Accessor for fighter pointer
	void createNewFighter(); //! Method to create a new default fighter
	void setLevel(int level); //! Mutator for the fighter's level
	void setSize(CharacterSize size); //! Mutator for the fighter's size
	void setName(string name); //! Mutator for the name
	void setStyle(FightStyle style); //! Setter for the fighter's style
	virtual void setType() = 0; //! Setter for the fighter type
	virtual void setAbilityScores(int abilityScrs[Character::NO_ABILITY]) = 0; //! Abstract method to set ability scores.
protected:
	Fighter* builtFighter; //! Pointer to fighter object
};