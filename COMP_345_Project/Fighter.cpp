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
#include <iomanip>
using namespace std;

#include "Fighter.h"

//! Constructor: Default Constructor
//! Sets Fighter's name to "unknown", all abilities to 3, the fighting style by default set to archery, the level and the size
//! It invokes one of the Parametrized constructor to initialize each data member (to avoid code repetition)
Fighter::Fighter() : Fighter("Unknown", 3, 3, 3, 3, 3, 3, FightStyle::ARCHERY, 1, CharacterSize::TINY){
	type = FighterType::BULLY;
}

Fighter::Fighter(string chrName) : Fighter(chrName, 3, 3, 3, 3, 3, 3, FightStyle::ARCHERY, 1, CharacterSize::TINY){
	type = FighterType::BULLY;
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
: Character(chrName, (str == 18 ? str : str++), (dex == 18 ? dex : dex++), (cons == 18 ? cons : cons++), intel, wisd, cha, chrLevel, chrSize){

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

Fighter::Fighter(Fighter& copyFight) : Character(dynamic_cast<Character&>(copyFight)){

	style = copyFight.getStyle();
	type = copyFight.getType();

}

//! Destructor for the fighter class
Fighter::~Fighter(){

}

//! Accessor method for the fighting style
//! @return fighter's style of enumerated type style
FightStyle Fighter::getStyle(){
	return style;
}

//! Accessor method for the fighter type
//! @return fighter's type of enumerated type type
FighterType Fighter::getType(){
	return type;
}

//! Mutator method for the fighter's type
//! @param style - the Fighter's new type of enumerated type 
void Fighter::setType(FighterType type){
	this->type = type;
}

//! Mutator method for the fighter's style
//! @param style - the Character's new style of enumerated type style
void Fighter::setStyle(FightStyle chrStyle){
	style = chrStyle;
}

//! Attack method for the Fighter's class
//! @param Reference to Character object
//! @return true - Opponent not dead, false - Opponent dead
bool Fighter::attack(Character &chr){

	int additionalAttack = 0;
	int additionalDamage = 0;

	//! Search if fighter is using melee or range weapon and add to attack depending on fighting style
	if (getCurrentWornItems()->getContents()[(int)ItemType::WEAPON]->getItemTypes() != ItemType::UNSPECIFIED){
		
		Weapon* weapon = (Weapon*)(getCurrentWornItems()->getItem(getCurrentWornItems()->getContents()[(int)ItemType::WEAPON]->getItemName()));
		if (weapon != NULL){
			//! Check range and melee weapon
			if (style==FightStyle::ARCHERY && weapon->getRange()> 1)
				additionalAttack = 2;

			if (style == FightStyle::DUELING && weapon->getRange() == 1)
				additionalDamage = 2;
		}

	}

	//! Counters for multiple attacks
	int calcLevel = getLevel();
	int count = 0;

	do{
		count++;
		cout << "\nAttack " << count << endl;
		int d20Roll = Dice::roll("1d20");
		//! Subtract armor class because Character is protected by Armor, add the attack bonus and the attack rounds per level
		int totalAttackBonus = (calcAttackBonus() + calcLevel + d20Roll + additionalAttack) - chr.getArmorClass();
		//! Log
		cout << "\nTrying to attack." << endl;
		cout << "Calculating attack roll ((Attack Bonus + Level + d20Roll + Fighter's additional attack) - Opponent's AC) : ("
			<< calcAttackBonus() << " + " << calcLevel << " + " << d20Roll << " + " << additionalAttack << ") - " << chr.getArmorClass() << endl;
		cout << "Attack roll: " << totalAttackBonus << endl;
		if (totalAttackBonus > 0){
			//! Calculate the damage cause to the opponent
			int d8Roll = Dice::roll("1d8");
			int totalDmgBonus = calcDamageBonus() +d8Roll + additionalDamage;
			//!Log
			cout << chr.getName() << " can be attacked." << endl;

			cout << "Calculating damage roll (Damage Bonus + d8Roll + Fighter's addition damage): "
				<< calcDamageBonus() << " + " << d8Roll << " + " << additionalDamage << endl;

			cout << "Hitting and causing a damage of " << totalDmgBonus << endl;
			if (chr.hit(totalDmgBonus)==0)//! Hit the opponent
				return false; 
		}
		else{
			cout << "Attack Missed. " << chr.getName() << " protected by Armor Class." << endl;
		}
		calcLevel -= 5; //! Decrease counter by 5 until reach 0 or below
	} while (calcLevel > 0);

	//system("pause");

	return true;

}

void Fighter::saveCharacter(){

	ofstream outStream("SaveFiles/Characters/" + getName() + ".txt", ios::out);

	outStream << "fighter\n" << getName() << "\n"<< to_string(getLevel()) << "\n" << to_string((int)getSize()) << "\n" << (int)style << "\n" << (int)type << "\n";

	for (int i = 0; i < NO_ABILITY; i++){
		outStream << to_string(getOneAbilityScore((CharacterAbility)i)) << "\n";
	}

	outStream << "backpack\n";
	for (auto i : getBackpackContents()->getContents()){
		outStream << i->getItemName() << "\n";
	}

	outStream << "wornItem\n";
	for (auto i : getCurrentWornItems()->getContents()){
		outStream << i->getItemName() << "\n";
	}

	outStream.close();

}

//! Overloading the output operator for displaying the fighter's stats
//! @param reference to output stream
//! @param reference to fighter object and cannot change data members since constant
//! @return reference to passed stream
ostream& operator<<(ostream& stream, const Fighter& fighter){
	
	const int labelSpace = 9;
	const int abilitylabelSpace = 19;
	const int abilityScrSpace = 8;
	const int abilityModSpace = 5;

	stream << "-------------------------------------------------------------------------------------------------------\n";
	stream << setw(30) << right << fighter.getName() << "'s STATS\n";
	stream << "-------------------------------------------------------------------------------------------------------\n";

	//! Specific output format for a Character object
	stream << "\nName: " << fighter.getName() <<
		"\nLevel: " << fighter.getLevel() <<
		"\nSize: " << fighter.getSize() << 
		"\nStyle: " << fighter.style << 
		"\nType: " << fighter.type << endl;

	stream << "\n\nAbility \t" << "Score\t Modifier\n";

	stream << CharacterAbility::STR << "\t" << fighter.getOneAbilityScore(CharacterAbility::STR) << "\t" << fighter.getOneAbilityModifier(CharacterAbility::STR) << "\n" <<
		CharacterAbility::DEX << "\t" << fighter.getOneAbilityScore(CharacterAbility::DEX) << "\t" << fighter.getOneAbilityModifier(CharacterAbility::DEX) << "\n" <<
		CharacterAbility::CONS << "\t" << fighter.getOneAbilityScore(CharacterAbility::CONS) << "\t" << fighter.getOneAbilityModifier(CharacterAbility::CONS) << "\n" <<
		CharacterAbility::INTEL << "\t" << fighter.getOneAbilityScore(CharacterAbility::INTEL) << "\t" << fighter.getOneAbilityModifier(CharacterAbility::INTEL) << "\n" <<
		CharacterAbility::WISD << "\t\t" << fighter.getOneAbilityScore(CharacterAbility::WISD) << "\t" << fighter.getOneAbilityModifier(CharacterAbility::WISD) << "\n" <<
		CharacterAbility::CHA << "\t" << fighter.getOneAbilityScore(CharacterAbility::CHA) << "\t" << fighter.getOneAbilityModifier(CharacterAbility::CHA) << "\n";

	stream << "\n\nCurrent Hit Points(HP): " << fighter.getCurrentHitPoints() <<
		"\nDamage Bonus: " << fighter.calcAttackBonus() <<
		"\nAttack Bonus: " << fighter.calcAttackBonus() <<
		"\nArmor Class: " << fighter.getArmorClass() <<
		"\n\nBackpack holding: \n\n" << *(fighter.getBackpackContents());
	stream << "\n\nWearing Items: \n\n" << *(fighter.getCurrentWornItems());

	stream << "-------------------------------------------------------------------------------------------------------\n";

	return stream;
}