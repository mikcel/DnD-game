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
	CharacterController();

	CharacterController(Character *currentChar);
	
	~CharacterController();

	Character* getCurrentCharacter();

	void setCurrentCharacter(Character *character);

	void createCharacter();

	void editCharacter();

	void saveCharacter();
	
private:

	Character *currentCharacter = NULL;

	void displayCharacterSize();

	void displayFighterStyle();

	bool checkScr(int *arr, int scr);

	void addItem();

};

Character* readCharacterFile(string charName, string charFileLocation);
