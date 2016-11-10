
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

		vector<string> chrFiles = getFilesInsideFolderNoExtension("SaveFiles/Characters/");
		
		if (chrFiles.size() == 0){
			cout << "There are no saved files.\n Returning to main menu...\n";
			system("pause");
			return;
		}
		cout << "The saved files available are: \n";
		for (auto i : chrFiles){
			cout << i << "\n";
		}
		string fileName = "";
		bool fileNameCorrect = false;
		cout << "\nPlease enter the name of the Character you want to load: ";
		while (!fileNameCorrect){
			cin >> fileName;
			if (find(chrFiles.begin(), chrFiles.end(), fileName) != chrFiles.end()){
				readCharacterFile(fileName, "SaveFiles/Character");
				fileNameCorrect = true;
			}
			else{
				cout << "File name does not exist. Try again: ";
			}
		}

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
				cout << "Please choose: ";
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
					cout << "\nIncorrect Fighting Style entered. Please enter style again from the list below: \n";
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

		bool flagCorrectChoice = false;
		string itemChoice = "";
		cout << "Do you want to add items to your backpack? (Y/N) ";
		while (!flagCorrectChoice){
			cin >> itemChoice;
			if (itemChoice == "Y" || itemChoice == "N")
				flagCorrectChoice = true;
			else
			{
				cout << "Incorrect choice. Please enter Y or N: ";
			}
		}

		if (itemChoice == "Y"){

			vector<string> filesInFolder = getFilesInsideFolderNoExtension("SaveFiles/Items");
			
			if (filesInFolder.size() != 0){
				cout << "The items template file available are:\n";
				for (auto i : filesInFolder){
					cout << i << "\n";
				}
				string itemFileName = "";
				bool itemFileFound = false;
				cout << "\nPlease enter the Item file name: ";
				while (!itemFileFound && itemFileName!="-1"){
					cin >> itemFileName;
					if (find(filesInFolder.begin(), filesInFolder.end(), itemFileName) != filesInFolder.end()){
						/*read item from file*/
						itemFileFound = true;
					}
					else{
						cout << "File not found. Please try again (-1 to stop): ";
					}
				}

			}
			else{
				cout << "There are no items files available. Please create items and then edit the character to add the items.\n";
				cin.ignore();
				system("pause");
			}
		}


		if (choice == 1){
			//! Create Character Object
			currentCharacter = new Character(name, "1d10", arrAbilityScores, level, (CharacterSize)size);
			if (!currentCharacter->validateNewCharacter()){ //! Validate
				//! If invalid character
				cout << "Incorrect Character. Character will not be saved";
				system("pause");
				currentCharacter = NULL;
			}
			else{
				cout << "Character Created!\nThe Stats are:\n" << *currentCharacter;
				saveCharacter();

			}
		}
		else{
			//! Create fighter
			currentCharacter = new Fighter(name, arrAbilityScores, (FightStyle)fightStyle, level, (CharacterSize)size);
			if (!currentCharacter->validateNewCharacter()){ //! Validate{
				//! If incorrect Fighter end program
				cout << "Incorrect Fighter.  Character will not be saved"<< *currentCharacter;
				system("pause");
				currentCharacter = NULL;
			}
			else{
				cout << "Fighter Created!\nThe stats are:\n" << *currentCharacter;
				saveCharacter();
			}
		}

		system("pause");
	}


}

void CharacterController::editCharacter(){

	if (currentCharacter==NULL){
		cout << "No Character has yet been created.\n";
		system("pause");
		return;
	}

	int menuChoice = 0;

	while (menuChoice!=5){

		cout << "Please choose from the following:\n"
			<< "1 - Save Character\n"
			<< "2 - Edit Name\n"
			<< "3 - Edit Level\n"
			<< "4 - Edit Size\n"
			<< "5 - Return\n";
		cout << "Please choose: ";
		cin >> menuChoice;
		system("cls");
		switch (menuChoice){
			case 1:
				saveCharacter();
				break;
			case 2:
			{
					  string newName = "";
					  cout << "Please enter the new Character name: ";
					  cin >> newName;
					  currentCharacter->setName(newName);
					  cout << "Name set.\n";
					  cout << *currentCharacter;
					  break;
			}
			case 3:
			{
					  int level = 0;
					  cout << "Please enter the new Character level (>1): ";
					  while (level < 1){
						cin >> level;
						if (level < 1){
							cout << "Incorrect Level. Try again (-1 to stop): ";
						}
						if (level == -1){
							break;
						}
					  }
					  if (level != -1){
						currentCharacter->setLevel(level);
						cout << "Level changed.";
					  }
					  else{
						  cout << "Level not changed.";
					  }
					  break;
			}
			case 4:{
		
					   int size = -1;
					   cout << "Please enter the new Character Size by selecting from the list below: ";
					   displayCharacterSize();
					   while (size < 0 || size>3){
						   cin >> size;
						   if (size < 0 || size>3){
							   cout << "Incorrect Size. Try again (-1 to stop): ";
						   }
						   if (size == -1){
							   break;
						   }
					   }
					   if (size != -1){
						   currentCharacter->setSize((CharacterSize)size);
						   cout << "Size changed.";
					   }
					   else{
						   cout << "Size not changed.";
					   }
					   
					   break;
			}
			case 5:
				break;
			default:
				cout << "Incorrect Menu choice. Try Again. ";
				
				break;			
		}
		if (menuChoice != 5){
			system("pause");
			system("cls");
		}

	}
	
}

void CharacterController::saveCharacter(){

	cout << "Saving the character...\n";

	vector<string> chrFiles = getFilesInsideFolderNoExtension("SaveFiles/Characters/");

	bool foundFile = false;
	for (auto i : chrFiles){
		if (i == currentCharacter->getName()){
			foundFile = true;
			break;
		}
	}

	if (chrFiles.size() ==0 || !foundFile){
		currentCharacter->saveCharacter();
		cout << "Saved Successfully!\n";
	}
	else{
		string choiceOverw = "";
		cout << "A file with the same name already exists. Do you want to overwrite it? (Y/N) ";
		cin >> choiceOverw;
		while (choiceOverw != "Y" && choiceOverw != "N"){
			cout << "Incorrect choice. Please enter again: ";
			cin >> choiceOverw;
		}
		if (choiceOverw == "Y")
		{
			currentCharacter->saveCharacter();
			cout << "Overwritten Successfully!\n";
		}
		else{
			cout << "File not overwritten.\n";
		}
	}

}

void CharacterController::readCharacterFile(string charName, string charFileLocation){

	ifstream inStream("SaveFiles/Characters/" + charName + ".dat", ios::in | ios::binary);

	string chrType = "";
	string strSize = "";
	string name;
	string hitDice;
	int level;
	int fightStyle;

	inStream >> chrType >> name >> hitDice >> level >> strSize >> fightStyle;

	int abilityScr[Character::NO_ABILITY];
	for (int i = 0; i < Character::NO_ABILITY; i++){
		inStream >> abilityScr[i];
	}

	if (chrType == "character")
		currentCharacter = new Character(name, hitDice, abilityScr, level, (CharacterSize)stoi(strSize));
	else
		currentCharacter = new Fighter(name, abilityScr, (FightStyle)fightStyle, level, (CharacterSize)stoi(strSize));

	inStream.close();

	cout << *currentCharacter;

	system("pause");
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
