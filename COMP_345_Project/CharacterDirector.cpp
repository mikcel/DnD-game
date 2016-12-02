//! 
//! @file 
//! @brief Implementation for Character Director class
//!

//! 
//! This file contains the implementation for the Character director class. The director will only create a fighter based on the inputs
//! and the fighter builder type provieded. That is, if the builder is a bully, it will create a bully builder by calling methods from the
//! Fighter builder class but also the set ability score for the bully builder which will determine in which order the bully builder should be
//!

#include "CharacterDirector.h"

//! Setter for the Fighter builder
//! @param fighterTypeBuild - pointer to the fighterbuilder which wants to be built
void CharacterDirector::setFighterBuilder(FighterBuilder* fighterTypeBuild){
	typeBuilder = fighterTypeBuild;
}

//! Method to get the constructed fighter from the respective builder
//! @return a pointer towards a built fighter from the fighter builder
Fighter* CharacterDirector::getFighter(){
	return typeBuilder->getBuiltFighter();
}

//! Method to construct a fighter based on the name, level, fighting style and character size
//! @param name the name of the fighter
//! @param level the fighter's level
//! @param fightStyle the fighting style of the fighter
//! @param chrSize the Fighter's size
void CharacterDirector::constructFighter(string name, int level, FightStyle fightStyle, CharacterSize chrSize){

	//! Get siz random ability scores by rolling a 4d6 die and selecting the 3 highest
	int abilityScrs[Character::NO_ABILITY];
	for (int i = 0; i < Character::NO_ABILITY; i++){
		abilityScrs[i] = rollDice();
	}

	//! Create the fighter and set the appropriate characteristics
	typeBuilder->createNewFighter();
	typeBuilder->setAbilityScores(abilityScrs);
	typeBuilder->setName(name);
	typeBuilder->setLevel(level);
	typeBuilder->setSize(chrSize);
	typeBuilder->setStyle(fightStyle);
	typeBuilder->setType();

}

//! Method to construct the fighter with only the level
//! @param level the fighter's level
void CharacterDirector::constructFighter(int level){

	//! Generate 6 ability scores by rolling a 4d6 and selecting the 3 highest
	int abilityScrs[Character::NO_ABILITY];
	for (int i = 0; i < Character::NO_ABILITY; i++){
		abilityScrs[i] = rollDice();
	}
	//! Create the fighter and set the appropriate characteristics
	typeBuilder->createNewFighter();
	typeBuilder->setAbilityScores(abilityScrs);
	typeBuilder->setLevel(level);

}

//! Method to get a random number by rolling a 4d6 dice
//! @return a number between 3 and 18
int CharacterDirector::rollDice(){

	//! Calculate the sum of all the rolls of a 1d6 and keep track of the lowest
	int diceScore = 0;
	int lowest = 24;
	for (int i = 0; i < 4; i++){
		int roll = Dice::instance().roll("1d6");
		diceScore += roll;
		if (roll < lowest)
			lowest = roll;
	}
	return diceScore - lowest; //! remove the lowest to get only the 3 highest rolls

}