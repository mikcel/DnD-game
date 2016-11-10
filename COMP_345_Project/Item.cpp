//! @file Item.cpp
//! @brief Class implementation of Item class
#pragma once
#include "Item.h"
#include "Character.h"
#include "Weapon.h"
#include <fstream>
//! Default constructor
Item::Item()
{
	itemName = "UNSPECIFIED";
	itemType = item::itemTypes::UNSPECIFIED;
	buffs = vector<Buff>(0);
}

//! Constructor that  takes a weapon item type and name
//! @param itemType: enum type of the type of item
//! @param itemName: string of the name of the item
Item::Item(item::itemTypes itemType, string itemName) {
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
Item::Item(item::itemTypes itemType,string itemName, vector<Buff> buffs) {
	this->itemType = itemType;
	this->itemName = itemName;
	this->buffs = buffs;
}

//! Destructor, nothing to specify, no heap memory used in the constructor.
Item::~Item()
{
}

//! method that gets the item type
//! @return :itemType, a enum type of the type of item
item::itemTypes Item::getItemTypes()
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
void Item::setItemType(item::itemTypes type)
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
	using namespace item;
	switch (itemType) {
		case itemTypes::HELMET:
		for (vector<Buff>::size_type i = 0; i < buffs.size(); i++)
		{
			if (buffs[i].getBuffType() != buff::buffTypes::INTELLIGENCE && buffs[i].getBuffType() != buff::buffTypes::ARMOR_CLASS && buffs[i].getBuffType() != buff::buffTypes::WISDOM)
			{
				return false;
			}
		}
		break;
		case itemTypes::ARMOR: case itemTypes::SHIELD:
		for (vector<Buff>::size_type i = 0; i < buffs.size(); i++)
		{
			if (buffs[i].getBuffType() != buff::buffTypes::ARMOR_CLASS)
			{
				return false;
			}
		}
		break;
	case itemTypes::RING:
		for (vector<Buff>::size_type i = 0; i < buffs.size(); i++)
		{
			if (buffs[i].getBuffType() != buff::buffTypes::STRENGTH && buffs[i].getBuffType() != buff::buffTypes::ARMOR_CLASS && buffs[i].getBuffType() != buff::buffTypes::WISDOM && buffs[i].getBuffType() != buff::buffTypes::CHARISMA && buffs[i].getBuffType() != buff::buffTypes::CONSTITUTION)
			{
				return false;
			}
		}
		break;
	case itemTypes::BELT:
		for (vector<Buff>::size_type i = 0; i < buffs.size(); i++)
		{
			if (buffs[i].getBuffType() != buff::buffTypes::STRENGTH && buffs[i].getBuffType() != buff::buffTypes::CONSTITUTION)
			{
				return false;
			}
		}
		break;
	case itemTypes::BOOTS:
		for (vector<Buff>::size_type i = 0; i < buffs.size(); i++)
		{
			if (buffs[i].getBuffType() != buff::buffTypes::ARMOR_CLASS && buffs[i].getBuffType() != buff::buffTypes::DEXTERITY)
			{
				return false;
			}
		}
		break;
	case itemTypes::WEAPON:
		
		for (vector<Buff>::size_type i = 0; i < buffs.size(); i++)
		{
			if (buffs[i].getBuffType() != buff::buffTypes::ATTACK_BONUS && buffs[i].getBuffType() != buff::buffTypes::DAMAGE_BONUS)
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
	itemString += to_string(itemType);
	itemString += "\n";
	for (auto b : buffs) {
		itemString += to_string(b.getBuffType());
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

	if (item.itemType != item::itemTypes::WEAPON)
		stream << endl;

	return stream;

}


void Item::saveItem() {
	ofstream outItem;
	outItem.open("saveFiles/Items/" + itemName + ".txt");
	outItem << serializeItem();
}