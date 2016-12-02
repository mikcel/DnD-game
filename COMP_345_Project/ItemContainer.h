//! @file ItemContainer.h
//! @brief this is the header file for ItemContainer class
//! each item container has a vector of item pointers that will point to either a pointer of an item or a pointer of a weapon
//! vector library is used to easily manipulate the contents
//! I used a vector of item pointers so that it can take both weapons (a sub class of item) and items.
//! this follows the rules of have containers that can hold items in the game
#pragma once
#include <vector>
#include "Item.h"
#include "Weapon.h"
#include "Enums.h"

//! class that will contain multiple items
class ItemContainer
{
public:
	//! Default Constructor
	ItemContainer();

	ItemContainer(ContainerType type);
	
	//! Constructor that takes a type and a vector of items  (will initialize worn items containers to size 7)
	//! @param type: enum type of container
	//! @param vectorOfItems: vector of item object pointers
	ItemContainer(ContainerType type, vector<Item*> vectorOfItems);
	
	ItemContainer(ItemContainer &copyCont);

	//! Destructor that goes through the container and deletes the pointers of the vectorOfItem
	~ItemContainer();
	
	//! method that gets the content of the item container
	//! @return : the vector of item pointers
	vector<Item*> getContents();

	//! method that gets the container type
	//! return: the enum type of the item container
	ContainerType getContainerType();

	//! method that sets the contents of the container
	//! @param newContents: a vector of pointers pointing to item objects
	void setContents(vector<Item*> newContents);

	//! method that sets the container type (if worn items is the new container type, it will make sure the vector is resized to 7 elements)
	//! @param type: enum type of the item container
	void setContainerType(ContainerType type);


	//! method that adds and item to the item container
	//! @param item: pointer to an item object
	void addItem(Item* item);

	//!method that gets the point of an item object in a item container
	//! @param itemName: string of the name of the item object
	//! @return: pointer to a item object
	Item* getItem(string itemName);

	//! method that returns a selected item and removes it from the original container
	//! @param itemName: the string of the name of the item object
	//! @return: pointer to an item object
	Item* popItem(string itemName);

	//! method that permanently removes an item from the program
	//! @param itemName: string of the name of the object
	void removeItem(string name);

	//! method that equips an item form the player's backpack to the worn items container
	//! @param itemName: string of the name of the item object in the backpack
	//! @param playerBackpack: pointer to an item container of type backpack
	//! return: boolean whether the method is succesfull
	bool equipItem(string itemName, ItemContainer* playerBackpack);

	//! method that unequips an item form the player's worn items and puts it in their backpack
	//! @param itemName: string of the name of the item object in the worn items
	//! @param playerBackpack: pointer to an item container of type backpack
	//! return: boolean whether the method is succesfull
	bool unequipItem(string itemName, ItemContainer* playerBackpack);

	//! Obtains a serialized representation of the item container
	string serializeItemContainer();
private:
	ContainerType containerType; // The type of the container
	vector<Item*> contents; // The items that are inside the container

	//! Friend declaration allowing the item info to be outputed inside a stream
	friend ostream& operator<<(ostream& stream, const ItemContainer& cont);
};

