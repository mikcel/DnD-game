//!
//! @file 
//! @brief Header file of the Character class.
//!

//! 
//! The Character Class is the main class of this project. This file declares the constructors, data members, 
//! constants, getter and setters, service methods and overridden functions that are all used to create and maintain a Character
//! object. It includes the string and iostream libraries for string variables and output use respectively. The enumerated file 
//! is also included to get access to the enumerated types for the classes data members and methods. The Character class also 
//! contains a method that overrides the output stream operator to give a specific output for each Character object 
//! instead of having a reference outputted to the console. The Character class makes use of the Item container Stub to simulate
//! the backpack and the currently worn items containers. 
//! The character class inherits fromt he subject class for the observer.
//!

#pragma once 

#include <string> //! Library for string for parameters of this type
#include <iostream> //! Iostream for output use
using namespace std; 

#include "Enums.h" //! Include header file for the enumerated type
#include "Dice.h"
#include "ItemContainer.h" //! Include the itemcontainer class
#include "Observable.h" //! Include the subject class for the observer pattern
#include "Element.h"
#include "Loggable.h"

//! Class that implements the Character
class Character : public Loggable {
public:
	
	//! Constant for the No. of abilities (scores & modifiers) (mainly use for array size)
	static const int  NO_ABILITY = 6; 

	//! Default Constructor
	Character(); 

	//! Constructor with name
	//! Used to facilitate map construction from a map file
	Character(string chrName);

	//! Constructor with name, an array of ability scores, the Character's level and size
	//! If level and size are not passed , the level is set to 1 by default and size to tiny by default
	Character(string chrName,int chrAbilityScores[NO_ABILITY], int chrLevel = 1, CharacterSize chrSize = CharacterSize::TINY);

	//! Constructor with name, six variables for each ability score, level and size 
	//! If level and size are not passed , the level is set to 1 by default and size to tiny by default
	Character(string chrName, int str, int dex, int cons, int intel, int wisd, int cha, int chrLevel = 1, CharacterSize chrSize = CharacterSize::TINY);
	
	Character(const Character &copyChar);
	
	//! Destrcutor
	virtual ~Character(); 

	string getName() const; //! Getter for Character's name
	int getLevel() const; //! Getter for Character's Level
	CharacterSize getSize() const; //! Getter for Character's Size
	int getOneAbilityScore(CharacterAbility ability) const; //! Getting one ability score
	int* getAllAbilityScores() const; //! Getter for an array of all the ability scores
	int getOneAbilityModifier(CharacterAbility ability) const; //! Getter one ability modifier
	int* getAllAbilityModifiers() const; //! Function to return a pointer to a copy of the ability modifiers array.
	int getCurrentHitPoints() const; //! Getter to get Character's HP
	int getMaxHP() const; //! Accessor for the max hit points
	int getArmorClass() const; //! Function that return Armor Class

	void setName(string chrName); //! Setter for the Character's name
	void setLevel(int chrLevel); //! Setter for the Character's level
	void setSize(CharacterSize chrSize); //! Function to set the Character's size
	void setAbilityScores(int str, int dex, int cons, int intel, int wisd, int cha); //! Function to set each ability scores
	void setAbilityScores(int chrAbilityScores[NO_ABILITY]); //! Function to set ability scores from a passed array
	void setCurrentHitPoints(int chrHitPt); //! Setter for the Character's HP

	int calcAttackBonus() const; //! Function to calculate the Attack Bonus
	void calcArmorClass(); //! Method to calculate a Character's Armor Class
	int calcDamageBonus() const; //! Function to calculate the Damage Bonus
	void generateAbilityModifiers(); //! Function to set the Ability modifiers for each ability score
	bool validateNewCharacter(); //! Method to validate a newly created Character
	int hit(int dmg); //! Function that is called when a Character gets hit. Decreases the Character's HP with a damage number
	virtual bool attack(Character &chr); //! Function that is used when a Character attacks another Character
	int getSizeModifier() const; //! Function to calculate the Size Modifier
	void incrementLevel(); //! Function to increase the Character's 
	void incrementArmorClass(int chrAC); //! Method to increment the Character's AC by a number

	bool takeOffItem(Item *objItem); //! Unequip item
	bool wearItem(Item *objItem); //! Wear an item (goes into currently Worn items)
	bool storeItem(Item *objItem); //! Add item into the backpack
	bool removeItemBack(Item *objItem); //! Remove item from the backpack
	ItemContainer* getBackpackContents() const; //! Get all items that are currently in the Character's backpack
	ItemContainer* getCurrentWornItems() const; //! Get all the items that the Character is currently wearing
	int getWeaponRange(); //! Melee or Range weapon being worn

	virtual void saveCharacter(); // Save teh character to a txt file

	virtual std::string provider(); //! Returns the Loggable provider.
	virtual Character* clone() = 0; // Copies the current CharacterElement

private:

	//! Default Constant value for the HP 
	const int DEFAULT_HP = 10;

	string name = "Unknown"; //! Name data member. Default is "Unknown"
	int level = 1; //! Level data member. Default is 1
	CharacterSize size = CharacterSize::TINY; //! Character's Size set to Tiny by default
	int abilityScores[NO_ABILITY]; //! Array for the ability scores with 6 elements 
	int abilityModifiers[NO_ABILITY]; //! Array for the ability modifiers containg 6 numbers
	int currentHitPoints = DEFAULT_HP; //! Character's Hp set to default HP (10)
	int maxHP = DEFAULT_HP; //! Max hp for the character
	int armorClass=0; //! Character's AC. 0 by default
	ItemContainer *backpack; //! Character's backpack
	ItemContainer *currentWornItems; //! Character's currently worn items container

	void takeOffBuff(vector<Buff> itemBuff); //! Method to check stats and buffs

	//! Method used to overload the output stream operator to output the Character's details to the console.
	friend ostream& operator<<(ostream& stream, const Character& chr); 

};

