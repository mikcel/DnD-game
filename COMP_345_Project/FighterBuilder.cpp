//!
//! @file 
//! @brief Implementation file for the Fighter Builder
//!

//!
//! This file contains the implementation for the fighter builder. It contains method to set each stats of the constructed fighter and
//! a virtual method to set ability scores that will be different for each fighter type. It also returns the fighter pointer that
//! was constructed based on the builder type.
//!

#include "FighterBuilder.h"

//! Method to access built fighter
//! @return The pointer to the constructed fighter
Fighter* FighterBuilder::getBuiltFighter(){
	return builtFighter;
}

//! Method to create a new Fighter. It will create a default fighter
//! @return -
void FighterBuilder::createNewFighter(){
	builtFighter = new Fighter();
}

//! Method to set the level of the fighter
//! @param level - The fighter's level
void FighterBuilder::setLevel(int level){
	builtFighter->setLevel(level);
}

//! Method to set the name of the fighter
//! @param name - the fighter's name
void FighterBuilder::setName(string name){
	builtFighter->setName(name);
}

//! Method to set the fighter's size
//! @param size - the Fighter's size
void FighterBuilder::setSize(CharacterSize size){
	builtFighter->setSize(size);
}

//! Method to set the style of the fighter
//! @param style - the fighter's style
void FighterBuilder::setStyle(FightStyle style){
	builtFighter->setStyle(style);
}
