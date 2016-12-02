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

//! Method that converts an Item object into a string representation
//! return: string that represents an Item Object
string Item::serializeItem () {
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

//! Returns a string output tht contains all the information about 
//! the item to the stream
//! @param stream the stream to which the string should be written
//! @param the item which information will be outputed
//! @return the stream to which the item inforamtion is written
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

//! method that takes the string representation of an Item object and saves to a text file
void Item::saveItem(){
	ofstream outItem;
	if (validateItem()){
		outItem.open("saveFiles/Items/" + itemName + ".txt");
		outItem << serializeItem();
		outItem.close();
		cout << "Item was saved!" << endl;
	}
	else{
		cout << "This item is not valid, changes will be discarded." << endl;
	}
}