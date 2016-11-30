//! 
//! @file 
//! @brief Header file for the Character Director
//!

//! 
//! This file defines the Character Director class. It specifies method to construct a fighter based on a given level or
//! on other inputs. It has a pointer towards a fighter builder which contains method to construct the fighter. The character 
//! Director only states which method needs to be used to construct a fighter.
//! 

#pragma once

#include "FighterBuilder.h"

class CharacterDirector{
public:
	void setFighterBuilder(FighterBuilder* fighterTypeBuild); //! Setter for the fighter builder
	Fighter* getFighter(); //! Get the constructed method
	void constructFighter(string name, int level, FightStyle fightStyle, CharacterSize chrSize); //! Method to construct a fighter with a name, level,style and size
	void constructFighter(int level); //! Method to build a fighter with level provided
private:
	FighterBuilder* typeBuilder; //! Pointer towards fighter builder
	int rollDice(); //! Private method for getting an ability score
};