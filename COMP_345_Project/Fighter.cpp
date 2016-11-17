//! 
//! @file 
//! @brief Implementation file for the Fighter Class.  
//! 

//! This file contains implementation of the different Fighter class constructor, the accessor and mutator for the fighting
//! style fo the Fighter and some other service methods. It  includes commen c++ libraries such as sring and iostream for string 
//! data variable and the output stream respectively. It also imports the algorithm library for string com[arison purposes. 
//! The d20 rules can be found in some parts fo this file for example te fighting syle influence on the Fighter's stats or when
//! attacking another player. Some new rules are also implemented.
//! 

#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
#include "Fighter.h"

//! Set the constatant static variable for the default hit dice to "1d10" for fighters
const string Fighter::DEFAULT_HIT_DICE = "1d10";

//! Constructor: Default Constructor
//! Sets Fighter's name to "unknown", all abilities to 3, the fighting style by default set to archery, the level and the size
//! It invokes one of the Parametrized constructor to initialize each data member (to avoid code repetition)
Fighter::Fighter() : Fighter("Unknown", 3, 3, 3, 3, 3, 3, FightStyle::ARCHERY, 1, CharacterSize::TINY){
	/*Intentionally left empty*/
}

//! Constructor: Parametrized constructor 1
//! This constructor takes the name, an array of 6 abilities, the fighting style, the level and the Fighter's size
//! It then calls the other parametrized constructor to passed these data to data members. It indexes the array passed
//! to obtain each specific ability by using the enumerated type. 
Fighter::Fighter(string chrName, int chrAbilityScores[Character::NO_ABILITY], FightStyle chrStyle, int chrLevel, CharacterSize chrSize) : Fighter(chrName, chrAbilityScores[(int)CharacterAbility::STR],
	chrAbilityScores[(int)CharacterAbility::DEX], chrAbilityScores[(int)CharacterAbility::CONS], chrAbilityScores[(int)CharacterAbility::INTEL], chrAbilityScores[(int)CharacterAbility::WISD],
	chrAbilityScores[(int)CharacterAbility::CHA], chrStyle, chrLevel, chrSize){
	/*Intentionally left empty*/
}

//! Constructor: Parametrized constructor 2
//! This constructor passes the name, the 6 abilities, the fighting style, the level and the size to the respective data members
//! This is the only constructor that calls he super class constructor and passes the respective parameters. It passes the name and
//! the default hit dice for the fighter. Note that the strength, the dexterity and the constitution are incremented by 1 if not 
//! already 18 as it is a characteristics of the Fighter class in the d20 rule. Other data members are initalized as usual.
Fighter::Fighter(string chrName, int str, int dex, int cons, int intel, int wisd, int cha, FightStyle chrStyle, int chrLevel, CharacterSize chrSize)
: Character(chrName, DEFAULT_HIT_DICE, (str == 18 ? str : str++), (dex == 18 ? dex : dex++), (cons == 18 ? cons : cons++), intel, wisd, cha, chrLevel, chrSize){

	//! set the character's style
	style = chrStyle;

	//! Get the constituion modifier
	int consMod = Character::getOneAbilityModifier(CharacterAbility::CONS);

	//! Check if the constitution modifier is +ve
	//! If true, add the constitution modifier to the HP
	if (consMod>=1)
		Character::setCurrentHitPoints(Character::getCurrentHitPoints() + consMod);

	//! If fighter's style to defense, increment the armor class
	if (style == FightStyle::DEFENSE)
		Character::incrementArmorClass(1);

}

//! Destructor for the fighter class
//! It destroys also the super object that were created when the fighter's class was initialized.
Fighter::~Fighter(){
	Character::~Character();
}

//! Accessor method for the fighting style
//! @return fighter's style of enumerated type style
FightStyle Fighter::getStyle(){
	return style;
}

//! Mutator method for the fighter's style
//! @param style - the Character's new style of enumerated type style
void Fighter::setStyle(FightStyle chrStyle){
	style = chrStyle;
}

//! Method to increment the fighter's level (overridden method of the Characterès class)
//! @param int - the hit dice roll no
void Fighter::incrementLevel(int hitRoll){
	Character::incrementLevel(hitRoll); //! Increment the level contained in the super class, Character
	Character::setHitDice(Character::getLevel() + "d10"); //! Change the hitdice (increment it by the new level)
	cout << "New Hit Dice: " << Character::getHitDice(); //! Output the new hit dice
}

//! Attack method for the Fighter's class
//! @param Reference to Character object
//! @param damage caused
//! @param weapon used
//! @return 0 - if character died (HP=0), 1 - Character was hit (Not protected by armor class) & 2 - Character was not hit
int Fighter::attack(Character &chr){

	//! Check if character is not the calling object
	if (&chr == this){
		cout << "\nYou cannot attack yourself." << endl;
		return 1;
	}

	//! Check style used based on the d20 rules
	//! If style is archery or dueling, increment damage by 2
	if (style == FightStyle::ARCHERY || style == FightStyle::DUELING){
		cout << "\nSince " << getName() << " is a fighter, 2 will be added to damage." << endl;
	}

	//! Call the Character's class attack method and return its return value
	return Character::attack(chr, 2);

}

void Fighter::saveCharacter(){

	ofstream outStream("SaveFiles/Characters/" + getName() + ".txt", ios::out);

	outStream << "fighter\n" << getName() << "\n" << getHitDice() << "\n"<< to_string(getLevel()) << "\n" << to_string((int)getSize()) << "\n" << (int)style << "\n";

	for (int i = 0; i < NO_ABILITY; i++){
		outStream << to_string(getOneAbilityScore((CharacterAbility)i)) << "\n";
	}

	outStream << "backpack\n";
	for (auto i : getBackpackContents()){
		outStream << i->getItemName() << "\n";
	}

	outStream << "wornItem\n";
	for (auto i : getCurrentWornItems()){
		outStream << i->getItemName() << "\n";
	}

	outStream.close();

}

//! Overloading the output operator for displaying the fighter's stats
//! @param reference to output stream
//! @param reference to fighter object and cannot change data members since constant
//! @return reference to passed stream
ostream& operator<<(ostream& stream, const Fighter& fighter){
	const Character& chr = fighter; //! Creates a reference of type Character and assignt he fighter's object to it.
	return stream << chr << "Style: " << fighter.style <<endl; //! Output the Character's stats first and then output the fighter's style
}