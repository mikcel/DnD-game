//! @file Item.cpp
//! @brief Class implementation of Item class
#pragma once
#include "Item.h"
#include "Character.h"
#include "Weapon.h"
#include "Enums.h"
#include <string>
#include <fstream>
#include <iostream>
//! Default constructor
Item::Item()
{
	itemName = "UNSPECIFIED";
	itemType = ItemType::UNSPECIFIED;
	buffs = vector<Buff>(0);
}

//! Constructor that  takes a weapon item type and name
//! @param itemType: enum type of the type of item
//! @param itemName: string of the name of the item
Item::Item(ItemType itemType, string itemName) {
	this->itemType = itemType;
	this->itemName = itemName;
	buffs = vector<Buff>(0);
}

Item::Item(Item *item) {
	this->itemType = item->itemType;
	this->itemName = item->itemName;
	buffs = item->getBuffs();
}

//! Constructor that takes a weapon item type, item name, and a vector of buff object
//! @param itemType: enum type of the type of item
//! @param itemName: string of the name of the item
//! @param buffs: a vector of Buff objects that adds modifiers to the item
Item::Item(ItemType itemType,string itemName, vector<Buff> buffs) {
	this->itemType = itemType;
	this->itemName = itemName;
	this->buffs = buffs;
}

Item::Item(Item &itm){
	this->itemName = itm.itemName;
	this->itemType = itm.itemType;
	vector<Buff> copyVec(0);
	for (auto i : itm.buffs){
		copyVec.push_back(i);
	}
	this->buffs = copyVec;
}

//! Destructor, nothing to specify, no heap memory used in the constructor.
Item::~Item()
{
}

//! method that gets the item type
//! @return :itemType, a enum type of the type of item
ItemType Item::getItemTypes()
{
	return itemType;
}
//! method that gets of buffs of an item
//! @return :buffs, a vector of Buff objects
vector<Buff> Item::getBuffs() 
{
	return buffs;
}
//! method that gets the item name
//! @return : a string holding the name of the item
string Item::getItemName()
{
	return itemName;
}

//! method that sets the item name
//! @param itemName: string of the new name of the item
void Item::setItemName(string itemName)
{
	this->itemName = itemName;
}
//! method that sets the item type
//! @param itemType: enum type of the item type
void Item::setItemType(ItemType type)
{
	itemType = type;
}

//! method that sets the buffs of an item
//! @param buffs: vector of Buff objects
void Item::setBuffs(vector<Buff> &buffs)
{
	this->buffs = buffs	;
}
//! method that checks if the item is valid by check if the right buffs are allocated to the right type of item
//! @return: boolean that indicates validity of item.
bool Item::validateItem()
{	
	switch (itemType) {
	case ItemType::HELMET:
		for (vector<Buff>::size_type i = 0; i < buffs.size(); i++)
		{
			if (buffs[i].getBuffType() != BuffType::INTELLIGENCE && buffs[i].getBuffType() != BuffType::ARMOR_CLASS && buffs[i].getBuffType() != BuffType::WISDOM)
			{
				return false;
			}
		}
		break;
	case ItemType::ARMOR: case ItemType::SHIELD:
		for (vector<Buff>::size_type i = 0; i < buffs.size(); i++)
		{
			if (buffs[i].getBuffType() != BuffType::ARMOR_CLASS)
			{
				return false;
			}
		}
		break;
	case ItemType::RING:
		for (vector<Buff>::size_type i = 0; i < buffs.size(); i++)
		{
			if (buffs[i].getBuffType() != BuffType::STRENGTH && buffs[i].getBuffType() != BuffType::ARMOR_CLASS && buffs[i].getBuffType() != BuffType::WISDOM && buffs[i].getBuffType() != BuffType::CHARISMA && buffs[i].getBuffType() != BuffType::CONSTITUTION)
			{
				return false;
			}
		}
		break;
	case ItemType::BELT:
		for (vector<Buff>::size_type i = 0; i < buffs.size(); i++)
		{
			if (buffs[i].getBuffType() != BuffType::STRENGTH && buffs[i].getBuffType() != BuffType::CONSTITUTION)
			{
				return false;
			}
		}
		break;
	case ItemType::BOOTS:
		for (vector<Buff>::size_type i = 0; i < buffs.size(); i++)
		{
			if (buffs[i].getBuffType() != BuffType::ARMOR_CLASS && buffs[i].getBuffType() != BuffType::DEXTERITY)
			{
				return false;
			}
		}
		break;
	case ItemType::WEAPON:
		
		for (vector<Buff>::size_type i = 0; i < buffs.size(); i++)
		{
			if (buffs[i].getBuffType() != BuffType::ATTACK_BONUS && buffs[i].getBuffType() != BuffType::DAMAGE_BONUS)
			{
				return false;
			}
		}
		break;
	default:
		return false;
	}
	return true;
}
string Item::serializeItem() {
	string itemString = "";
	itemString += itemName;
	itemString += "\n";
	itemString += to_string((int)itemType);
	itemString += "\n";
	for (auto b : buffs) {
		itemString += to_string((int)b.getBuffType());
		itemString += "\n";
		itemString += to_string(b.getBuffAmount());
		itemString += "\n";
	}
	return itemString;
 }

ostream& operator<<(ostream& stream, const Item& item){

	string buffString = "";

	if (buffString == "")
		buffString = "No Buffs\n";

	stream << "Item's Name: " << item.itemName <<
		"\nItem's Type: " << item.itemType <<
		"\nBuffs: \n";

	for (auto i : item.buffs){
		stream << "Buff: + " << i.getBuffAmount() << " of type: " << i.getBuffType() << "\n";
	}

	if (item.itemType != ItemType::WEAPON)
		stream << endl;

	return stream;

}


//! Method to add item to backpack
//! @param Character to add item to its backpack
static void createItem(Character &chr) {

	string name = ""; //! Item name
	int itemType = (int)ItemType::UNSPECIFIED; //! item type
	int choiceItem = 0; //! Item or weapon
	int range = 0; //! Range of weapon
	vector<Buff> vecBuff(0); //! Vector for buff

	//! Ask for weapon or item
	cout << "\nDo you want to create an Item - 0 or a Weapon - 1? ";
	cin >> choiceItem;
	//! check choice
	while (choiceItem < 0 || choiceItem>1) { //!  ask to continue enter if incorrect
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
		while (itemType < 0 || itemType>6) {
			cout << "\nIncorrect choice. Please enter again: ";
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
			while (choiceBuff != -1 && (choiceBuff < 0 || choiceBuff>8)) {
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
			while (choiceBuff != -1 && (choiceBuff < 0 || choiceBuff>8)) {
				cout << "\nIncorrect Input. Please enter a correct number: ";
				cin >> choiceBuff;
			}

			//! If do not want to exit
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
	cout << "\nDo you want to add the item to the backpack? (Y/N) ";
	cin >> contAns;

	//! Check input
	while (contAns != "Y" && contAns != "N") {
		cout << "\nPlease enter Y or N: ";
		cin >> contAns;
	}

	//! If wan to continue, then store in backpack
	if (contAns == "Y") {
		if (choiceItem == 0)
			chr.storeItem(&newItem);
		else
			chr.storeItem(&newWeapon);
	}
}

void Item::saveItem(){
	ofstream outItem;
	outItem.open("saveFiles/Items/" + itemName + ".txt");
	outItem << serializeItem();
	outItem.close();
	cout << "Item was saved!" << endl;
}