//! 
//! @file 
//! @brief Implementation file for the Character Class.  
//! 

//! 
//! The file contains the implementation of the Character class' constructors, getter and setters, and other service
//! methods. It includes several common c++ libraries such as string ans iostream for string data members and for 
//! console output respectively. 
//! The d20 rules are respected in this class, for instance the calculation of the armor class or the generation of the 
//! ability modifiers. Moreover, some new rules were implemented such as the calculation of damage upon a hit or the damage bonus.
//!

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
using namespace std;

#include "Character.h"

//! Default Constructor. 
//! Sets all abilities to 3, name to "Unknown", level to 1 and size to Tiny.
//! It invokes one of the parametrized constructor (see below) to initailize each data member
Character::Character() : Character("Unknown", 3, 3, 3, 3, 3, 3, 1, CharacterSize::TINY){

	/*Intentionally left empty*/

}

//! Constructor with name
//! Used to facilitate map construction from a map file
Character::Character(string chrName):Character(chrName, 3, 3, 3, 3, 3, 3, 1, CharacterSize::TINY)
{

}
//! Constructor: gets the name, an array of ability scores, the level and the size.
//! It invokes the other parametrized constructor to set each variable.
//! Note: to initialize each ability score, each of them is taken from the passed array using the enum type to index the array.
Character::Character(string chrName, int chrAbilityScores[NO_ABILITY], int chrLevel, CharacterSize chrSize) :
Character(chrName, chrAbilityScores[(int)CharacterAbility::STR], chrAbilityScores[(int)CharacterAbility::DEX], chrAbilityScores[(int)CharacterAbility::CONS], chrAbilityScores[(int)CharacterAbility::INTEL],
chrAbilityScores[(int)CharacterAbility::WISD], chrAbilityScores[(int)CharacterAbility::CHA], chrLevel, chrSize){
	/*Intentionally left empty*/
}

Character::Character(const Character &copyChar) {
	this->name = copyChar.name;
	this->level = copyChar.level;
	this->size = copyChar.size;

	setAbilityScores(copyChar.getOneAbilityScore(CharacterAbility::STR), copyChar.getOneAbilityScore(CharacterAbility::DEX),
		copyChar.getOneAbilityScore(CharacterAbility::CONS), copyChar.getOneAbilityScore(CharacterAbility::INTEL), 
		copyChar.getOneAbilityScore(CharacterAbility::WISD), copyChar.getOneAbilityScore(CharacterAbility::CHA));

	int hp = (abilityModifiers[(int)CharacterAbility::CONS] + Dice::roll("1d10")) * level;
	currentHitPoints = hp;
	maxHP = hp;
	//! Invokes the method to calculate the armor class
	calcArmorClass();

	//! Initialise the two items container
	backpack = new ItemContainer(*copyChar.backpack);
	currentWornItems = new ItemContainer(*copyChar.currentWornItems);

}
//! Constructor: passes values to the name, the hit dice, the size, the level and each ability score
Character::Character(string chrName, int str, int dex, int cons, int intel, int wisd, int cha, int chrLevel, CharacterSize chrSize){

	//! Sets name, size, level and hit dice
	name = chrName;
	level = chrLevel;
	size = chrSize;

	//! Call the setter method for the ability scores
	setAbilityScores(str, dex, cons, intel, wisd, cha);

	int diceRoll = Dice::roll("1d10");
	currentHitPoints = (abilityModifiers[(int)CharacterAbility::CONS] + diceRoll) * level;
	maxHP = currentHitPoints;

	//! Invokes the method to calculate the armor class
	calcArmorClass();

	//! Initialise the two items container
	backpack = new ItemContainer(ContainerType::BACKPACK);
	currentWornItems = new ItemContainer(ContainerType::WORN_ITEM);

}

//! Default Destructor
Character::~Character(){
	delete backpack;
	delete currentWornItems;
}

//! Accessor for the Character's name. 
//! @return name
string Character::getName() const{
	return name;
}

//! Accessor for the Character's level.
//! @return level
int Character::getLevel() const{
	return level;
}

//! Accessor for the Character's Size.
//! @return size
CharacterSize Character::getSize() const{
	return size;
}

//! Accessor for one ability score
//! @param ability - Of type abilities from enumerated type
//! @return integer, the ability score passed as parameter
int Character::getOneAbilityScore(CharacterAbility ability) const{

	//! Get ability by using the array index (enum type) passed as parameter 
	return abilityScores[(int)ability];

}

//! Accessor for all ability scores
//! @return a pointer to a copy array containing all the ability scores
int* Character::getAllAbilityScores() const{

	int *arrayPointer; //! Pointer for new array
	int arrayCopy[NO_ABILITY]; //! New array to be returned

	arrayPointer = arrayCopy; //! Make pointer reference the newly created array

	//! For loop to copy each element of array abilities to newly created array
	for (int i = 0; i < Character::NO_ABILITY; i++){
		arrayCopy[i] = abilityScores[i];
	}

	//! return the pointer to the new array
	return arrayPointer;
}

//! Accessor for one ablity modifier.
//! @param ability - of type CharacterAbility (enumerated) to index array of ability modifiers
//! @return the ability modifer asked for (parameter)
int Character::getOneAbilityModifier(CharacterAbility ability) const{

	//! Return the ability modifier by indexing the array to the ability passed (enum type)
	return abilityModifiers[(int)ability];

}

//! Accessor method for all ability modifiers
//! @return a pointer to a copy array of the ability mofidiers
int* Character::getAllAbilityModifiers() const{

	int *arrayPointer; //! Declare pointer
	int arrayCopy[NO_ABILITY]; //! Declare array to be returned

	arrayPointer = arrayCopy; //! Pointer points to new array

	//! For loop copies each modifier to the new array
	for (int i = 0; i < sizeof(abilityModifiers); i++){
		arrayCopy[i] = abilityModifiers[i];
	}

	return arrayPointer; //! Return the pointer to en the newly created array
}

//! Accessor method for the Character's HP
//! @return Current hit points of the Character object
int Character::getCurrentHitPoints() const{
	return currentHitPoints;
}

int Character::getMaxHP() const{
	return maxHP;
}

//! Getter for Armor Class
//! @return Armor Class
int Character::getArmorClass() const{
	return armorClass;
}

//! Setter for the Character's name
//! @param string - Character's new name
void Character::setName(string chrName){

	if (name != "") //! Check if new name is not empty
		name = chrName;
	else{ //! If incorrect name, output error message
		cout << "Incorrect Name";
	}
}

//! Mutator for the Character's level
//! @param int new Character level
void Character::setLevel(int chrLevel){
	if (chrLevel > 0){ //! Check that new level is positive
		level = chrLevel;

		int diceRoll = Dice::instance().roll("1d10");
		currentHitPoints = (abilityModifiers[(int)CharacterAbility::CONS] + diceRoll) * level;
		maxHP = currentHitPoints;
	}
	else{ //! Incorrect message is output if negative new level
		cout << "Incorrect Level.";
	}
}

//! Mutator for the Character's size
//! @param Size enumerated size as new Character's size
void Character::setSize(CharacterSize chrSize){
	size = chrSize;
	calcArmorClass();
}

//! Mutator method for ability scores
//! @param ints 6 integers for each ability
void Character::setAbilityScores(int str, int dex, int cons, int intel, int wisd, int cha){
	//!Set each ability score to the passed ones by indexing the array using the abilities enumerated type
	abilityScores[(int)CharacterAbility::STR] = str;
	abilityScores[(int)CharacterAbility::DEX] = dex;
	abilityScores[(int)CharacterAbility::CONS] = cons;
	abilityScores[(int)CharacterAbility::INTEL] = intel;
	abilityScores[(int)CharacterAbility::WISD] = wisd;
	abilityScores[(int)CharacterAbility::CHA] = cha;
	generateAbilityModifiers();
}

//! Mutator for the all ability scores
//! @param array - interger array to copy from elements for each score
void Character::setAbilityScores(int chrAbilityScores[NO_ABILITY]){

	//! Copy each element from passed array to ability score array
	for (int i = 0; i < NO_ABILITY; i++){
		abilityScores[i] = chrAbilityScores[i];
	}
	generateAbilityModifiers();

}

//! Setter for Character's HP
//! @param int Caracter's new hit point
void Character::setCurrentHitPoints(int chrHitPt){
	currentHitPoints = chrHitPt;
}

//! Service method to calculate Armor Class
//! @param -
void Character::calcArmorClass(){
	//! Formula for Armor Class: 10 + size mofifier + dexterity modifier
	armorClass = 10 + getSizeModifier() + abilityModifiers[(int)CharacterAbility::DEX];
}

//! Service Method to calculate characters' damage bonus
//! @param - 
int Character::calcDamageBonus() const{

	//! Formula: Strength modifier + level
	int bonus = abilityModifiers[(int)CharacterAbility::STR] + level;

	if (currentWornItems->getContents()[(int)ItemType::WEAPON]->getItemTypes() != ItemType::UNSPECIFIED){

		Item *weapon = currentWornItems->getItem(currentWornItems->getContents()[(int)ItemType::WEAPON]->getItemName());

		vector<Buff> buff = weapon->getBuffs();
		for (auto i : buff){
			if (i.getBuffType() == BuffType::DAMAGE_BONUS)
				bonus += i.getBuffAmount();
		}

	}

	//! Formula above can return negative values because of size modifier
	//! Check if the calculate returned a negative value
	//! If +ve set damage bonus to calculated one, else set to 0
	if (bonus > 0)
		return bonus;
	else
		return 0;
}

//! Service Method to calculate Character's Attack Bonuss
//! @param string - Weapon type that the Character's holds 
int Character::calcAttackBonus() const{

	int attackBonus = 0;
	//! Check if size mod is greater than level so as not to get -ve attack bonus
	if (getSizeModifier() > 0)
		attackBonus = getSizeModifier();

	if (currentWornItems->getContents()[(int)ItemType::WEAPON]->getItemTypes() != ItemType::UNSPECIFIED){

		Weapon* weapon = (Weapon*)(currentWornItems->getItem(currentWornItems->getContents()[(int)ItemType::WEAPON]->getItemName()));
		if (weapon != NULL){
			//! Check range and melee weapon

			if (weapon->getRange()==1)  
				attackBonus += abilityModifiers[(int)CharacterAbility::STR];//! Melee weapon
			else
				attackBonus += abilityModifiers[(int)CharacterAbility::DEX];//! Range weapon

			vector<Buff> buff = weapon->getBuffs();
			for (auto i : buff){
				if (i.getBuffType() == BuffType::ATTACK_BONUS)
					attackBonus += i.getBuffAmount();
			}

		}

	}

	//! In case attack Bonus is -ve
	if (attackBonus < 0)
		return 0;
	else
		return attackBonus;

}

//! Method to calculate the ability modifier for each ability score
//! @param none
void Character::generateAbilityModifiers(){

	//! Check size of ability scores array ( If all scores were entered before calculating the respective modifiers)
	if (sizeof(abilityScores) / 4 == 0)
		cout << "No scores have been entered yet.";
	else{
		//! For each ability score, generate a modifier by subtracting 10, dividing by two
		//! and taking the floor of the results. This si the formula provided by the d20 rule.
		for (int i = 0; i < NO_ABILITY; i++){
			double modifier = (abilityScores[i] - 10) / 2.0;
			abilityModifiers[i] = floor(modifier);
		}
	}

}

//! Method to check if a newly created characer is valid or not
//! @return true if the Character is valid by evaluating different conditions and false if not
bool Character::validateNewCharacter(){

	//! Check if level is -ve
	if (level <= 0){
		cout << "\nIncorrect Level entered.";
		return false;
	}

	//! Validate if each ability score is in the range 3-18
	for (int i = 0; i < NO_ABILITY; i++){
		if (abilityScores[i]<3 || abilityScores[i]>18){
			cout << "\nIncorrect " << CharacterAbility(i) << " entered.";
			return false;
		}
	}

	//! Return true if everthing is valid
	return true;

}

//! Function to reduce damage of Character if gets hit
//! @param int representing the damage caused to the character
//! @return 0 - if character died (HP=0), 1 - Character was hit 
int Character::hit(int dmg){

	int returnVal = 0;
	if (dmg >= currentHitPoints){  //! If new Damage is more than current HP, character dies.
		cout << name << " hit by " << dmg << " damage. \nNot enough to be protected by armor and above HP. Game Over for " << getName() << endl;
		currentHitPoints = 0;
		returnVal = 0;
	}
	else{ //! If protected by armor class, no damage
		currentHitPoints -= dmg; //! Subtract damage from HP
		cout << name << " hit by " << dmg << " damage.\n"
			<< name << "'s Current Hit Points (HP): " << currentHitPoints << endl;
		returnVal = 1;
	}
	return returnVal;

}

//! Function to attack another Character
//! @param Character - Representing the Character wanted to attack
//! @return true - Opponent not dead, false - Opponent dead
bool Character::attack(Character &chr){

	//! Counters for multiple attacks
	int calcLevel = level;
	int count = 0;
	do{
		count++;
		cout << "Attack " << count << endl;
		int d20Roll = Dice::instance().roll("1d20");
		//! Subtract armor class because Character is protected by Armor, add the attack bonus and the attack rounds per level
		int totalAttackBonus = (calcAttackBonus() + calcLevel + d20Roll) - chr.armorClass;
		cout << "\nTrying to attack." << endl;
		string log = "Calculating attack roll ((Attack Bonus + Level + d20Roll) - Opponent's AC) : (" + to_string(calcAttackBonus()) + " + " + to_string(calcLevel) + " + " + to_string(d20Roll) + ") - " + to_string(chr.getArmorClass()) + "\n";
		
		
		cout << "Attack roll: " << totalAttackBonus << endl;
		if (totalAttackBonus > 0){
			//! Calculate damage caused to opponent		
			int d8Roll = Dice::instance().roll("1d8");
			int totalDmgBonus = calcDamageBonus() + d8Roll ;
			//!Log
			cout << chr.getName() << " can be attacked." << endl;

			cout << "Calculating damage roll (Damage Bonus + d8Roll): "
				<< calcDamageBonus() << " + " << d8Roll << " + "  << endl;

			cout << "Hitting and causing a damage of " << totalDmgBonus << endl;
			if (chr.hit(totalDmgBonus)==0)//! Hit the opponent with damage calculated
				return false; 
		}
		else{
			cout << "Attack Missed. Opponent protected by Armor Class.";
		}
		calcLevel -= 5; //! Decrease by 5 for each level and attack
	} while (calcLevel > 0);

	//system("pause");

	return true;//! return true if opponent did not died

}

//! Function that determine size modifier for a character object
//! @return the size modifier of the character depending on his size

int Character::getSizeModifier() const{

	//! A switch statement is implemented for the different sizes as the size is an enumerated type
	//! It is easier to understand the code using an enumerated combined with a switch statement.
	//! Return a number determine by the d20 rules for each size
	switch (size)
	{
	case CharacterSize::FINE:
		return 8;
	case CharacterSize::TINY:
		return 2;
	case CharacterSize::HUGE:
		return -2;
	case CharacterSize::COLOSSAL:
		return -8;
	default:
		return 0;
	}
}

//! Function that can be used to increment the level of the Character and at the same time increases the HP
void Character::incrementLevel(){
	level++; //! Increment level by 1

	//! Calculate new hit points
	//! Take constitution modifier and add with the hit dice roll
	int increment = abilityModifiers[(int)CharacterAbility::CONS] + Dice::roll("1d10");
	currentHitPoints += increment;
	maxHP += increment;
	//! Output new information
	cout << "Level " << level << " reached." << endl;
	cout << "Current HP: " << currentHitPoints << endl;
}

//! Function used to unequip an item from the Character and put them back to the backpack
//! @param int - representing the roll of the Character's hit dice
bool Character::takeOffItem(Item *objItem){

	if (currentWornItems->unequipItem(objItem->getItemName(), backpack)){
		takeOffBuff(objItem->getBuffs());
		return true;
	}
	return false;

}

//! Function that takes an item and wear NOTE: WILL BE LATER BETTER IMPLEMENTED WHEN MERGING THE PROJECT
//! @param Item - New item to wear
//! @return true - successsfully worn, false otherwise
bool Character::wearItem(Item *objItem){

	if (currentWornItems->getContents()[(int)objItem->getItemTypes()]->getItemTypes() != ItemType::UNSPECIFIED){
		takeOffBuff(currentWornItems->getContents()[(int)objItem->getItemTypes()]->getBuffs());
	}

	if (currentWornItems->equipItem(objItem->getItemName(), backpack)){
		vector<Buff> itemBuff = objItem->getBuffs();
		for (auto i : itemBuff){
			switch (i.getBuffType()){
				case BuffType::ARMOR_CLASS:{
											   armorClass += i.getBuffAmount();
											   break;
				}
				case BuffType::INTELLIGENCE:{
												abilityModifiers[(int)CharacterAbility::INTEL] += i.getBuffAmount();
												break;
				}
				case BuffType::WISDOM:{
										  abilityModifiers[(int)CharacterAbility::WISD] += i.getBuffAmount();
										  break;
				}
				case BuffType::STRENGTH:{
											abilityModifiers[(int)CharacterAbility::STR] += i.getBuffAmount();
											break;
				}
				case BuffType::CONSTITUTION:{
												abilityModifiers[(int)CharacterAbility::CONS] += i.getBuffAmount();
												break;
				}
				case BuffType::CHARISMA:{
											abilityModifiers[(int)CharacterAbility::CHA] += i.getBuffAmount();
											break;
				}
				case BuffType::DEXTERITY:{
											 abilityModifiers[(int)CharacterAbility::DEX] += i.getBuffAmount();
											 break;
				}
			}
		}
		return true;
	}
	return false;
}

//! Function that takes an item and container type and switches it NOTE: WILL BE LATER BETTER IMPLEMENTED WHEN MERGING THE PROJECT
//! @param Item - New item to wear, containerType (backpack or currently worn item)
//! @return true - successsfully switched, false otherwise
bool Character::storeItem(Item *objItem)
{
	if (!objItem->validateItem())
		return false;

	backpack->addItem(objItem);

	return true;
}

//! Function to get all the items that are currently in the Character's backpack 
//! @return Copy of the backpack item container
ItemContainer* Character::getBackpackContents() const{

	return new ItemContainer(*backpack);

}

//! Function to get all the items that are currently worn by the Character
//! @return copy of the currently worn items container
ItemContainer* Character::getCurrentWornItems() const{

	return new ItemContainer(*currentWornItems);

}

//! Function to increment the AC by a number
//! @param int - representing by how much to increment AC
void Character::incrementArmorClass(int chrAC){

	//! Check if number passed is valid (not -ve)
	if (chrAC >= 0)
		armorClass += chrAC; //! Increment if number is correct
	else
		cout << "\nIncorrect incremental\n"; //! Error message if invalid parameter
}

//! Remove certain buffs from the Character and affecting his stats
//! @param itemBuff a vector of all the buffs that should be removed from the Character
void Character::takeOffBuff(vector<Buff> itemBuff){
	for (auto i : itemBuff){
		switch (i.getBuffType()){
		case BuffType::ARMOR_CLASS:{
			armorClass -= i.getBuffAmount();
			break;
		}
		case BuffType::INTELLIGENCE:{
			abilityModifiers[(int)CharacterAbility::INTEL] -= i.getBuffAmount();
			break;
		}
		case BuffType::WISDOM:{
			abilityModifiers[(int)CharacterAbility::WISD] -= i.getBuffAmount();
			break;
		}
		case BuffType::STRENGTH:{
			abilityModifiers[(int)CharacterAbility::STR] -= i.getBuffAmount();
			break;
		}
		case BuffType::CONSTITUTION:{
			abilityModifiers[(int)CharacterAbility::CONS] -= i.getBuffAmount();
			break;
		}
		case BuffType::CHARISMA:{
			abilityModifiers[(int)CharacterAbility::CHA] -= i.getBuffAmount();
			break;
		}
		case BuffType::DEXTERITY:{
			abilityModifiers[(int)CharacterAbility::DEX] -= i.getBuffAmount();
			break;
		}
		}
	}
}

//! Remove an item from the backpack
//! @param objItem an item to be removed from the Character's backpack
//! @return true if the item is valid and has been successfully deleted, false otherwise
bool Character::removeItemBack(Item *objItem){


	if (!objItem->validateItem())
		return false;
	backpack->removeItem(objItem->getItemName());

	return true;

}

//! Save character inside a txt file
//! All the information about the character will be stored inside a
//! text file that will have the same name as the name of teh Character
void Character::saveCharacter(){


	ofstream outStream("SaveFiles/Characters/" + name + ".txt", ios::out);

	outStream << "character\n" << name << "\n" << to_string(level) << "\n" << to_string((int)size) << "\n0\n";

	for (int i = 0; i < NO_ABILITY; i++){
		outStream << to_string(abilityScores[i]) << "\n";
	}

	outStream << "backpack\n";
	for (auto i : backpack->getContents()){
		outStream << i->getItemName() << "\n";
	}

	outStream << "wornItem\n";
	for (auto i : currentWornItems->getContents()){
		outStream << i->getItemName() << "\n";
	}

	outStream.close();

}

//! Method that overloads the output stream operator in order to give a specific output for each character object
//! @return reference to passed output sream with a new output
ostream& operator<<(ostream& stream, const Character& chr){

	const int labelSpace = 9;
	const int abilitylabelSpace = 19;
	const int abilityScrSpace = 8;
	const int abilityModSpace = 5;

	stream << "-------------------------------------------------------------------------------------------------------\n";
	stream << setw(30) << right << chr.name << "'s STATS\n";
	stream << "-------------------------------------------------------------------------------------------------------\n";

	//! Specific output format for a Character object
	stream << "\nName: " << chr.name <<
		"\nLevel: " << chr.level <<
		"\nSize: " << chr.size;

	stream << "\n\nAbility \t" << "Score\t Modifier\n";

	stream << CharacterAbility::STR << "\t" << chr.abilityScores[(int)CharacterAbility::STR] << "\t" << chr.abilityModifiers[(int)CharacterAbility::STR] << "\n" <<
		CharacterAbility::DEX << "\t" << chr.abilityScores[(int)CharacterAbility::DEX] << "\t" << chr.abilityModifiers[(int)CharacterAbility::DEX] << "\n" <<
		CharacterAbility::CONS << "\t" << chr.abilityScores[(int)CharacterAbility::CONS] << "\t" << chr.abilityModifiers[(int)CharacterAbility::CONS] << "\n" <<
		CharacterAbility::INTEL << "\t" << chr.abilityScores[(int)CharacterAbility::INTEL] << "\t" << chr.abilityModifiers[(int)CharacterAbility::INTEL] << "\n" <<
		CharacterAbility::WISD << "\t\t" << chr.abilityScores[(int)CharacterAbility::WISD] << "\t" << chr.abilityModifiers[(int)CharacterAbility::WISD] << "\n" <<
		CharacterAbility::CHA << "\t" << chr.abilityScores[(int)CharacterAbility::CHA] << "\t" << chr.abilityModifiers[(int)CharacterAbility::CHA] << "\n";

	stream << "\n\nCurrent Hit Points(HP): " << chr.currentHitPoints << "/" << chr.maxHP <<
		"\nDamage Bonus: " << chr.calcDamageBonus() <<
		"\nAttack Bonus: " << chr.calcAttackBonus() <<
		"\nArmor Class: " << chr.armorClass <<
		"\nBackpack holding: \n\n" << *(chr.backpack);
	stream << "\n\nWearing Items: \n\n" << *(chr.currentWornItems);

	stream << "-------------------------------------------------------------------------------------------------------\n";

	return stream;
}

//!Return the provider string "Character"
string Character::provider()
{
	return "Character";
}

