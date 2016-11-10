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
//! Sets all abilities to 3, name to "Unknown", hit dice to "1d10", level to 1 and size to Tiny.
//! It invokes one of the parametrized constructor (see below) to initailize each data member
Character::Character() : Character("Unknown", "1d10", 3, 3, 3, 3, 3, 3, 1, CharacterSize::TINY){

	/*Intentionally left empty*/

}

//! Constructor: gets the name, the hit dice, an array of ability scores, the level and the size.
//! It invokes the other parametrized constructor to set each variable.
//! Note: to initialize each ability score, each of them is taken from the passed array using the enum type to index the array.
Character::Character(string chrName, string hitDice, int chrAbilityScores[NO_ABILITY], int chrLevel, CharacterSize chrSize) :
Character(chrName, hitDice, chrAbilityScores[(int)CharacterAbility::STR], chrAbilityScores[(int)CharacterAbility::DEX], chrAbilityScores[(int)CharacterAbility::CONS], chrAbilityScores[(int)CharacterAbility::INTEL],
chrAbilityScores[(int)CharacterAbility::WISD], chrAbilityScores[(int)CharacterAbility::CHA], chrLevel, chrSize){
	/*Intentionally left empty*/
}

Character::Character(Character &copyChar) {
	this->name = copyChar.name;
	this->level = copyChar.level;
	this->size = copyChar.size;
	this->hitDice = copyChar.hitDice;

	for (int i = 0; i < NO_ABILITY; i++){
		abilityScores[i] = copyChar.abilityScores[i];
	}

	//! Call the method to generate the each ability modifiers
	generateAbilityModifiers();

	//! Invokes the method to calculate the armor class
	calcArmorClass();

	//! Initialise the two items container
	backpack = new ItemContainer(*copyChar.backpack);
	currentWornItems = new ItemContainer(*copyChar.currentWornItems);

	//! Calculate the attack and damage bonuses
	calcDamageBonus();
	calcAttackBonus();
}
//! Constructor: passes values to the name, the hit dice, the size, the level and each ability score
Character::Character(string chrName, string hitDice, int str, int dex, int cons, int intel, int wisd, int cha, int chrLevel, CharacterSize chrSize){

	//! Sets name, size, level and hit dice
	name = chrName;
	level = chrLevel;
	size = chrSize;
	this->hitDice = hitDice;

	//! Call the setter method for the ability scores
	setAbilityScores(str, dex, cons, intel, wisd, cha);

	//! Call the method to generate the each ability modifiers
	generateAbilityModifiers();

	//! Invokes the method to calculate the armor class
	calcArmorClass();

	//! Initialise the two items container
	backpack = new ItemContainer(ContainerType::BACKPACK);
	currentWornItems = new ItemContainer(ContainerType::WORN_ITEM);

	//! Calculate the attack and damage bonuses
	calcDamageBonus();
	calcAttackBonus();
}

//! Default Destructor
Character::~Character(){
	delete backpack;
	delete currentWornItems;
}

//! Accessor for the Character's name. 
//! @return name
string Character::getName(){
	return name;
}

//! Accessor for the Character's level.
//! @return level
int Character::getLevel(){
	return level;
}

//! Accessor for the Character's Size.
//! @return size
CharacterSize Character::getSize(){
	return size;
}

//! Accessor for one ability score
//! @param ability - Of type abilities from enumerated type
//! @return integer, the ability score passed as parameter
int Character::getOneAbilityScore(CharacterAbility ability){
	
	//! Get ability by using the array index (enum type) passed as parameter 
	return abilityScores[(int)ability]; 
	
}

//! Accessor for all ability scores
//! @return a pointer to a copy array containing all the ability scores
int* Character::getAllAbilityScores(){

	int *arrayPointer; //! Pointer for new array
	int arrayCopy[NO_ABILITY]; //! New array to be returned
	
	arrayPointer = arrayCopy; //! Make pointer reference the newly created array

	//! For loop to copy each element of array abilities to newly created array
	for (int i = 0; i < sizeof(abilityScores); i++){
		arrayCopy[i] = abilityScores[i];
	}

	//! return the pointer to the new array
	return arrayPointer;
}

//! Accessor for one ablity modifier.
//! @param ability - of type CharacterAbility (enumerated) to index array of ability modifiers
//! @return the ability modifer asked for (parameter)
int Character::getOneAbilityModifier(CharacterAbility ability){
	
	//! Return the ability modifier by indexing the array to the ability passed (enum type)
	return abilityModifiers[(int)ability];
	
}

//! Accessor method for all ability modifiers
//! @return a pointer to a copy array of the ability mofidiers
int* Character::getAllAbilityModifiers(){

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
int Character::getCurrentHitPoints(){
	return currentHitPoints;
}

//! Accessor method for the Damage Bonus
//! @return Character's Damage bonus
int Character::getDamageBonus(){
	return damageBonus;
}

//! Getter for attack Bonus
//! @return Attack Bonus
int Character::getAttackBonus(){
	return attackBonus;
}

//! Getter for Armor Class
//! @return Armor Class
int Character::getArmorClass(){
	return armorClass;
}

//! Accessor method for Character's hit dice
//! @return the character's hit dice
string Character::getHitDice(){
	return hitDice;
}

//! Setter for the Character's name
//! @param string - Character's new name
void Character::setName(string chrName){

	if (name!="") //! Check if new name is not empty
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
	}
	else{ //! Incorrect message is output if negative new level
		cout << "Incorrect Level.";
	}
}

//! Mutator for the Character's size
//! @param Size enumerated size as new Character's size
void Character::setSize(CharacterSize chrSize){
	size = chrSize;
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
}

//! Mutator for the all ability scores
//! @param array - interger array to copy from elements for each score
void Character::setAbilityScores(int chrAbilityScores[NO_ABILITY]){
	
	//! Copy each element from passed array to ability score array
	for (int i = 0; i < NO_ABILITY; i++){
		abilityScores[i] = chrAbilityScores[i];
	}

}

//! Setter for Character's HP
//! @param int Caracter's new hit point
void Character::setCurrentHitPoints(int chrHitPt){
	currentHitPoints = chrHitPt;
}

//! Mutator for the Cahracter's hit dice
//! @param string New hit dice
void Character::setHitDice(string hitDice){
	this->hitDice = hitDice;
}

//! Service method to calculate Armor Class
//! @param -
void Character::calcArmorClass(){
	//! Formula for Armor Class: 10 + size mofifier + dexterity modifier
	armorClass = 10 + getSizeModifier() + abilityModifiers[(int)CharacterAbility::DEX];
}

//! Service Method to calculate characters' damage bonus
//! @param - 
void Character::calcDamageBonus(){

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
		damageBonus = bonus;
	else
		damageBonus = 0;
}

//! Service Method to calculate Character's Attack Bonus
//! NOTE: THERE WILL BE A BETTER IMPLEMENTATION ONCE PROJECT WILL BE MERGED (with the weapons)
//! @param string - Weapon type that the Character's holds 
void Character::calcAttackBonus(){

	//! Check if size mod is greater than level so as not to get -ve attack bonus
	if (getSizeModifier() > level)
		attackBonus = level + getSizeModifier();
	else
		attackBonus = level;

	if (currentWornItems->getContents()[(int)ItemType::WEAPON]->getItemTypes() != ItemType::UNSPECIFIED){
		
		Weapon* weapon = (Weapon*)(currentWornItems->getItem(currentWornItems->getContents()[(int)ItemType::WEAPON]->getItemName()));
		if (weapon != NULL){

			if (weapon->getRange()==1) 
				attackBonus += abilityModifiers[(int)CharacterAbility::STR];
			else 
				attackBonus += abilityModifiers[(int)CharacterAbility::DEX];

			vector<Buff> buff = weapon->getBuffs();
			for (auto i : buff){
				if (i.getBuffType() == BuffType::ATTACK_BONUS)
					attackBonus += i.getBuffAmount();
			}

		}

	}


	//! In case attack Bonus is -ve
	if (attackBonus < 0)
		attackBonus = 0;

}

//! Method to calculate the ability modifier for each ability score
//! @param none
void Character::generateAbilityModifiers(){

	//! Check size of ability scores array ( If all scores were entered before calculating the respective modifiers)
	if (sizeof(abilityScores)/4 == 0)
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
//! @return 0 - if character died (HP=0), 1 - Character was hit (Not protected by armor class) & 2 - Character was not hit
int Character::hit(int dmg){

	int returnVal = 0;
	int newDmg = dmg - armorClass; //! Subtract armor class because Character is protected by Armor (max. 22)
	if (newDmg >= currentHitPoints){  //! If new Damage is more than current HP, character dies.
		notify();
		cout << "\n" << name << " hit by " << dmg << " damage. \nNot enough to be protected by armor and above HP. Game Over for " << getName() << "\n";
		currentHitPoints = 0;
		returnVal = 0;
	}
	else if (newDmg > 0){ //! If new damage is less than current HP
		currentHitPoints -= newDmg; //! Subtract damage from HP
		notify();
		cout << "\n" << name << " hit by " << dmg << " damage.\n"
			<< "Protected by AC; Total Damage: " << newDmg << "\n"
			<< name << "'s Current Hit Points (HP): " << currentHitPoints << endl;
		returnVal = 1;
	}
	else{ //! If protected by armor class, no damage
		cout << "\nArmor Protected " << name << " from " << dmg << " damage. Attack Missed.\n" << name << "'s Current Hit Points (HP): " << currentHitPoints << endl;
		returnVal = 2;
	}
	
	return returnVal;

}

//! Function to attack another Character
//! @param Character and int - Representing the Character wanted to attack and the damage to be caused.
//! @return 0 - if character died (HP=0), 1 - Character was hit (Not protected by armor class) & 2 - Character was not hit 
int Character::attack(Character &chr, int dmg){
	
	//! Check if character reference is not the calling object itself
	if (&chr == this){
		cout << "\nYou cannot attack yourself." << endl;
		return 2; //! Return not hit
	}


	cout << "\nWith Attack Bonus and Damage Bonus, total damage is " << dmg + attackBonus + damageBonus << endl;

	//! Return value got from the hit function of the passed Character
	return chr.hit(dmg + attackBonus + damageBonus);
}

//! Function that determine size modifier for a character object
//! @return the size modifier of the character depending on his size
int Character::getSizeModifier(){
	
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
//! @param int - representing the roll of the Character's hit dice
void Character::incrementLevel(int hitDiceNo){
	level++; //! Increment level by 1

	//! Calculate new hit points
	//! Take constitution modifier and add with the hit dice roll
	currentHitPoints += abilityModifiers[(int)CharacterAbility::CONS] + hitDiceNo;

	calcAttackBonus();

	//! Output new information
	cout << "Level" << level << "reached.\n"
		<<"Current HP: " << currentHitPoints;
}

bool Character::takeOffItem(Item *objItem){

	if (currentWornItems->unequipItem(objItem->getItemName(), backpack)){
		if (objItem->getItemTypes() == ItemType::WEAPON){
			calcAttackBonus();
			calcDamageBonus();
		}
		else{
			takeOffBuff(objItem->getBuffs());
		}
		notify();
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
		if (objItem->getItemTypes() == ItemType::WEAPON){
			calcAttackBonus();
			calcDamageBonus();
		}
		else
		{
			vector<Buff> itemBuff= objItem->getBuffs();
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
		}
		notify();
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

	notify();
	return true;
}

vector<Item*> Character::getBackpackContents(){

	return backpack->getContents();

}

vector<Item*> Character::getCurrentWornItems(){

	return currentWornItems->getContents();

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

bool Character::removeItemBack(Item *objItem){

	if (!objItem->validateItem())
		return false;
	backpack->removeItem(objItem->getItemName());

	notify();
	return true;

}

void Character::saveCharacter(){
	

	ofstream outStream("SaveFiles/Characters/" + name + ".dat", ios::out | ios::binary);
	
	outStream << "character\n" << name << "\n" << hitDice << "\n" << to_string(level) << "\n" << to_string((int)size) << "\n0\n";

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
	stream << setw(60) << right << chr.name << "'s STATS\n";
	stream << "-------------------------------------------------------------------------------------------------------\n";

	//! Specific output format for a Character object
	stream << "\nName: " << chr.name <<
		"\nLevel: " << chr.level <<
		"\t\tSize: " << chr.size;
		
	stream << "\n\nAbility \t" << "Score\t Modifier\n";

	stream << CharacterAbility::STR << "\t" << chr.abilityScores[(int)CharacterAbility::STR] << "\t" << chr.abilityModifiers[(int)CharacterAbility::STR] << "\n" <<
		CharacterAbility::DEX << "\t" << chr.abilityScores[(int)CharacterAbility::DEX] << "\t" << chr.abilityModifiers[(int)CharacterAbility::DEX] << "\n" <<
		CharacterAbility::CONS << "\t" << chr.abilityScores[(int)CharacterAbility::CONS] << "\t" << chr.abilityModifiers[(int)CharacterAbility::CONS] << "\n" <<
		CharacterAbility::INTEL << "\t" << chr.abilityScores[(int)CharacterAbility::INTEL] << "\t" << chr.abilityModifiers[(int)CharacterAbility::INTEL] << "\n" <<
		CharacterAbility::WISD << "\t\t" << chr.abilityScores[(int)CharacterAbility::WISD] << "\t" << chr.abilityModifiers[(int)CharacterAbility::WISD] << "\n" <<
		CharacterAbility::CHA << "\t" << chr.abilityScores[(int)CharacterAbility::CHA] << "\t" << chr.abilityModifiers[(int)CharacterAbility::CHA] << "\n";

	stream << "\n\nCurrent Hit Points(HP): " << chr.currentHitPoints <<
		"\nDamage Bonus: " << chr.damageBonus <<
		"\nAttack Bonus: " << chr.attackBonus <<
		"\nArmor Class: " << chr.armorClass <<
		"\nHit Dice: " << chr.hitDice << "\n" <<
		"\nBackpack holding: \n\n" << *(chr.backpack) <<
		"\n\nWearing Items: \n\n" << *(chr.currentWornItems);

	stream << "-------------------------------------------------------------------------------------------------------\n";

	return stream;
}

//! Method to create a new item  and add to backpack
//! @param Character to add item to its backpack
//void Character::createItem(){
//string name = ""; //! Item name
//int itemType = item::itemTypes::UNSPECIFIED; //! item type
//int choiceItem = 0; //! Item or weapon
//int range = 0; //! Range of weapon
//vector<Buff> vecBuff(0); //! Vector for buff
//
//						 //! Ask for weapon or item
//cout << "\nDo you want to create an Item - 0 or a Weapon - 1? ";
//cin >> choiceItem;
////! check choice
//while (choiceItem<0 || choiceItem>1) { //!  ask to continue enter if incorrect
//	cout << "\nIncorrect choice. Please choose only 0 or 1: ";
//	cin >> choiceItem;
//}
//
//if (choiceItem == 0) { //! If item or weapon
//
//	cout << "\nLet's create a new Item!!!";
//
//	cout << "\nEnter the Item Name: ";
//	cin.ignore();
//	getline(cin, name); //! Get name
//
//						//! output all posisible type and ask to choose
//	cout << "Enter the Item type no. from the list provided below:\n";
//	cout << (int)item::itemTypes::HELMET << " - " << item::itemTypes::HELMET << "\n"
//		<< (int)item::itemTypes::ARMOR << " - " << item::itemTypes::ARMOR << "\n"
//		<< (int)item::itemTypes::SHIELD << " - " << item::itemTypes::SHIELD << "\n"
//		<< (int)item::itemTypes::RING << " - " << item::itemTypes::RING << "\n"
//		<< (int)item::itemTypes::BELT << " - " << item::itemTypes::BELT << "\n"
//		<< (int)item::itemTypes::BOOTS << " - " << item::itemTypes::BOOTS << "\n"
//		<< (int)item::itemTypes::WEAPON << " - " << item::itemTypes::WEAPON << "\n";
//	cout << "Enter choice: ";
//	cin >> itemType;
//	//! Continue to ask if choice is incorrectly entered
//	while (itemType<0 || itemType>6) {
//		cout << "\nIncorrect choice. Please enter again: ";
//		cin >> itemType;
//	}
//
//	int choiceBuff = 0; //! Buff choice
//	while (choiceBuff != -1) { //! While player wants to continue add buff
//		cout << "\nChoose the buffs for this item from the list below: \n";
//		//! Display all possible buffs
//		cout << (int)buff::buffTypes::INTELLIGENCE << " - " << buff::buffTypes::INTELLIGENCE << "\n"
//			<< (int)buff::buffTypes::WISDOM << " - " << buff::buffTypes::WISDOM << "\n"
//			<< (int)buff::buffTypes::ARMOR_CLASS << " - " << buff::buffTypes::ARMOR_CLASS << "\n"
//			<< (int)buff::buffTypes::STRENGTH << " - " << buff::buffTypes::STRENGTH << "\n"
//			<< (int)buff::buffTypes::CHARISMA << " - " << buff::buffTypes::CHARISMA << "\n"
//			<< (int)buff::buffTypes::CONSTITUTION << " - " << buff::buffTypes::CONSTITUTION << "\n"
//			<< (int)buff::buffTypes::DEXTERITY << " - " << buff::buffTypes::DEXTERITY << "\n"
//			<< (int)buff::buffTypes::ATTACK_BONUS << " - " << buff::buffTypes::ATTACK_BONUS << "\n"
//			<< (int)buff::buffTypes::DAMAGE_BONUS << " - " << buff::buffTypes::DAMAGE_BONUS << "\n"
//			<< "-1 to stop\n";
//		cout << "Enter choice: ";
//		cin >> choiceBuff; //! Enter buff choice
//
//						   //! Check for buff choice. Ask again if incorrectly entered
//		while (choiceBuff != -1 && (choiceBuff<0 || choiceBuff>8)) {
//			cout << "\nIncorrect Input. Please enter a correct number: ";
//			cin >> choiceBuff;
//		}
//
//		//! If do not want to exxit
//		if (choiceBuff != -1) {
//			int amount = 0;
//			//! Ask for buff amount
//			cout << "Enter buff's amount: ";
//			cin.ignore();
//			cin >> amount;
//			//! Put in vector for buff
//			vecBuff.push_back(Buff((buff::buffTypes)choiceBuff, amount));
//		}
//
//	}
//}
//else {
//	//! Create a weapon
//	cout << "\nLet's create a new Weapon!!!";
//	cout << "\nEnter the Weapon Name: ";
//	cin.ignore();
//	getline(cin, name); //! Get weapon name
//
//	cout << "\nPlease enter the weapon's range: ";
//	cin >> range; //! Get weapon range
//
//	int choiceBuff = 0;
//	while (choiceBuff != -1) { //! Ask for buff choice
//		cout << "\nChoose the buffs for this weapon from the list below: \n";
//		cout << (int)buff::buffTypes::INTELLIGENCE << " - " << buff::buffTypes::INTELLIGENCE << "\n"
//			<< (int)buff::buffTypes::WISDOM << " - " << buff::buffTypes::WISDOM << "\n"
//			<< (int)buff::buffTypes::ARMOR_CLASS << " - " << buff::buffTypes::ARMOR_CLASS << "\n"
//			<< (int)buff::buffTypes::STRENGTH << " - " << buff::buffTypes::STRENGTH << "\n"
//			<< (int)buff::buffTypes::CHARISMA << " - " << buff::buffTypes::CHARISMA << "\n"
//			<< (int)buff::buffTypes::CONSTITUTION << " - " << buff::buffTypes::CONSTITUTION << "\n"
//			<< (int)buff::buffTypes::DEXTERITY << " - " << buff::buffTypes::DEXTERITY << "\n"
//			<< (int)buff::buffTypes::ATTACK_BONUS << " - " << buff::buffTypes::ATTACK_BONUS << "\n"
//			<< (int)buff::buffTypes::DAMAGE_BONUS << " - " << buff::buffTypes::DAMAGE_BONUS << "\n"
//			<< "-1 to stop\n";
//		cout << "Enter choice: ";
//		cin >> choiceBuff;
//
//		//! Check for buff choice. Ask again if incorrectly entered
//		while (choiceBuff != -1 && (choiceBuff<0 || choiceBuff>8)) {
//			cout << "\nIncorrect Input. Please enter a correct number: ";
//			cin >> choiceBuff;
//		}
//
//		//! If do not want to exxit
//		if (choiceBuff != -1) {
//			int amount = 0;
//			//! Ask for buff amount
//			cout << "Enter buff's amount: ";
//			cin.ignore();
//			cin >> amount;
//			//! Put in vector for buff
//			vecBuff.push_back(Buff((buff::buffTypes)choiceBuff, amount));
//		}
//
//	}
//}
//
//Item newItem; //! Item variable
//Weapon newWeapon; //! Weapon variable
//if (choiceItem == 0) { //! If item or weapon
//					   //! Create and validate item
//	newItem = Item((item::itemTypes)itemType, name, vecBuff);
//	if (newItem.validateItem()) {
//		cout << "\nHere is the item that you want to add: \n";
//		cout << newItem;
//	}
//	else {
//		//! If not correct item. return back.
//		cout << "\nIncorrect Item. Item Refused.";
//		return;
//	}
//}
//else {
//	//! Create and validae weapon
//	newWeapon = Weapon(item::itemTypes::WEAPON, name, vecBuff, range);
//	if (newWeapon.validateWeapon()) {
//		cout << "\nHere is the weapon that you want to add: \n";
//		cout << newWeapon;
//	}
//	else {
//		//! If invalid weapon. do not add to backpack and return
//		cout << "\nIncorrect Weapon. Weapon Refused.";
//		return;
//	}
//}
//
////! Ask for user confirmation to add in bakcpack
//string contAns = "";
//cout << "\nDo you want to add the item to the backpack? (Y/N)\nEntering N will discard all unsaved data.";
//cin >> contAns;
//
////! Check input
//while (contAns != "Y" && contAns != "N") {
//	cout << "\nPlease enter Y or N: ";
//	cin >> contAns;
//}
//
////! If wan to continue, then store in backpack
//if (contAns == "Y") {
//	if (choiceItem == 0) {
//		storeItem(&newItem);
//		newItem.saveItem();
//	}
//	else {
//		storeItem(&newWeapon);
//		newItem.saveItem();
//	}
//}
//
//}

//void Character::editItem() {
//	int userChoice =-1;
//	while (true) {
//		cout << "Enter the index of the item you wish to edit.\nNote:The item must be in your character's backpack.\nEnter -1 to quit." << endl;
//		int itemIndex = 0;
//		for (auto i : backpack->getContents()) {
//			cout << itemIndex << ": " << i->getItemName()<<endl;
//			itemIndex++;
//		}
//		string userChoiceStr;
//		cin >> userChoiceStr;
//		try {
//			userChoice = stoi(userChoiceStr);
//			if (userChoice == -1) {
//				return;
//			}
//			Item* item = backpack->getContents()[userChoice];
//			cout << "Selected: " <<item->getItemName()<<endl;
//			cout << "What do you want to modify?" << endl;
//			cout << "0: Item Name\n1: Buff\nEnter -1 to quit." << endl;
//			cin >> userChoiceStr;
//			userChoice = stoi(userChoiceStr);
//			if (userChoice == 0) {
//				cout << "Enter the new name of the item." << endl;
//				string  newItemName;
//				cin.ignore();
//				getline(cin, newItemName);
//				item->setItemName(newItemName);
//			}
//			else if(userChoice==1) {
//				//buffs
//				for (auto bu : item->getBuffs()) {
//					cout << "buff type "<<bu.getBuffType() << endl;
//					cout << "buff amount "<<bu.getBuffAmount() << endl;
//				}
//				int choiceBuff = 0;
//				int choiceAmount = 0;
//				while (true) { //! Ask for buff choice
//					cout << "\nChoose the buffs for this item from the list below:\nEnter -1 to stop picking buffs.\n";
//					cout << (int)buff::buffTypes::INTELLIGENCE << " - " << buff::buffTypes::INTELLIGENCE << "\n"
//						<< (int)buff::buffTypes::WISDOM << " - " << buff::buffTypes::WISDOM << "\n"
//						<< (int)buff::buffTypes::ARMOR_CLASS << " - " << buff::buffTypes::ARMOR_CLASS << "\n"
//						<< (int)buff::buffTypes::STRENGTH << " - " << buff::buffTypes::STRENGTH << "\n"
//						<< (int)buff::buffTypes::CHARISMA << " - " << buff::buffTypes::CHARISMA << "\n"
//						<< (int)buff::buffTypes::CONSTITUTION << " - " << buff::buffTypes::CONSTITUTION << "\n"
//						<< (int)buff::buffTypes::DEXTERITY << " - " << buff::buffTypes::DEXTERITY << "\n"
//						<< (int)buff::buffTypes::ATTACK_BONUS << " - " << buff::buffTypes::ATTACK_BONUS << "\n"
//						<< (int)buff::buffTypes::DAMAGE_BONUS << " - " << buff::buffTypes::DAMAGE_BONUS << "\n"
//						<< "-1 to stop\n"<<endl;
//					cout << "Enter choice: " << endl;
//					cin >> choiceBuff;
//					if (choiceBuff == -1) {
//						break;
//					}
//					cout << "Enter amount: " << endl;
//					cin >> choiceAmount;
//					
//					if (choiceAmount == -1) {
//						break;
//					}
//					vector<Buff> buffs = item->getBuffs();
//					bool buffExist=false;
//					int buffIterator = 0;
//					for (auto b : buffs) {
//						if (b.getBuffType() == (buff::buffTypes)choiceBuff) {
//							buffExist = true;
//							cout << "FOUND BUFF" << endl;
//							//b.setBuffAmount(choiceAmount);
//							buffs[buffIterator].setBuffAmount(choiceAmount);
//							break;
//						}
//						buffIterator++;
//					}
//					if (!buffExist) {
//						buffs.push_back(Buff((buff::buffTypes)choiceBuff, choiceAmount));
//					}
//					cout << "SET BUFFS" << endl;
//					item->setBuffs(buffs);
//				}
//				vector<Item*> tmpBackpack = backpack->getContents();
//				tmpBackpack[userChoice] = new Item(item);
//				backpack->setContents(tmpBackpack);
//				//back pack is updated
//
//				for (auto bu : item->getBuffs()) {
//					cout << "buff type" << bu.getBuffType() << endl;
//					cout << "buff amount" << bu.getBuffAmount() << endl;
//				}
//
//			}
//			else if (userChoice == -1) {
//				return;
//			}
//			else {
//				cout << "Invalid input.\nExiting" << endl;
//				return;
//			}
//
//			cout << "Edit another Item?\nEnter 0 to continue, -1 to quit." << endl;
//			cin >> userChoiceStr;
//			userChoice = stoi(userChoiceStr);
//			if (userChoice == 0) {
//				continue;
//			}
//			else if(userChoice==-1){
//				return;
//			}
//		}//end of try
//		catch (...) {
//			cout << "Invalid input.\nExiting" << endl;
//			return;
//		}
//		
//		
//	}
//
//}
