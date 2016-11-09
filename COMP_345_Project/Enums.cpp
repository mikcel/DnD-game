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
ostream& operator<<(ostream& stream, chr::Size size){

	string strSize; //! Variable to hold the contents to output for each size

	//! A switch statement to assign a different value for each size to output.
	switch (size)
	{
		case chr::Size::TINY:
			strSize = "TINY";
			break;
		case chr::Size::FINE:
			strSize = "FINE";
			break;
		case chr::Size::HUGE:
			strSize = "HUGE";
			break;
		case chr::Size::COLOSSAL:
			strSize = "COLOSSAL";
			break;
	}

	return stream << strSize; //! Return the assigned string variable to the stream.
}

//! Method for outputting the Character's Ability
ostream& operator<<(ostream& stream, chr::Abilities ability){
	string strAbility; //! Variable to hold the contents to output for each ability

	//! A switch statement to assign a different value for each ability to output.
	switch (ability)
	{
		case chr::Abilities::STR:
			strAbility = "STRENGTH";
			break;
		case chr::Abilities::DEX:
			strAbility = "DEXTERITY";
			break;
		case chr::Abilities::CONS:
			strAbility = "CONSTITUTION";
			break;
		case chr::Abilities::INTEL:
			strAbility = "INTELLIGENCE";
			break;
		case chr::Abilities::WISD:
			strAbility = "WISDOM";
			break;
		case chr::Abilities::CHA:
			strAbility = "CHARISMA";
			break;
	}

	return stream << strAbility; //! Return the assigned string variable to the stream.
}

//! Method for outputting the Fighter's Style
ostream& operator<<(ostream& stream, fight::Style style){

	string strStyle; //! Variable to hold the contents to output for each ability

	//! A switch statement to assign a different value for each fighting style to output.
	switch (style)
	{
		case fight::Style::ARCHERY:
			strStyle = "ARCHERY";
			break;
		case fight::Style::DEFENSE:
			strStyle = "DEFENSE";
			break;
		case fight::Style::DUELING:
			strStyle = "DUELING";
			break;
	}

	return stream << strStyle; //! Return the assigned string variable to the stream.
}

ostream& operator<<(ostream& stream, item::itemTypes type){

	using namespace item;

	string strType; //! Variable to hold the contents to output for each item type

	//! A switch statement to assign a different value for each fighting style to output.
	switch (type)
	{
		case itemTypes::ARMOR:
			strType = "ARMOR";
			break;
		case itemTypes::BELT:
			strType = "BELT";
			break;
		case itemTypes::BOOTS:
			strType = "BOOTS";
			break;
		case itemTypes::HELMET:
			strType = "HELMET";
			break;
		case itemTypes::RING:
			strType = "RING";
			break;
		case itemTypes::SHIELD:
			strType = "SHIELD";
			break;
		case itemTypes::UNSPECIFIED:
			strType = "UNSPECIFIED";
			break;
		case itemTypes::WEAPON:
			strType = "WEAPON";
			break;
	}

	return stream << strType; //! Return the assigned string variable to the stream.

}

ostream& operator <<(ostream& stream, buff::buffTypes buffType){

	using namespace buff;
	string strType; //! Variable to hold the contents to output for each item type

	//! A switch statement to assign a different value for each fighting style to output.
	switch (buffType)
	{
		case buffTypes::INTELLIGENCE:
			strType = "INTELLIGENCE";
			break;
		case buffTypes::WISDOM:
			strType = "WISDOM";
			break;
		case buffTypes::ARMOR_CLASS:
			strType = "ARMOR CLASS";
			break;
		case buffTypes::STRENGTH:
			strType = "STRENGTH";
			break;
		case buffTypes::CHARISMA:
			strType = "CHARISMA";
			break;
		case buffTypes::CONSTITUTION:
			strType = "CONSTITUTION";
			break;
		case buffTypes::DEXTERITY:
			strType = "DEXTERITY";
			break;
		case buffTypes::ATTACK_BONUS:
			strType = "ATTACK BONUS";
			break;
		case buffTypes::DAMAGE_BONUS:
			strType = "DAMAGE BONUS";
			break;
	}

	return stream << strType; //! Return the assigned string variable to the stream.
}