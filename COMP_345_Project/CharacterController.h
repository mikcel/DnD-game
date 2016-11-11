//! 
//! @file
//! @brief Header file for Character Controller
//!

//!
//! This file defines the Character Controller for the game. It mainly allows the creation and the edition of a character.
//! It also enables reading a character from a file that is used in many places in the code
//!

#pragma once
#include "Character.h"
#include "Fighter.h"
#include "FolderUtils.h"
#include "ItemUtils.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <time.h>
using namespace std;

class CharacterController
{
public:
	CharacterController(); //! Default Constructor

	CharacterController(Character *currentChar); //! Parametrized Constructor - pointer to a character
	
	~CharacterController(); //! Destructor

	Character* getCurrentCharacter(); //! Getter method for character

	void setCurrentCharacter(Character *character); //! Setter method for Character

	void createCharacter(); //! Method to create a Character

	void editCharacter(); //! Method to edit a Character

	void saveCharacter(); //! Method to save a Character
	
private:

	Character *currentCharacter = NULL; //! Pointer to a character object

	void displayCharacterSize(); //! Method to display all available character sizes

	void displayFighterStyle(); //! Method to display all available fighter style

	bool checkScr(int *arr, int scr); //! Method to check score when entering

	void addItem(); //! Method to add an item to a Character

};

Character* readCharacterFile(string charName, string charFileLocation); //! Method to read a character from a file
