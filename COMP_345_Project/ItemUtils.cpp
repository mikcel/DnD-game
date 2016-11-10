#include "ItemUtils.h"
#include <iostream>
#include <vector>
#include <string>
#include "Item.h"
#include "ItemContainer.h"
#include "Character.h"
using namespace std;

void editItem() {
	int userChoice = -1;
	while (true) {
		cout << "Enter the index of the item you wish to edit.\nNote:The item must be in your character's backpack.\nEnter -1 to quit." << endl;
		int itemIndex = 0;
		for (auto i : backpack->getContents()) {
			cout << itemIndex << ": " << i->getItemName() << endl;
			itemIndex++;
		}
		string userChoiceStr;
		cin >> userChoiceStr;
		try {
			userChoice = stoi(userChoiceStr);
			if (userChoice == -1) {
				return;
			}
			Item* item = backpack->getContents()[userChoice];
			cout << "Selected: " << item->getItemName() << endl;
			cout << "What do you want to modify?" << endl;
			cout << "0: Item Name\n1: Buff\nEnter -1 to quit." << endl;
			cin >> userChoiceStr;
			userChoice = stoi(userChoiceStr);
			if (userChoice == 0) {
				cout << "Enter the new name of the item." << endl;
				string  newItemName;
				cin.ignore();
				getline(cin, newItemName);
				item->setItemName(newItemName);
			}
			else if (userChoice == 1) {
				//buffs
				for (auto bu : item->getBuffs()) {
					cout << "buff type " << bu.getBuffType() << endl;
					cout << "buff amount " << bu.getBuffAmount() << endl;
				}
				int choiceBuff = 0;
				int choiceAmount = 0;
				while (true) { //! Ask for buff choice
					cout << "\nChoose the buffs for this item from the list below:\nEnter -1 to stop picking buffs.\n";
					cout << (int)buff::buffTypes::INTELLIGENCE << " - " << buff::buffTypes::INTELLIGENCE << "\n"
						<< (int)buff::buffTypes::WISDOM << " - " << buff::buffTypes::WISDOM << "\n"
						<< (int)buff::buffTypes::ARMOR_CLASS << " - " << buff::buffTypes::ARMOR_CLASS << "\n"
						<< (int)buff::buffTypes::STRENGTH << " - " << buff::buffTypes::STRENGTH << "\n"
						<< (int)buff::buffTypes::CHARISMA << " - " << buff::buffTypes::CHARISMA << "\n"
						<< (int)buff::buffTypes::CONSTITUTION << " - " << buff::buffTypes::CONSTITUTION << "\n"
						<< (int)buff::buffTypes::DEXTERITY << " - " << buff::buffTypes::DEXTERITY << "\n"
						<< (int)buff::buffTypes::ATTACK_BONUS << " - " << buff::buffTypes::ATTACK_BONUS << "\n"
						<< (int)buff::buffTypes::DAMAGE_BONUS << " - " << buff::buffTypes::DAMAGE_BONUS << "\n"
						<< "-1 to stop\n" << endl;
					cout << "Enter choice: " << endl;
					cin >> choiceBuff;
					if (choiceBuff == -1) {
						break;
					}
					cout << "Enter amount: " << endl;
					cin >> choiceAmount;

					if (choiceAmount == -1) {
						break;
					}
					vector<Buff> buffs = item->getBuffs();
					bool buffExist = false;
					int buffIterator = 0;
					for (auto b : buffs) {
						if (b.getBuffType() == (buff::buffTypes)choiceBuff) {
							buffExist = true;
							cout << "FOUND BUFF" << endl;
							//b.setBuffAmount(choiceAmount);
							buffs[buffIterator].setBuffAmount(choiceAmount);
							break;
						}
						buffIterator++;
					}
					if (!buffExist) {
						buffs.push_back(Buff((buff::buffTypes)choiceBuff, choiceAmount));
					}
					cout << "SET BUFFS" << endl;
					item->setBuffs(buffs);
				}
				vector<Item*> tmpBackpack = backpack->getContents();
				tmpBackpack[userChoice] = new Item(item);
				backpack->setContents(tmpBackpack);
				//back pack is updated

				for (auto bu : item->getBuffs()) {
					cout << "buff type" << bu.getBuffType() << endl;
					cout << "buff amount" << bu.getBuffAmount() << endl;
				}

			}
			else if (userChoice == -1) {
				return;
			}
			else {
				cout << "Invalid input.\nExiting" << endl;
				return;
			}

			cout << "Edit another Item?\nEnter 0 to continue, -1 to quit." << endl;
			cin >> userChoiceStr;
			userChoice = stoi(userChoiceStr);
			if (userChoice == 0) {
				continue;
			}
			else if (userChoice == -1) {
				return;
			}
		}//end of try
		catch (...) {
			cout << "Invalid input.\nExiting" << endl;
			return;
		}


	}

}


void createItem() {
	string name = ""; //! Item name
	int itemType = item::itemTypes::UNSPECIFIED; //! item type
	int choiceItem = 0; //! Item or weapon
	int range = 0; //! Range of weapon
	vector<Buff> vecBuff(0); //! Vector for buff

							 //! Ask for weapon or item
	cout << "\nDo you want to create an Item - 0 or a Weapon - 1? ";
	cin >> choiceItem;
	//! check choice
	while (choiceItem<0 || choiceItem>1) { //!  ask to continue enter if incorrect
		cout << "\nIncorrect choice. Please choose only 0 or 1: ";
		cin >> choiceItem;
	}

	if (choiceItem == 0) { //! If item or weapon

		cout << "\nLet's create a new Item!!!";

		cout << "\nEnter the Item Name: ";
		cin.ignore();
		getline(cin, name); //! Get name

							//! output all posisible type and ask to choose
		cout << "Enter the Item type no. from the list provided below:\n";
		cout << (int)item::itemTypes::HELMET << " - " << item::itemTypes::HELMET << "\n"
			<< (int)item::itemTypes::ARMOR << " - " << item::itemTypes::ARMOR << "\n"
			<< (int)item::itemTypes::SHIELD << " - " << item::itemTypes::SHIELD << "\n"
			<< (int)item::itemTypes::RING << " - " << item::itemTypes::RING << "\n"
			<< (int)item::itemTypes::BELT << " - " << item::itemTypes::BELT << "\n"
			<< (int)item::itemTypes::BOOTS << " - " << item::itemTypes::BOOTS << "\n"
			<< (int)item::itemTypes::WEAPON << " - " << item::itemTypes::WEAPON << "\n";
		cout << "Enter choice: ";
		cin >> itemType;
		//! Continue to ask if choice is incorrectly entered
		while (itemType<0 || itemType>6) {
			cout << "\nIncorrect choice. Please enter again: ";
			cin >> itemType;
		}

		int choiceBuff = 0; //! Buff choice
		while (choiceBuff != -1) { //! While player wants to continue add buff
			cout << "\nChoose the buffs for this item from the list below: \n";
			//! Display all possible buffs
			cout << (int)buff::buffTypes::INTELLIGENCE << " - " << buff::buffTypes::INTELLIGENCE << "\n"
				<< (int)buff::buffTypes::WISDOM << " - " << buff::buffTypes::WISDOM << "\n"
				<< (int)buff::buffTypes::ARMOR_CLASS << " - " << buff::buffTypes::ARMOR_CLASS << "\n"
				<< (int)buff::buffTypes::STRENGTH << " - " << buff::buffTypes::STRENGTH << "\n"
				<< (int)buff::buffTypes::CHARISMA << " - " << buff::buffTypes::CHARISMA << "\n"
				<< (int)buff::buffTypes::CONSTITUTION << " - " << buff::buffTypes::CONSTITUTION << "\n"
				<< (int)buff::buffTypes::DEXTERITY << " - " << buff::buffTypes::DEXTERITY << "\n"
				<< (int)buff::buffTypes::ATTACK_BONUS << " - " << buff::buffTypes::ATTACK_BONUS << "\n"
				<< (int)buff::buffTypes::DAMAGE_BONUS << " - " << buff::buffTypes::DAMAGE_BONUS << "\n"
				<< "-1 to stop\n";
			cout << "Enter choice: ";
			cin >> choiceBuff; //! Enter buff choice

							   //! Check for buff choice. Ask again if incorrectly entered
			while (choiceBuff != -1 && (choiceBuff<0 || choiceBuff>8)) {
				cout << "\nIncorrect Input. Please enter a correct number: ";
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
				vecBuff.push_back(Buff((buff::buffTypes)choiceBuff, amount));
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

		int choiceBuff = 0;
		while (choiceBuff != -1) { //! Ask for buff choice
			cout << "\nChoose the buffs for this weapon from the list below: \n";
			cout << (int)buff::buffTypes::INTELLIGENCE << " - " << buff::buffTypes::INTELLIGENCE << "\n"
				<< (int)buff::buffTypes::WISDOM << " - " << buff::buffTypes::WISDOM << "\n"
				<< (int)buff::buffTypes::ARMOR_CLASS << " - " << buff::buffTypes::ARMOR_CLASS << "\n"
				<< (int)buff::buffTypes::STRENGTH << " - " << buff::buffTypes::STRENGTH << "\n"
				<< (int)buff::buffTypes::CHARISMA << " - " << buff::buffTypes::CHARISMA << "\n"
				<< (int)buff::buffTypes::CONSTITUTION << " - " << buff::buffTypes::CONSTITUTION << "\n"
				<< (int)buff::buffTypes::DEXTERITY << " - " << buff::buffTypes::DEXTERITY << "\n"
				<< (int)buff::buffTypes::ATTACK_BONUS << " - " << buff::buffTypes::ATTACK_BONUS << "\n"
				<< (int)buff::buffTypes::DAMAGE_BONUS << " - " << buff::buffTypes::DAMAGE_BONUS << "\n"
				<< "-1 to stop\n";
			cout << "Enter choice: ";
			cin >> choiceBuff;

			//! Check for buff choice. Ask again if incorrectly entered
			while (choiceBuff != -1 && (choiceBuff<0 || choiceBuff>8)) {
				cout << "\nIncorrect Input. Please enter a correct number: ";
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
				vecBuff.push_back(Buff((buff::buffTypes)choiceBuff, amount));
			}

		}
	}

	Item newItem; //! Item variable
	Weapon newWeapon; //! Weapon variable
	if (choiceItem == 0) { //! If item or weapon
						   //! Create and validate item
		newItem = Item((item::itemTypes)itemType, name, vecBuff);
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
		newWeapon = Weapon(item::itemTypes::WEAPON, name, vecBuff, range);
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
	cout << "\nDo you want to add the item to the backpack? (Y/N)\nEntering N will discard all unsaved data.";
	cin >> contAns;

	//! Check input
	while (contAns != "Y" && contAns != "N") {
		cout << "\nPlease enter Y or N: ";
		cin >> contAns;
	}

	//! If wan to continue, then store in backpack
	if (contAns == "Y") {
		if (choiceItem == 0) {
			storeItem(&newItem);
			newItem.saveItem();
		}
		else {
			storeItem(&newWeapon);
			newItem.saveItem();
		}
	}

}