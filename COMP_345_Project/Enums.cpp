//! 
//! @file 
//! @brief Implemetation file for the enumerated methods that override the output stream operator 
//! 

//! 
//! This file implements the three methods declared in the header file. All 3 methods overrides the output stream
//! operator to provide an output to the console for each enumerated type for the project. These will mainly be used when
//! outputting the a Character's or Fighter's stats. The output stream operator is overridden so that the console outputs a 
//! meaningful string instead of a number that represents the enumerated type. 
//! The same principle is used in each method, i.e. a string variable to hold data to be outputted, a switch statement to 
//! determine the enumerated value and returning to the stream the string variable.
//! 

#include <string>
#include <iostream>
#include "Enums.h" //! Include the Enums header file

//! Method for outputing the Character's Size
ostream& operator<<(ostream& stream, CharacterSize size){

	string strSize; //! Variable to hold the contents to output for each size

	//! A switch statement to assign a different value for each size to output.
	switch (size)
	{
	case CharacterSize::TINY:
		strSize = "TINY";
		break;
	case CharacterSize::FINE:
		strSize = "FINE";
		break;
	case CharacterSize::HUGE :
		strSize = "HUGE";
		break;
	case CharacterSize::COLOSSAL:
		strSize = "COLOSSAL";
		break;
	}

	return stream << strSize; //! Return the assigned string variable to the stream.
}

//! Method for outputting the Character's Ability
ostream& operator<<(ostream& stream, CharacterAbility ability){
	string strAbility; //! Variable to hold the contents to output for each ability

	//! A switch statement to assign a different value for each ability to output.
	switch (ability)
	{
	case CharacterAbility::STR:
		strAbility = "STRENGTH";
		break;
	case CharacterAbility::DEX:
		strAbility = "DEXTERITY";
		break;
	case CharacterAbility::CONS:
		strAbility = "CONSTITUTION";
		break;
	case CharacterAbility::INTEL:
		strAbility = "INTELLIGENCE";
		break;
	case CharacterAbility::WISD:
		strAbility = "WISDOM";
		break;
	case CharacterAbility::CHA:
		strAbility = "CHARISMA";
		break;
	}

	return stream << strAbility; //! Return the assigned string variable to the stream.
}

//! Method for outputting the Fighter's Style
ostream& operator<<(ostream& stream, FightStyle style){

	string strStyle; //! Variable to hold the contents to output for each ability

	//! A switch statement to assign a different value for each fighting style to output.
	switch (style)
	{
	case FightStyle::ARCHERY:
		strStyle = "ARCHERY";
		break;
	case FightStyle::DEFENSE:
		strStyle = "DEFENSE";
		break;
	case FightStyle::DUELING:
		strStyle = "DUELING";
		break;
	}

	return stream << strStyle; //! Return the assigned string variable to the stream.
}

//! Method for outputting the Fighter's type
ostream& operator<<(ostream& stream, FighterType type){

	string strType; //! Variable to hold the contents to output for each ability

	//! A switch statement to assign a different value for each fighter type to output.
	switch (type)
	{
		case FighterType::BULLY:
			strType = "BULLY";
			break;
		case FighterType::NIMBLE:
			strType = "NIMBLE";
			break;
		case FighterType::TANK:
			strType = "TANK";
			break;
	}

	return stream << strType; //! Return the assigned string variable to the stream.
}

ostream& operator<<(ostream& stream, ItemType type){

	string strType; //! Variable to hold the contents to output for each item type

	//! A switch statement to assign a different value for each fighting style to output.
	switch (type)
	{
	case ItemType::ARMOR:
		strType = "ARMOR";
		break;
	case ItemType::BELT:
		strType = "BELT";
		break;
	case ItemType::BOOTS:
		strType = "BOOTS";
		break;
	case ItemType::HELMET:
		strType = "HELMET";
		break;
	case ItemType::RING:
		strType = "RING";
		break;
	case ItemType::SHIELD:
		strType = "SHIELD";
		break;
	case ItemType::UNSPECIFIED:
		strType = "UNSPECIFIED";
		break;
	case ItemType::WEAPON:
		strType = "WEAPON";
		break;
	}

	return stream << strType; //! Return the assigned string variable to the stream.

}

ostream& operator <<(ostream& stream, BuffType buffType){

	string strType; //! Variable to hold the contents to output for each item type

	//! A switch statement to assign a different value for each fighting style to output.
	switch (buffType)
	{
	case BuffType::INTELLIGENCE:
		strType = "INTELLIGENCE";
		break;
	case BuffType::WISDOM:
		strType = "WISDOM";
		break;
	case BuffType::ARMOR_CLASS:
		strType = "ARMOR CLASS";
		break;
	case BuffType::STRENGTH:
		strType = "STRENGTH";
		break;
	case BuffType::CHARISMA:
		strType = "CHARISMA";
		break;
	case BuffType::CONSTITUTION:
		strType = "CONSTITUTION";
		break;
	case BuffType::DEXTERITY:
		strType = "DEXTERITY";
		break;
	case BuffType::ATTACK_BONUS:
		strType = "ATTACK BONUS";
		break;
	case BuffType::DAMAGE_BONUS:
		strType = "DAMAGE BONUS";
		break;
	}

	return stream << strType; //! Return the assigned string variable to the stream.
}