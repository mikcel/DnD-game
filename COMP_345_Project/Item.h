//! @file Item.h
//! @brief Header file for item class
//! using vector library to contain all of the buffs/enhancements per item
//! this follows the rules of specific items being able to have specific enhancments
#pragma once
#include <vector>
#include <string>
#include "Buff.h"
#include "Enums.h"

using namespace std;

//! class to create wearable items that the player can use.
class Item
{
public:
	//! Default constructor
	Item();
	
	//! Constructor that  takes a weapon item type and name
	//! @param itemType: enum type of the type of item
	//! @param itemName: string of the name of the item
	Item(ItemType itemType,string itemName);
	Item(Item *item);
	//! Constructor that takes a weapon item type, item name, and a vector of buff object
	//! @param itemType: enum type of the type of item
	//! @param itemName: string of the name of the item
	//! @param buffs: a vector of Buff objects that adds modifiers to the item
	Item(ItemType itemType, string itemName, vector<Buff> buffs);
	
	Item(Item &itm);

	//! Destructor, nothing to specify, no heap memory used in the constructor.
	~Item();

	//! method that gets the item type
	//! @return :itemType, a enum type of the type of item
	ItemType getItemTypes();

	//! method that gets of buffs of an item
	//! @return :buffs, a vector of Buff objects
	vector<Buff> getBuffs();

	//! method that gets the item name
	//! @return : a string holding the name of the item
	string getItemName();

	//! method that sets the item type
	//! @param itemType: enum type of the item type
	void setItemType(ItemType itemType);

	//! method that sets the buffs of an item
	//! @param buffs: vector of Buff objects
	void setBuffs(vector<Buff> &buffs);

	//! method that sets the item name
	//! @param itemName: string of the new name of the item
	void setItemName(string itemName);
	
	//! method that checks if the item is valid by check if the right buffs are allocated to the right type of item
	//! @return: boolean that indicates validity of item.
	bool validateItem();

	//! Method that converts an Item object into a string representation
	//! return: string that represents an Item Object
	virtual string serializeItem();

	//! method that takes the string representation of an Item object and saves to a text file
	virtual void saveItem();
private:
	//members of the class
	ItemType itemType;
	vector<Buff> buffs;
	string itemName;

	friend ostream& operator<<(ostream& stream, const Item& item);

};

