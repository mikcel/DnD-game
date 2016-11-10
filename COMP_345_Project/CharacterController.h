#pragma once
#include "Character.h"
#include "Fighter.h"
#include <iostream>
#include <time.h>
using namespace std;

class CharacterController
{
public:
	CharacterController();

	CharacterController(Character *currentChar);
	
	~CharacterController();

	Character* getCurrentCharacter();

	void setCurrentCharacter(Character *character);

	void createCharacter();

	void editCharacter();

	void saveCharacter();

	Character* readCharacterFile(string charName, string charFileLocation);

private:

	Character *currentCharacter;

	void displayCharacterSize();

	void displayFighterStyle();

	bool checkScr(int *arr, int scr);

};
