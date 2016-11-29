//!
//! @file
//! @brief Implementation file for the nimble builder
//!

//! 
//! This file implements the only method of the nimble builder, the set ability scores method. The method will sort the given array of
//! random ability scores and set the numbers to the respective ability scores in a particular order.
//!

#include "NimbleBuilder.h"

//! Method to set the fighter's type to nimble
void NimbleBuilder::setType(){
	builtFighter->setType(FighterType::NIMBLE);
}

//! Method to set the ability scores of a nimble
//! @param abilityScrs array of randomly generated ability scores
void NimbleBuilder::setAbilityScores(int abilityScrs[Character::NO_ABILITY]){

	//! Sorting of the array
	for (int i = 0; i < Character::NO_ABILITY; i++){
		for (int j = 0; j < Character::NO_ABILITY; j++){
			if (i != j && abilityScrs[i] > abilityScrs[j]){
				int temp = abilityScrs[i];
				abilityScrs[i] = abilityScrs[j];
				abilityScrs[j] = temp;
			}
		}
	}

	//! Set the scores in the following order of importance: dexterity, constitution, strength, intelligence, charisma and wisdom
	builtFighter->setAbilityScores(abilityScrs[2], abilityScrs[0], abilityScrs[1], abilityScrs[3], abilityScrs[4], abilityScrs[5]);

}