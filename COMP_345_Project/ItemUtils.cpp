#include "ItemUtils.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Item.h"
#include "ItemContainer.h"
#include "Character.h"
#include "FolderUtils.h"
#include "Enums.h"
using namespace std;

//! Free Function to edit an Item File
void editItem() {
	cout << "==== ITEM EDITION ====" << endl << endl;
	int userChoice = -1;
	while (true) {
		cout << "Enter the index of the item you wish to edit.\nEnter -1 to quit." << endl;
		vector<string> ItemFileNames= getFilesInsideFolderNoExtension("SaveFiles/Items");
		int itemIndex = 0;
		for (auto i : ItemFileNames) {
			cout << itemIndex << ": " << i << endl;
			itemIndex++;
		}

		cin >> userChoice;
		
		while (cin.fail() || userChoice < -1 || userChoice > ItemFileNames.size() -1) {
			cout << "Incorrect Input. Please enter a correct number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> userChoice;
		}

		if (userChoice == -1) {
			return;
		}
		string chosenItem = ItemFileNames[userChoice];
		Item* item = readItemFile(chosenItem);
		cout << "Selected: " << item->getItemName() << endl;
		cout << "What do you want to modify?" << endl;
		cout << "0: Item Name\n1: Buff\nEnter -1 to quit." << endl;
		cin >> userChoice;

		while (cin.fail() || userChoice < -1 || userChoice > 1) {
			cout << "Incorrect Input. Please enter a valid number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> userChoice;
		}

		if (userChoice == 0) {
			cout << "Enter the new name of the item." << endl;
			string  newItemName;
			cin.ignore();
			getline(cin, newItemName);
			item->setItemName(newItemName);
			item->saveItem();
			delete item;
		}
		else if (userChoice == 1) {
			//buffs
				
			int choiceBuff = 0;
			int choiceAmount = 0;
			while (true) { //! Ask for buff choice
				cout << "Current buffs:" << endl;
				for (auto bu : item->getBuffs()) {
					cout << "buff type " << bu.getBuffType() << endl;
					cout << "buff amount " << bu.getBuffAmount() << endl;
				}
				cout << "\nChoose the buffs for this item from the list below:\nEnter -1 to stop picking buffs.\n";
				cout << (int)BuffType::INTELLIGENCE << " - " << BuffType::INTELLIGENCE << "\n"
					<< (int)BuffType::WISDOM << " - " << BuffType::WISDOM << "\n"
					<< (int)BuffType::ARMOR_CLASS << " - " << BuffType::ARMOR_CLASS << "\n"
					<< (int)BuffType::STRENGTH << " - " << BuffType::STRENGTH << "\n"
					<< (int)BuffType::CHARISMA << " - " << BuffType::CHARISMA << "\n"
					<< (int)BuffType::CONSTITUTION << " - " << BuffType::CONSTITUTION << "\n"
					<< (int)BuffType::DEXTERITY << " - " << BuffType::DEXTERITY << "\n"
					<< (int)BuffType::ATTACK_BONUS << " - " << BuffType::ATTACK_BONUS << "\n"
					<< (int)BuffType::DAMAGE_BONUS << " - " << BuffType::DAMAGE_BONUS << "\n"
					<< "-1 to stop\n" << endl;

				cout << "Enter choice: " << endl;
				cin >> choiceBuff;
				while (cin.fail() || choiceBuff < -1 || choiceBuff >(int)BuffType::DAMAGE_BONUS) {
					cout << "Incorrect Input. Please enter a valid number: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> choiceBuff;
				}

				if (choiceBuff == -1) {
					break;
				}

				cout << "Enter amount: " << endl;
				cin >> choiceAmount;
				while (cin.fail() || (choiceAmount < 0 && choiceAmount != -1)) {
					cout << "Incorrect Input. Please enter a valid number: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> choiceAmount;
				}

				if (choiceAmount == -1) {
					break;
				}
				vector<Buff> buffs = item->getBuffs();
				bool buffExist = false;
				int buffIterator = 0;
				for (auto b : buffs) {
					if (b.getBuffType() == (BuffType)choiceBuff) {
						buffExist = true;
						buffs[buffIterator].setBuffAmount(choiceAmount);
						break;
					}
					buffIterator++;
				}
				if (!buffExist) {
					buffs.push_back(Buff((BuffType)choiceBuff, choiceAmount));
				}
				item->setBuffs(buffs);

			}
			if (item->getItemTypes() == ItemType::WEAPON){
				Weapon* weapon = dynamic_cast<Weapon*>(item);
				if (!weapon->validateWeapon()){
					cout << "Invalid Weapon!\nDiscarding changes.";
					delete weapon;
					return;
				}
			}
			else{
				if (!item->validateItem()){
					cout << "Invalid Weapon!\nDiscarding changes.";
					delete item;
					system("pause");
					return;
				}
			}

			cout << "Saving item..." << endl;
			item->saveItem();
			cout << "Item saved." << endl;
		}
		else if (userChoice == -1) {
			return;
		}
		else {
			cout << "Invalid input.\nExiting" << endl;
			return;
		}

		cout << "Edit another Item?\nEnter 0 to continue, -1 to quit." << endl;
		cin >> userChoice;
		while (cin.fail()) {
			cout << "Incorrect Input. Please enter a correct number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> userChoice;
		}

		if (userChoice == 0) {
			continue;
		}
		else if (userChoice == -1) {
			return;
		}
	}
}

//! Free function to create a new item
void createItem() {
	cout << "==== ITEM CREATION ====" << endl << endl;
	string name = ""; //! Item name
	int itemType = (int)ItemType::UNSPECIFIED; //! item type
	int choiceItem = -1; //! Item or weapon
	int range = 0; //! Range of weapon
	vector<Buff> vecBuff(0); //! Vector for buff

	//! Ask for weapon or item
	cout << "\nDo you want to create an Item - 0 or a Weapon - 1? ";
	cin >> choiceItem;

	//! check choice
	while (cin.fail() || choiceItem<0 || choiceItem>1) { //!  ask to continue enter if incorrect
		cout << "Incorrect choice. Please choose only 0 or 1: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choiceItem;
	}

	if (choiceItem == 0) { //! If item or weapon

		cout << "\nLet's create a new Item!!!";

		cout << "\nEnter the Item Name: ";
		cin.ignore();
		getline(cin, name); //! Get name

							//! output all posisible type and ask to choose
		cout << "Enter the Item type no. from the list provided below:\n";
		cout << (int)ItemType::HELMET << " - " << ItemType::HELMET << "\n"
			<< (int)ItemType::ARMOR << " - " << ItemType::ARMOR << "\n"
			<< (int)ItemType::SHIELD << " - " << ItemType::SHIELD << "\n"
			<< (int)ItemType::RING << " - " << ItemType::RING << "\n"
			<< (int)ItemType::BELT << " - " << ItemType::BELT << "\n"
			<< (int)ItemType::BOOTS << " - " << ItemType::BOOTS << "\n"
			<< (int)ItemType::WEAPON << " - " << ItemType::WEAPON << "\n";
		cout << "Enter choice: ";
		cin >> itemType;
		//! Continue to ask if choice is incorrectly entered
		while (cin.fail() || itemType<0 || itemType>6) {
			cout << "Incorrect choice. Please enter again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> itemType;
		}

		int choiceBuff = 0; //! Buff choice
		while (choiceBuff != -1) { //! While player wants to continue add buff
			cout << "\nChoose the buffs for this item from the list below: \n";
			//! Display all possible buffs
			cout << (int)BuffType::INTELLIGENCE << " - " << BuffType::INTELLIGENCE << "\n"
				<< (int)BuffType::WISDOM << " - " << BuffType::WISDOM << "\n"
				<< (int)BuffType::ARMOR_CLASS << " - " << BuffType::ARMOR_CLASS << "\n"
				<< (int)BuffType::STRENGTH << " - " << BuffType::STRENGTH << "\n"
				<< (int)BuffType::CHARISMA << " - " << BuffType::CHARISMA << "\n"
				<< (int)BuffType::CONSTITUTION << " - " << BuffType::CONSTITUTION << "\n"
				<< (int)BuffType::DEXTERITY << " - " << BuffType::DEXTERITY << "\n"
				<< (int)BuffType::ATTACK_BONUS << " - " << BuffType::ATTACK_BONUS << "\n"
				<< (int)BuffType::DAMAGE_BONUS << " - " << BuffType::DAMAGE_BONUS << "\n"
				<< "-1 to stop\n";
			cout << "Enter choice: ";
			cin >> choiceBuff; //! Enter buff choice

							   //! Check for buff choice. Ask again if incorrectly entered
			while (cin.fail() || choiceBuff != -1 && (choiceBuff<0 || choiceBuff>8)) {
				cout << "Incorrect Input. Please enter a correct number: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> choiceBuff;
			}

			//! If do not want to exxit
			if (choiceBuff != -1) {
				int amount = 0;
				//! Ask for buff amount
				cout << "Enter buff's amount: ";
				cin.ignore();
				cin >> amount;
				//! Put in vector for buff
				vecBuff.push_back(Buff((BuffType)choiceBuff, amount));
			}

		}
	}
	else {
		//! Create a weapon
		cout << "\nLet's create a new Weapon!!!";
		cout << "\nEnter the Weapon Name: ";
		cin.ignore();
		getline(cin, name); //! Get weapon name

		cout << "\nPlease enter the weapon's range: ";
		cin >> range; //! Get weapon range

		while (cin.fail()) {
			cout << "Incorrect Input. Please enter a correct number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> range;
		}

		int choiceBuff = 0;
		while (choiceBuff != -1) { //! Ask for buff choice
			cout << "\nChoose the buffs for this weapon from the list below: \n";
			cout << (int)BuffType::INTELLIGENCE << " - " << BuffType::INTELLIGENCE << "\n"
				<< (int)BuffType::WISDOM << " - " << BuffType::WISDOM << "\n"
				<< (int)BuffType::ARMOR_CLASS << " - " << BuffType::ARMOR_CLASS << "\n"
				<< (int)BuffType::STRENGTH << " - " << BuffType::STRENGTH << "\n"
				<< (int)BuffType::CHARISMA << " - " << BuffType::CHARISMA << "\n"
				<< (int)BuffType::CONSTITUTION << " - " << BuffType::CONSTITUTION << "\n"
				<< (int)BuffType::DEXTERITY << " - " << BuffType::DEXTERITY << "\n"
				<< (int)BuffType::ATTACK_BONUS << " - " << BuffType::ATTACK_BONUS << "\n"
				<< (int)BuffType::DAMAGE_BONUS << " - " << BuffType::DAMAGE_BONUS << "\n"
				<< "-1 to stop\n";
			cout << "Enter choice: ";
			cin >> choiceBuff;

			//! Check for buff choice. Ask again if incorrectly entered
			while (cin.fail() || choiceBuff != -1 && (choiceBuff<0 || choiceBuff>8)) {
				cout << "Incorrect Input. Please enter a correct number: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> choiceBuff;
			}

			//! If do not want to exit
			if (choiceBuff != -1) {
				int amount = 0;
				//! Ask for buff amount
				cout << "Enter buff's amount: ";
				cin.ignore();
				cin >> amount;

				while (cin.fail()) {
					cout << "Incorrect Input. Please enter a correct number: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> amount;
				}

				//! Put in vector for buff
				vecBuff.push_back(Buff((BuffType)choiceBuff, amount));
			}

		}
	}

	Item newItem; //! Item variable
	Weapon newWeapon; //! Weapon variable
	if (choiceItem == 0) { //! If item or weapon
						   //! Create and validate item
		newItem = Item((ItemType)itemType, name, vecBuff);
		if (newItem.validateItem()) {
			cout << "\nHere is the item that you want to add: \n";
			cout << newItem;
		}
		else {
			//! If not correct item. return back.
			cout << "\nIncorrect Item. Item Refused.";
			return;
		}
	}
	else {
		//! Create and validae weapon
		newWeapon = Weapon(ItemType::WEAPON, name, vecBuff, range);
		if (newWeapon.validateWeapon()) {
			cout << "\nHere is the weapon that you want to add: \n";
			cout << newWeapon;
		}
		else {
			//! If invalid weapon. do not add to backpack and return
			cout << "\nIncorrect Weapon. Weapon Refused.";
			return;
		}
	}

	//! Ask for user confirmation to add in bakcpack
	string contAns = "";
	cout << "\nDo you want to save this item? (Y/N)\nEntering N will discard all unsaved data.";
	cin >> contAns;

	//! Check input
	while (contAns != "Y" && contAns != "N") {
		cout << "\nPlease enter Y or N: ";
		cin >> contAns;
	}

	//! If wan to continue, then store in backpack
	if (contAns == "Y") {
		if (choiceItem == 0) {
			newItem.saveItem();
		}
		else {
			newWeapon.saveItem();
		}
	}

}

//! Free function that reads an item file
//! return: pointer to the newly read item
Item* readItemFile(string itemName){
	ifstream itemFile;
	itemFile.open("SaveFiles/Items/" + itemName + ".txt");
	
	Item* item = new Item();
	Weapon* weapon = new Weapon();
	string readLine;
	getline(itemFile, readLine);
	item->setItemName(readLine);
	weapon->setItemName(readLine);
	getline(itemFile, readLine);

	item->setItemType((ItemType)stoi(readLine));
	weapon->setItemType((ItemType)stoi(readLine));
	if (item->getItemTypes() == ItemType::WEAPON){

		getline(itemFile, readLine);
		weapon->setRange(stoi(readLine));

	}
	bool isBuffType = true;
	vector<Buff> tmpBuffs(0);
	BuffType tmpBuffType;
	while (!itemFile.eof()){
		if (isBuffType){
			getline(itemFile, readLine);
			if (readLine == "" || readLine == "\n"){
				break;
			}
			tmpBuffType = (BuffType)stoi(readLine);
		}
		else{
			getline(itemFile, readLine);
			if (readLine == "" || readLine == "\n"){
				break;
			}
			tmpBuffs.push_back(Buff(tmpBuffType, stoi(readLine)));
		}
		isBuffType = !isBuffType;
	}
	
	if (item->getItemTypes() == ItemType::WEAPON){
		weapon->setBuffs(tmpBuffs);
		delete item;
		return weapon;
	}
	else{
		item->setBuffs(tmpBuffs);
		delete weapon;
		return item;
	}
}