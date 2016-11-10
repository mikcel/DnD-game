//! @file ItemContainer.cpp
//! @brief Class for the item container
#pragma once
#include "ItemContainer.h"
//! Default Constructor
ItemContainer::ItemContainer()
{
	containerType = ContainerType::CHEST;
	contents = vector<Item*>(0);

}


ItemContainer::ItemContainer(ContainerType type){

	containerType = type;
	vector<Item*>vecTemp(0);
	if (type == ContainerType::WORN_ITEM)
	{
		for (int i = 0; i < 7; i++){
			vecTemp.push_back(new Item());
		}
	}
	contents = vecTemp;

}

//! Constructor that takes a type and a vector of items (will initialize worn items containers to size 7)
//! @param type: enum type of container
//! @param vectorOfItems: vector of item object pointers
ItemContainer::ItemContainer(ContainerType type, vector<Item*> vectorOfItems)
{
	vector<Item*> vecTemp(0);
	containerType = type;
	if (vectorOfItems.size() >= 1) {
		for (auto i : vectorOfItems) {
			vecTemp.push_back(new Item(*i));
		}
	}
	int wornItemSize = 7;
	if (type == ContainerType::WORN_ITEM) {
		int sizeDiff = wornItemSize - contents.size();
		for (; sizeDiff >0; sizeDiff--) {
			vecTemp.push_back(new Item());
		}
	}
	contents = vecTemp;
}

ItemContainer::ItemContainer(ItemContainer &copyCont)
{
	this->containerType = copyCont.containerType;
	vector<Item*> copyVector(0);
	for (auto i : copyCont.contents){
		if (i->getItemTypes()==ItemType::WEAPON)
			copyVector.push_back(new Weapon(*(dynamic_cast<Weapon*>(i))));
		else
			copyVector.push_back(new Item(*i));
	}
	this->contents = copyVector;
}

//! Destructor that goes through the container and deletes the pointers of the vectorOfItem
ItemContainer::~ItemContainer()
{
	for (auto i : contents) {
		delete i;
	}
}

//! method that sets the contents of the container
//! @param newContents: a vector of pointers pointing to item objects
void ItemContainer::setContents(vector<Item*> newContents) {
	contents = newContents;
}
//! method that gets the container type
//! return: the enum type of the item container
ContainerType ItemContainer::getContainerType() {
	return containerType;
}

//! method that sets the container type (if worn items is the new container type, it will make sure the vector is resized to 7 elements)
//! @param type: enum type of the item container
void ItemContainer::setContainerType(ContainerType type) {
	//resize the container if new type is worn items
	if (type == ContainerType::WORN_ITEM) {
		int wornItemSize = 7;
		int sizeDiff = wornItemSize - contents.size();
		for (; sizeDiff >0; sizeDiff--) {
			contents.push_back(new Item());
		}
	}
	containerType = type;
}

//! method that gets the content of the item container
//! @return : the vector of item pointers
vector<Item*> ItemContainer::getContents()
{
	return contents;
}

//! method that adds and item to the item container
//! @param item: pointer to an item object
void ItemContainer::addItem(Item* item)
{
	if (this->getContainerType() == ContainerType::WORN_ITEM) {
		return;
	}
	else {
		if (item->getItemTypes() == ItemType::WEAPON)
		{
			Weapon *wpn1 = (Weapon*)item;
			contents.push_back(new Weapon(*wpn1));
		}
		else
			contents.push_back(new Item(*item));
	}
}

//! method that permanently removes an item from the program
//! @param itemName: string of the name of the object
void ItemContainer::removeItem(string itemName) {

	for (vector<Item*>::size_type i = 0; i < contents.size(); i++) {
		
		if (contents[i]->getItemName().compare(itemName) == 0) {
			//if it's not a worn item container, simply delete object and remove the element from the container
			delete contents[i];
			if (containerType != ContainerType::WORN_ITEM) {
				contents.erase(contents.begin() + i);
			}
			else {
				//repopulates the newly empty worn items "slot" (maintain 7 slot structure)
				contents[i] = new Item();
			}
		}
	}
}

//! method that returns a selected item and removes it from the original container
//! @param itemName: the string of the name of the item object
//! @return: pointer to an item object
Item* ItemContainer::popItem(string itemName) {
	for (vector<Item*>::size_type i = 0; i<contents.size(); i++) {
		//search for match
		if (contents[i]->getItemName().compare(itemName) == 0) {
			//assigns a new pointer to the memory cell
			Item* returningItem = contents[i];
			//if it's not a worn item container, simply remove the element from the container
			if (containerType != ContainerType::WORN_ITEM) {
				contents.erase(contents.begin() + i);
			}
			else {
				//repopulates the newly empty worn items "slot" (maintain 7 slot structure)
				contents[i] = new Item();
			}
			return returningItem;
		 }
	}
	return NULL;
}

//!method that gets the point of an item object in a item container
//! @param itemName: string of the name of the item object
//! @return: pointer to a item object
Item* ItemContainer::getItem(string itemName) {
	
	for (vector<Item*>::size_type  i = 0; i<contents.size(); i++) {
		//searching for a match
		string name = contents[i]->getItemName();
		if ((name.compare(itemName)) == 0) {
			return contents[i];
		}
	}
	//returns an unspecified item to signify that it did not find the matching item
	return new Item();
}

//! method that equips an item form the player's backpack to the worn items container
//! @param itemName: string of the name of the item object in the backpack
//! @param playerBackpack: pointer to an item container of type backpack
//! return: boolean whether the method is succesfull
bool ItemContainer::equipItem(string itemName, ItemContainer* playerBackpack) {

	//makes sure that the container types are what is needed
	if (this->getContainerType() != ContainerType::WORN_ITEM || playerBackpack->getContainerType() != ContainerType::BACKPACK) {
		return false;
	}
	
	Item* item = playerBackpack->getItem(itemName);
	vector<Item*>::size_type  index;
	//matching the item type to the worn items contents vector
	switch (item->getItemTypes()) {
		case ItemType::HELMET:
			index = 0;
			break;
		case ItemType::ARMOR:
			index = 1;
			break;
		case ItemType::SHIELD:
			index = 2;
			break;
		case ItemType::RING:
			index = 3;
			break;
		case ItemType::BELT:
			index = 4;
			break;
		case ItemType::BOOTS:
			index = 5;
			break;
		case ItemType::WEAPON:
			index = 6;
			break;
		default:
			return false;
	}
	//switching the pointers
	//checks if the slot is already filled if so, it will transfer the item back into the backpack
	if (contents[index]->getItemTypes() != ItemType::UNSPECIFIED) {
		playerBackpack->addItem(contents[index]);
	}
	contents[index] = playerBackpack->popItem(item->getItemName());
	item = NULL;
	return true;
}
//! method that unequips an item form the player's worn items and puts it in their backpack
//! @param itemName: string of the name of the item object in the worn items
//! @param playerBackpack: pointer to an item container of type backpack
//! return: boolean whether the method is succesfull
bool ItemContainer::unequipItem(string itemName, ItemContainer* playerBackpack) {

	//makes sure that the container types are what is needed
	if (this->getContainerType() != ContainerType::WORN_ITEM || playerBackpack->getContainerType() != ContainerType::BACKPACK) {
		return false;
	}
	Item* item = getItem(itemName);
	vector<Item*>::size_type  index;
	//matching the item type to the worn items contents vector
	switch (item->getItemTypes()) {
		case ItemType::HELMET:
			index = 0;
			break;
		case ItemType::ARMOR:
			index = 1;
			break;
		case ItemType::SHIELD:
			index = 2;
			break;
		case ItemType::RING:
			index = 3;
			break;
		case ItemType::BELT:
			index = 4;
			break;
		case ItemType::BOOTS:
			index = 5;
			break;
		case ItemType::WEAPON:
			index = 6;
			break;
		default:
			return false;
	}
	//switching the pointers
	playerBackpack->addItem(this->popItem(item->getItemName()));
	item = NULL;
	return true;

}

//! Overloading output stream operator for the Item container
ostream& operator<<(ostream& stream, const ItemContainer& cont){

	if (cont.contents.size() == 0)
		return stream << "No Items";

	int countNullItem = 0;
	for (auto i : cont.contents){
		if (i->getItemTypes() == ItemType::WEAPON)
		{
			Weapon *wpn = (Weapon*)i;
			stream << *wpn <<endl;
		}
		else if(i->getItemTypes() != ItemType::UNSPECIFIED){
			stream << *i;
		}
		else{
			countNullItem++;
		}
	}

	if (countNullItem == cont.contents.size())
		stream << "No Items" << endl;

	return stream;

}

string ItemContainer::serializeItemContainer() {
	string contstr="";
	for (auto i : this->contents) {
		contstr += i->serializeItem();
	}
	return contstr;
}
