
#include "CharacterController.h"


CharacterController::CharacterController()
{
	
}

CharacterController::CharacterController(Character *currentCharacter){

	this->currentCharacter = currentCharacter;

}

CharacterController::~CharacterController()
{
	delete currentCharacter;
}

Character* CharacterController::getCurrentCharacter(){
	return currentCharacter;
}

void CharacterController::setCurrentCharacter(Character *character){
	currentCharacter = new Character(*character);
}

void CharacterController::createCharacter(){

	system("cls");

	bool choiceCorrect = false; //Flag for correct choice between character and fighter creation 
	int choice = 0; //! Choice of user

	char choiceLoad;
	cout << "\nDo you want to load a Character from a saved file? (Y/N) -> ";

	bool loadFile = false; //! Flag to check if continue input is correct
	while (!loadFile){
		cin >> choiceLoad;
		if (choiceLoad == 'N' || choiceLoad == 'Y'){
			loadFile = true;
		}
		else
		{
			cout << "Please enter Y or N: ";
		}

	}

	if (choiceLoad == 'Y'){

		/*string fileName;
		cout << "Please enter the Character Name for the file: ";
		cin >> fileName;

		ifstream readFile("../SaveFiles/Character/" + fileName + ".txt", ios::binary);
		if (!readFile)
		{
			cerr << "Cannot open file for reading.\n";
			cout << "Exiting program...\n";
			system("pause");
			exit(1);
		}

		chr1 = new Character();
		readFile.read((char*)chr1, sizeof (Character));

		cout << *chr1;
		system("pause");
		exit(1);*/

	}
	else{
		cout << "\nPlease choose between creating a simple Character(1) or a Fighter(2) \nEnter the respective number: ";

		//! Keep asking if choice is not correct
		while (!choiceCorrect){

			cin >> choice;
			if (choice == 1){ //! If choice is Character
				cout << "\nTime to create a new Character!" << "\nLet's gets started.";
				choiceCorrect = true;
			}
			else if (choice == 2){ //! If choice is Fighter
				cout << "\nTime to create a new Fighter!" << "\nLet's gets started.";
				choiceCorrect = true;
			}
			else{ //! Asks again if incorrect choice
				cout << "\nIncorrect choice. Please enter only 1 or 2 depending on the character type you want to create.\n";
				cout << "1 - Character OR 2 - Fighter. Please choose correctly: ";
			}

		}

		bool characterCorrect = false; //! Flag for correct Character

		string name; //! Player's name
		int level; //! Player's level
		int size; //! Player's size
		int fightStyle; //! Fighter's fighting style

		//! While character not correct keep asking
		while (!characterCorrect){

			cout << "\nEnter your player's name: ";
			cin.ignore();
			getline(cin, name); //! Get name even with spaces

			cout << "Enter your level: ";
			cin >> level; //! Get level

			cout << "Enter choose size from the list below:\n";
			//! Display all the sizes possible
			displayCharacterSize();
			cin >> size; //! Get size

			if (choice == 2){ //! If fighter
				cout << "Enter your Fighter Style from the list below:\n";
				//! Displays all the fighting style possible
				displayFighterStyle();
				cin >> fightStyle; //! Get fighting style if fighter
			}

			if (!cin){ //! Error while inputting
				cout << "\nIncorrect Input. Please enter again all data.";
			}
			else if (level<1){ //! Check level
				while (level < 1){ //! if level is still not good keep asking
					cout << "\nIncorrect Level entered. Please enter level again: ";
					cin >> level;
				}
			}
			else if (size<0 || size>3){ //! Check size
				while (size<0 || size>3){ //! If size is still not good check size
					cout << "\nIncorrect Size entered. Please enter Size again: ";
					displayCharacterSize();
					cin >> size;
				}
			}
			else if (choice == 2 && (fightStyle<0 || fightStyle>2)){
				while (fightStyle<0 || fightStyle>2){ //! if fighting style is still not good ask again
					cout << "\nIncorrect Fighting Style entered. Please enter style again from the list below: ";
					displayFighterStyle();
					cin >> fightStyle;
				}
			}

			//! Display information entered for now and ask if want to continue
			cout << "\n\nHere are the data you entered for your character: ";
			cout << "\nName: " << name << "\nLevel: " << level << "\nSize: " << (CharacterSize)size;

			if (choice == 2)
				cout << "\nFighting Style: " << (FightStyle)fightStyle;

			string changeData = "";
			bool changeDataCorrect = false; //! Flag to check if continue input is correct
			cout << "\nDo you want to change anything? (Y/N) ";
			while (!changeDataCorrect){
				cin >> changeData;
				if (changeData == "N"){
					characterCorrect = true;
					changeDataCorrect = true;
				}
				else if (changeData == "Y"){
					changeDataCorrect = true;
				}
				else
				{
					cout << "Please enter Y or N: ";
				}

			}

		}

		//! Generates the ability score
		cout << "\n\nTime to generate the ability scores...";

		srand(time(0)); //! Give a starting point to the random function

		int arrRand[Character::NO_ABILITY]; //Create an array with the no of abilities a character should have
		int *ptr = arrRand; //! Pointer that points to newly created array

		int arrAbilityScores[Character::NO_ABILITY];//! Creates a second array of ability scores that will be used to passed to the Character constructor

		//! For loop to generate random numbers between 3 and 18 and but them in the first created array
		cout << "\n\nThe random scores are: ";
		for (int i = 0; i < Character::NO_ABILITY; i++){
			arrRand[i] = rand() % 16 + 3;
			cout << arrRand[i] << " ";
		}

		//! Variable use for input
		int chosenScr = 0;

		//! Make user chooses which number generated he wants to assign to each score.
		cout << "\nPlease choose a score from the numbers obtained for the following: \n";
		for (int i = 0; i < Character::NO_ABILITY - 1; i++){

			//! Outputs the number that are left ot be chosen
			cout << "The numbers left are: ";
			for (int i = 0; i < Character::NO_ABILITY; i++){
				if (arrRand[i] != 0)
					cout << arrRand[i] << " ";
			}

			//! For each ability, (using the enumrated type), choose score
			cout << "\n" << CharacterAbility(i) << ": ";
			cin >> chosenScr;

			//! If incorrect input, program dies
			if (!cin){
				cerr << "Program dies";
				exit(1);
			}

			//! Check if number entered is in random generated array. if not ask user to enter again until number is valid
			while (!checkScr(ptr, chosenScr)){
				cout << "Please choose a correct no.: ";
				cin >> chosenScr;
			}

			//! Initialise the number chosen to the respective ability score
			arrAbilityScores[i] = chosenScr;
			cout << "\n";
		}

		//! Add remaining ability score
		for (int i = 0; i < Character::NO_ABILITY; i++){
			if (arrRand[i] != 0){
				arrAbilityScores[Character::NO_ABILITY - 1] = arrRand[i];
				break;
			}
		}

		if (choice == 1){
			//! Create Character Object
			currentCharacter = new Character(name, "1d10", arrAbilityScores, level, (CharacterSize)size);
			if (!currentCharacter->validateNewCharacter()){ //! Validate
				//! If invalid character
				cout << "Incorrect Character. Exiting program...";
				system("pause");
				exit(1);
			}
		}
		else{
			//! Create fighter
			currentCharacter = new Fighter(name, arrAbilityScores, (FightStyle)fightStyle, level, (CharacterSize)size);
			if (!currentCharacter->validateNewCharacter()){ //! Validate{
				//! If incorrect Fighter end program
				cout << "Incorrect Fighter. Exiting program...";
				system("pause");
				exit(1);
			}
		}
	}

}

void CharacterController::editCharacter(){


}

void CharacterController::saveCharacter(){

	cout << "Saving the character...\n";

	currentCharacter->saveCharacter();

}


void CharacterController::displayCharacterSize(){

	cout << (int)CharacterSize::FINE << " - FINE\n"
		<< (int)CharacterSize::TINY << " - TINY\n"
		<< (int)CharacterSize::HUGE << " - HUGE\n"
		<< (int)CharacterSize::COLOSSAL << " - COLOSSAL\nPlease choose: ";

}

void CharacterController::displayFighterStyle(){

	cout << (int)FightStyle::ARCHERY << " - " << FightStyle::ARCHERY << "\n"
		<< (int)FightStyle::DEFENSE << " - " << FightStyle::DEFENSE << "\n"
		<< (int)FightStyle::DUELING << " - " << FightStyle::DUELING << "\n";

}

//! function to check if a number is in an array
//! @param array pointer - array to check
//! @param number - number to check if in array
//! @return true - if number is in array, false - if not
bool CharacterController::checkScr(int *arr, int scr){

	//! If number is 0 return false (no. already used in array/element does not exist)
	if (scr == 0)
		return false;

	//! for loop to check for number in each element
	for (int i = 0; i < Character::NO_ABILITY; i++){
		if (*(arr + i) == scr) //! Use pointer to look through array
		{
			*(arr + i) = NULL; //! Fag that number has been used
			return true; //! Return true if found
		}
	}
	return false; //! Return false if not found

}