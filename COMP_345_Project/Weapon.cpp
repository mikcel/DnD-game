//! @file Weapon.cpp
//! @brief Class that instantiate weapon specific items

#pragma once
#include "Weapon.h"
#include "Item.h"

//! Default Contructor
Weapon::Weapon():Item()
{	
	range = 1;
}

//! Contructor that takes the weapon type,  the buffs, and the range
//! @param itemType: enum type of the type of item
//! @param itemName: string of the name of the item
//! @param buffs: a vector of Buff objects that adds modifiers to the item
//! @param range: int of the range of the weapon
Weapon::Weapon(ItemType itemType, string itemName, vector<Buff> buffs, int range):Item( itemType, itemName, buffs)
{
	if (range < 1) {
		range = 1;
	}
	this->range = range;
}

Weapon::Weapon(Weapon &wpn):Item(wpn.getItemTypes(),wpn.getItemName(),wpn.getBuffs()){
	this->range = wpn.range;
}

//! Destructor, nothing added
Weapon::~Weapon()
{

}
//! method that gets the rang of the weapon
//! @return: int of the range of the weapon
int Weapon::getRange() {
	return range;
}
//!method that sets the range of the weapon
//! @param range: int of the range of the weapon
void Weapon::setRange(int range) {
	this->range = range;
}

//! method that validates the weapons is of enum type weapon
//! @return : depending on the validity of the weapon object
bool Weapon::validateWeapon() 
{
	if (this->getItemTypes() == ItemType::WEAPON) 
	{
		return true;
	}
	return false;
}

string Weapon::serializeItem() {
	string itemString = "";
	itemString += this->getItemName();
	itemString += "\n";
	itemString += to_string((int)(this->getItemTypes()));
	itemString += "\n";
	itemString += to_string(this->range);
	itemString += "\n";

	BuffType a = (BuffType)1;
	//int b = (int)a;

	for (auto b : this->getBuffs()) {
		itemString += to_string((int)b.getBuffType());
		itemString += "\n";
		itemString += to_string(b.getBuffAmount());
		itemString += "\n";
	}
	return itemString;
}

ostream& operator<<(ostream& stream, const Weapon& wpn){
	const Item &itm = wpn;
	return stream << itm << "\nRange: " << wpn.range << endl;
}