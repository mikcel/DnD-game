//!
//! @file 
//! @brief Implementation file for Character Controller

#include "CharacterController.h"
#include "CharacterDirector.h"
#include "FighterBuilder.h"
#include "BullyBuilder.h"
#include "NimbleBuilder.h"
#include "TankBuilder.h"

//! Default Constructor
CharacterController::CharacterController()
{
	/*Intentionally left blank*/
}

//! Parametrized Constructor
//! @param Character pointer
CharacterController::CharacterController(Character *currentCharacter){

	this->currentCharacter = currentCharacter; //! Sets the current Character to the object passed

}

//! Destructor
CharacterController::~CharacterController()
{
}

//! Getter to obtain the current Character
//! @return Character pointer to the current Character
Character* CharacterController::getCurrentCharacter(){
	return currentCharacter;
}

//! Setter for Current character
//! @param Character pointer to an object
//! @return -
void CharacterController::setCurrentCharacter(Character *character){
	currentCharacter = character->clone();
}

//! Method to create a Character
void CharacterController::createCharacter(){
	
	cout << "==== FIGHTER CREATION ====" << endl << endl;

	cout << "Let's create your fighter !!!" << endl;

	bool characterCorrect = false; //! Flag for correct Character

	string name; //! Player's name
	int level; //! Player's level
	int size; //! Player's size
	int fightStyle; //! Fighter's fighting style
	int fighterType; //! Fighter's Type

	//! While character not correct keep asking
	while (!characterCorrect){

		cout << "\nEnter your fighter's name: ";
		cin.ignore();
		getline(cin, name); //! Get name even with spaces

		cout << "\nEnter your level: ";
		bool correctLevel = false;
		while (!correctLevel){ //! if level is still not good keep asking
			while (!(cin >> level)){
				cout << "\nIncorrect Level entered. Please enter level again: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (level < 1){
				cout << "\nIncorrect Level entered. Please enter level again: ";
			}
			else{
				correctLevel = true;
			}
		}

		cout << "\nEnter choose size from the list below:\n";
		//! Display all the sizes possible
		displayCharacterSize();
		bool correctSize = false;
		while (!correctSize){ //! If size is still not good check size
			while (!(cin >> size)){
				cout << "\nIncorrect Size entered. Please enter Size again: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (size <0 || size>3){
				cout << "\nIncorrect Size entered. Please enter Size again: ";
			}
			else{
				correctSize = true;
			}
		}

		cout << "\nEnter your Fighter Style from the list below:\n";
			//! Displays all the fighting style possible
			displayFighterStyle();
			cout << "Please choose: ";
			bool correctStyle = false;
			while (!correctStyle){ //! if fighting style is still not good ask again
				while (!(cin >> fightStyle)){
					cout << "\nIncorrect Fighting Style entered. Please enter style again: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				if (fightStyle<0 || fightStyle>2){
					cout << "\nIncorrect Fighting Style entered. Please enter style again: ";
				}
				else{
					correctStyle = true;
				}
			}
		

		cout << "\nFighter Types available: " << endl;
		displayFighterType();
		cout << "Which type of fighter do you want to create (Enter the corresponding number)? ";
		while (!(cin >> fighterType)){
			cout << "Incorrect Fighter type. Try again: ";
			cin.ignore();
			cin.clear();
		}

		//! Display information entered for now and ask if want to continue
		cout << "\nHere are the data you entered for your fighter: ";
		cout << "\nName: " << name << "\nLevel: " << level << "\nSize: " << (CharacterSize)size;
			cout << "\nFighting Style: " << (FightStyle)fightStyle;
		cout << "\nFighter Type: " << (FighterType)fighterType;

		string changeData = "";
		bool changeDataCorrect = false; //! Flag to check if continue input is correct
		cout << "\nPlease note that once set the fighter type cannot be modified. \nDo you want to change anything? (Y/N) ";

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

	CharacterDirector chrDirect;
	switch (fighterType)
	{
		case 0:
			chrDirect.setFighterBuilder(new BullyBuilder());
			break;
		case 1:
			chrDirect.setFighterBuilder(new NimbleBuilder());
			break;
		case 2:
			chrDirect.setFighterBuilder(new TankBuilder());
			break;
	}

	chrDirect.constructFighter(name,level,(FightStyle)fightStyle,(CharacterSize)size);

		//! Create fighter
	currentCharacter = chrDirect.getFighter();
		if (!currentCharacter->validateNewCharacter()){ //! Validate{
			//! If incorrect Fighter end program
			cout << "Incorrect Fighter.  Character will not be saved";
			system("pause");
			currentCharacter = NULL;
			return;
		}

	bool flagCorrectChoice = false;
	string itemChoice = "";
	
	//! Ask if user wants to add item to backpack
	cout << "\nDo you want to add items to your backpack? (Y/N) "; 
	while (!flagCorrectChoice){
		cin >> itemChoice; //! Enter choice and check
		if (itemChoice == "Y" || itemChoice == "N")
			flagCorrectChoice = true;
		else
		{
			cout << "Incorrect choice. Please enter Y or N: "; //! Error message
		}
	}

	if (itemChoice == "Y"){ //! If correct choice call method to add item
		addItem();
	}

	cout << "\nFighter Created!\nThe Stats are:\n\n" << *dynamic_cast<Fighter*>(currentCharacter) << endl;

	saveCharacter(); //! Save Character 

	system("pause");

}

//! Method to edit character
//! @return - 
void CharacterController::editCharacter(){
	cout << "==== FIGHTER EDITION ====" << endl << endl;

	//! Get all files available in the Characters folder
	vector<string> chrFiles = getFilesInsideFolderNoExtension("SaveFiles/Characters/");

	if (chrFiles.size() == 0) { //! Check if files exist or not
		cout << "No Fighter has yet been created.\n";
		system("pause");
		return;
	}
	cout << "The saved files available are: \n";
	for (auto i : chrFiles) { //! Output all save files available
		cout << i << "\n";
	}
	string fileName = "";
	bool fileNameCorrect = false; //! Ask for name of the file to load
	cout << "\nPlease enter the name of the Fighter you want to load: ";
	while (!fileNameCorrect) {
		cin >> fileName; //! Check if name is correct
		if (find(chrFiles.begin(), chrFiles.end(), fileName) != chrFiles.end()) {
			currentCharacter = readCharacterFile(fileName);
			fileNameCorrect = true;
		}
		else { //! Error message if file does not exist
			cout << "File name does not exist. Try again: ";
		}
	}

	system("cls"); //! Clear screen and show the stats of the loaded fighter
		cout << *(dynamic_cast<Fighter*>(currentCharacter));

	int menuChoice = 0;
	string menuChoiceStr;
	bool charChanged = false;

	//! While do not want to exit
	while (menuChoice != 10){
		//! Output the menu to choose what to edit in the character
		cout << "Currently edited character: " << currentCharacter->getName() << endl << endl;
		cout << "Please choose from the following:\n"
			<< "0 - Display Fighter\n"
			<< "1 - Save Character\n"
			<< "2 - Edit Name\n"
			<< "3 - Edit Level\n"
			<< "4 - Edit Size\n"
			<< "5 - Add Item\n"
			<< "6 - Remove Item\n"
			<< "7 - Equip Item\n"
			<< "8 - Unequip Item\n"
			<< "9 - Edit Fighting Style\n"
			<< "10 - Return\n";
		cout << "Please choose: ";
		while (!(cin >> menuChoiceStr)){
			cout << "Enter a valid input." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		try { //! Check valid input from user
			menuChoice = stoi(menuChoiceStr);
		}
		catch (...) {
			cout << "Enter a valid input." << endl;
			continue;
		}

		cout << endl;

		//! Switch case depending on the chocie of the user
		bool styleChangeCorrect = true;
		switch (menuChoice){
			case 0: //! Display Character
				if (system("CLS"))
				{
					system("clear");
				}
				cout << *(dynamic_cast<Fighter*>(currentCharacter)) << endl;
				break;
			case 1: //! Save Character
				saveCharacter();
				break;
			case 2: //! Edit the character's name
			{
				//! Ask and set new name
				string newName = "";
				cout << "Please enter the new Character name: ";
				cin >> newName;
				currentCharacter->setName(newName); 
				cout << "Name set.\n";
				cout << *currentCharacter;
				charChanged = true;
				break;
			}
			case 3: //! Edit the character's level
			{
				int level = 0; //! Ask new level and set level
				cout << "Please enter the new Character level (>1): ";
				bool correctLevel = false;
				while (!correctLevel){ //! if level is still not good keep asking
					while (!(cin >> level)){
						cout << "\nIncorrect Level entered. Please enter level again: ";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					if (level < 1){
						cout << "\nIncorrect Level entered. Please enter level again: ";
					}
					else{
						correctLevel = true;
					}
				}

				if (level != -1){
					currentCharacter->setLevel(level);
					cout << "Level changed.";
					charChanged = true;
				}
				else{
					cout << "Level not changed.";
				}
				break;
			}
			case 4:{ //! Edit Character's Size
		
				int size = -1; //! Display available size list and ask for new size
				cout << "Please enter the new Character Size by selecting from the list below:\n";
				displayCharacterSize();
				bool correctSize = false;
				while (!correctSize){ //! If size is still not good check size
					while (!(cin >> size)){
						cout << "\nIncorrect Size entered. Please enter Size again: ";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					if (size <0 || size>3){
						cout << "\nIncorrect Size entered. Please enter Size again: ";
					}
					else{
						correctSize = true;
					}
				}
				if (size != -1){
					currentCharacter->setSize((CharacterSize)size); //! Set the size if correct
					cout << "Size changed.";
					charChanged = true;
				}
				else{
					cout << "Size not changed.";
				}
					   
				break;
			}
			case 5:{ //! Add a new item to backpack
				charChanged = addItem();
				break;
			}
			case 6:{ //! Remove an item from backpack

				vector <Item*> backItem;
				//! Get all backpack contents
				backItem = currentCharacter->getBackpackContents()->getContents();

				if (backItem.size() == 0) //! Check if there are items
					cout << "\n:( There are no item in the backpack!!!";
				else{

					int itemID = 0;
					bool flagCorrect = false; //! Display all available items
					cout << "\nHere are the items that are in your backpack: ";
					for (int i = 0; i < backItem.size(); i++){
						cout << "\nItem ID: " << i << "\n" << *backItem[i];
					}

					cout << "\nPlease enter the correct item ID: ";
					//! Ask user to choose item
					while (itemID != -1 && !flagCorrect){

						while (!(cin >> itemID)){
							cout << "\nIncorrect Item Id entered. Try Again or else enter -1 to exit: ";
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}

						//! Check id entered
						if (itemID >= 0 && itemID<backItem.size()){

								//! If Wearing item was ok
								if (!currentCharacter->removeItemBack(backItem[itemID])){
									cout << "\nError. Try Again or else enter -1 to exit: ";
								}
								else{
									cout << "Item Removed\n";
									flagCorrect = true;
									charChanged = true;
								}

						}
						else{
							//! Asks id for item again since incorrectly entered
							cout << "\nIncorrect Item Id entered. Try Again or else enter -1 to exit: ";

						}
					}

				}

				break;
			}
			case 7: //! Equip with an item
			{
				vector<Item*> backItem; //! Get backpack contents
					backItem = currentCharacter->getBackpackContents()->getContents();
				if (backItem.size() == 0) //! Check if there are items in backpack
					cout << "\n:( There are no Item that you can equip with!!! Try adding a new item first.\n";

				else{

					int itemID = 0; //! Identify each item in backpack
					bool flagCorrect = false;
					cout << "\nHere are the item(s) in your backpack that you can equip yourself with: ";

					//! output backcpack contents with id
					for (int i = 0; i < backItem.size(); i++){
						cout << "\nITEM ID: " << i << "\n" << *backItem[i];
					}

					cout << "\nPlease enter the correct item ID: ";
					//! Ask user to choose item
					while (itemID != -1 && !flagCorrect){

						while (!(cin >> itemID)){
							cout << "\nIncorrect Item Id entered. Try Again or else enter -1 to exit: ";
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}

						//! Check id entered
						if (itemID >= 0 && itemID<backItem.size()){
							//! If Wearing item was ok
							if (!currentCharacter->wearItem(backItem[itemID])){
								cout << "\nError. Try Again or else enter -1 to exit: ";
							}
							else{
								cout << "Item Equiped\n";
								flagCorrect = true;
								charChanged = true;
							}

						}
						else if (itemID!=-1){
							//! Asks id for item again since incorrectly entered
							cout << "\nIncorrect Item Id entered. Try Again or else enter -1 to exit: ";

						}
					}
				}

				break;
			}
			case 8:{ //! Unequip an item

				//! Get contents of currently worn item
				vector<Item*> holdItem;
				holdItem = currentCharacter->getCurrentWornItems()->getContents();
				//! check if there are items
				bool wearingItem = false;
				for (auto i : holdItem){
					if (i->getItemTypes() != ItemType::UNSPECIFIED)
						wearingItem = true;
				}

				if (!wearingItem)
					//! Telle user there are no items currently wearing
					cout << "\n:( You are wearing no items!!! Add a new one or equip yourself first.\n";

				else{

					int itemID = 0;
					bool flagCorrect = false;
					cout << "\nHere are the item(s) that you are currently wearing:";
					//! output all currently worn items with an id
					for (int i = 0; i < holdItem.size(); i++){
						if (holdItem[i]->getItemTypes() != ItemType::UNSPECIFIED){
							cout << "\nITEM ID: " << i << "\n" << *holdItem[i];
						}
					}

					cout << "\nPlease enter the correct item ID: ";
					//! ask user to enter id
					while (itemID != -1 && !flagCorrect){

						while (!(cin >> itemID)){
							cout << "\nIncorrect Item Id entered. Try Again or else enter -1 to exit: ";
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}

						//! Check id
						if (itemID != -1 && holdItem[itemID]->getItemTypes() != ItemType::UNSPECIFIED){

								//! Take off item
								if (!currentCharacter->takeOffItem(holdItem[itemID])){
									cout << "\nError. Try Again or else enter -1 to exit: ";
								}
								else{
									cout << "Item Unequiped \n";
									flagCorrect = true;
									charChanged = true;
								}

						}
						else if (itemID != -1){
							//! Ask to reenter id if incorretly entered
							cout << "\nIncorrect Item Id entered. Try Again or else enter -1 to exit: ";

						}
					}
				}

				break;
			}
			case 9:{ //! Change fighter style

				//! Check if a fighter is a character or not
				if (!dynamic_cast<Fighter*>(currentCharacter)){
					cout << "Not a fighter. Cannot modify.";
					styleChangeCorrect = false;
					break;
				}
				
				//! Display list of available fighter styles and ask user to select
				int style = -1;
				cout << "Please enter the new Fighter style selecting from the list below:\n";
				displayFighterStyle();
				bool correctStyle = false;
				while (!correctStyle){ //! if fighting style is still not good ask again
					while (!(cin >> style)){
						cout << "\nIncorrect Fighting Style entered. Please enter style again: ";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					if (style<0 || style>2){
						cout << "\nIncorrect Fighting Style entered. Please enter style again: ";
					}
					else{
						correctStyle = true;
					}
				}
				if (style != -1){ //! Set style

					dynamic_cast<Fighter*>(currentCharacter)->setStyle((FightStyle)style);
					cout << "Style changed.";
					charChanged = true;
				}
				else{
					cout << "Style not changed.";
				}

				break;
			}
			case 10: //! Return back to main menu
				break;
			
			default: //! Else incorrect menu choice
				cout << "Incorrect Menu choice. Try Again." << endl;
				continue;			
		}

		if (menuChoice != 0 && menuChoice != 10){ //! if not exiting save the character if all is valid
			if (menuChoice != 1 && styleChangeCorrect && charChanged)
				saveCharacter();
			system("pause"); //! Pause to show output and clear the console
			if (system("CLS"))
			{
				system("clear");
			}
			cout << endl;
		}

	}
	
}

//! Method to save Character
//! @return -
void CharacterController::saveCharacter(){

	cout << "Saving the character..." << endl;;

	//! get all saved files from the Characters folders
	vector<string> chrFiles = getFilesInsideFolderNoExtension("SaveFiles/Characters/");

	//! Check if file exist for the character name 
	bool foundFile = false;
	for (auto i : chrFiles){
		if (i == currentCharacter->getName()){
			foundFile = true;
			break;
		}
	}

	if (chrFiles.size() == 0 || !foundFile){ //! If file does not exist or there is no file file in the folder, save the character
		currentCharacter->saveCharacter();
		cout << "Saved Successfully!\n";
	}
	else{
		string choiceOverw = ""; //! If file already exist, ask user if he/she wants to overwrite the file
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

//! Method to read a Character form a file
//! @param string - the character file location
//! @param string - the Character name
//! @return pointer to a character object
Character* readCharacterFile(string charName){

	//! Open stream to read character
	ifstream inStream("SaveFiles/Characters/" + charName + ".txt", ios::in);

	if (!inStream){ //! If error in stream return nullptr
		return nullptr;
	}

	//! creates a temporary pointer to character
	Character * tempCharacter = nullptr;

	//! Variables to contain all data of a character
	string chrType = "";
	string strSize = "";
	string name;
	int level;
	int fightStyle;
	int fightType;

	//! read all the basic stats
	inStream >> chrType >> name >> level >> strSize;

	if (chrType == "fighter")
		inStream >> fightStyle >> fightType;

	//! Read the ability scores
	int abilityScr[Character::NO_ABILITY];
	for (int i = 0; i < Character::NO_ABILITY; i++){
		inStream >> abilityScr[i];
	}

	//! If character create a character object else create a fighter object
	if (chrType == "fighter"){
		tempCharacter = new Fighter(name, abilityScr, (FightStyle)fightStyle, level, (CharacterSize)stoi(strSize));
		dynamic_cast<Fighter*>(tempCharacter)->setType((FighterType)fightType);
	}

	//! get the item in the backpack
	string itemName;
	inStream.ignore();
	getline(inStream, itemName);
	getline(inStream, itemName);

	//! Create a null pointer for item
	Item *itmPoint = nullptr;
	
	//! while not read wornitem container, continue to read
	while (itemName != "wornItem"){

		//! Read an item and store it in the character's backpack
		itmPoint = readItemFile(itemName);
		tempCharacter->storeItem(itmPoint);
		getline(inStream, itemName);

	}

	//! REad the current worn items
	for (int i = 0; i < 7; i++){
		getline(inStream, itemName);
		if (itemName != "UNSPECIFIED"){
			itmPoint = readItemFile(itemName); //! Read item if not unspecified, store and wear it
			tempCharacter->storeItem(itmPoint);
			tempCharacter->wearItem(itmPoint);
		}
	}

	delete itmPoint;

	inStream.close();

	return tempCharacter; //! return the temporary pointer
}

//! Method to display all available character size
//! @return -
void CharacterController::displayCharacterSize(){

	cout << (int)CharacterSize::FINE << " - FINE\n"
		<< (int)CharacterSize::TINY << " - TINY\n"
		<< (int)CharacterSize::HUGE << " - HUGE\n"
		<< (int)CharacterSize::COLOSSAL << " - COLOSSAL\nPlease choose: ";

}

//! Method to display all available fighter style
//! @return -
void CharacterController::displayFighterStyle(){

	cout << (int)FightStyle::ARCHERY << " - " << FightStyle::ARCHERY << "\n"
		<< (int)FightStyle::DEFENSE << " - " << FightStyle::DEFENSE << "\n"
		<< (int)FightStyle::DUELING << " - " << FightStyle::DUELING << "\n";

}

//! Method to display all available fighter types
//! @return -
void CharacterController::displayFighterType(){

	cout << (int)FighterType::BULLY << " - " << FighterType::BULLY << "\n"
		<< (int)FighterType::NIMBLE << " - " << FighterType::NIMBLE << "\n"
		<< (int)FighterType::TANK  << " - " << FighterType::TANK << "\n";

}

//! Method to add an item to the character's backpack
//! @return - true if item(s) added, false otherwise
bool CharacterController::addItem(){

	//! Get all item files avialable in the respective folder
	vector<string> filesInFolder = getFilesInsideFolderNoExtension("SaveFiles/Items");

	if (filesInFolder.size() == 0){ //! Check there are any saved items
		cout << "There are no items files available. Please create items and then edit the character to add the items.\n";
		cin.ignore();
		system("pause");
		return false;
	}
	else{ 
		//! If there are saved items, ask user to input item file name.
		bool itemAdded = false;
		Item* itmPoint = nullptr;
		int itemID = 0;

		//! while there are items in the folders to add and user do not want to stop
		while (itemID != -1 && filesInFolder.size() != 0){

			//! Display all available files
			cout << "The item template files available are:\n";
			for (int i = 0; i < filesInFolder.size(); i++){
				cout << i << " - " << filesInFolder[i] << "\n";
			}

			//! Ask user for item name 
			cout << "\nPlease enter the Item ID (-1 to stop adding): ";

			//! Check user input
			while (!(cin >> itemID)){
				cout << "Incorrect No. Please try again (-1 to stop): ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			//! Check if item id entered is correct
			if (itemID >= 0 && itemID<filesInFolder.size()){

				//! Check if item is already in backapck
				bool itemFound = false;
				for (auto i : currentCharacter->getBackpackContents()->getContents()){
					if (i->getItemName() == filesInFolder[itemID])
						itemFound = true;
				}

				//! If item not in backpack add the item
				if (!itemFound){
					itmPoint = readItemFile(filesInFolder[itemID]);
					currentCharacter->storeItem(itmPoint); 
					cout << "Item Added.\n";
					filesInFolder.erase(filesInFolder.begin() + itemID);
					itemAdded = true;
				}
				else{ //! If item in backpack erase from the available list and ask again
					cout << "Item already in backpack. Cannot add again.\n";
					filesInFolder.erase(filesInFolder.begin() + itemID);
				}
			}
			else if (itemID != -1){
				cout << "Incorrect No. Please try again." << endl;
			}

		}

		delete itmPoint;
		return itemAdded;
	}

}
