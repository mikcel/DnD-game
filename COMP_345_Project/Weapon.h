//! @file Weapon.h
//! @brief The header file for the Weapon class
//! This is a sub class of the items class. When a new weapon is created, it must be a weapon object
//! This is done so that weapons can have an extra member that holds the range of the weapon.
//! This range memeber is only specific to weaopn so it made sense to make it a sub class to item.
#pragma once
#include "Item.h"

//! Class, subclass of Item to instantiate weapon specific items
class Weapon : public Item
{
public:
	//! Default Contructor
	Weapon();
	
	//! Contructor that takes the weapon type,  the buffs, and the range
	//! @param itemType: enum type of the type of item
	//! @param itemName: string of the name of the item
	//! @param buffs: a vector of Buff objects that adds modifiers to the item
	//! @param range: int of the range of the weapon
	Weapon(ItemType itemType, string itemName, vector<Buff> buffs, int range);
	
	Weapon(Weapon &wpn);

	//! Destructor, nothing added
	~Weapon();
	
	//! method that gets the rang of the weapon
	//! @return: int of the range of the weapon
	int getRange();
	//! method that sets the range of the weapon
	//! @param range: int of the range of the weapon
	void setRange(int range);

	//! method that validates the weapons is of enum type weapon
	//! @return : depending on the validity of the weapon object
	bool validateWeapon(); 

	//! Method that converts an Item object into a string representation
	//! return: string that represents an Item Object
	virtual string serializeItem();

	//! method that takes the string representation of an Item object and saves to a text file
	virtual void saveItem();
private:
	int range;

	//! Operator allowing writting the contents of the weapon to a stream
	friend ostream& operator<<(ostream& stream, const Weapon& weapon);
};

