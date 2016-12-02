//! @file Chest.h
//! @brief Class for Chest objects which inherits from Element and Iteam Container
//! Used to create item containers for the map.

#pragma once
#include "Element.h"
#include "ItemContainer.h"

//! Class defining the chest
class Chest:public ItemContainer,public Element
{
public:
	//! Chest Default Constructor
	Chest();
	//! Chest Copy Constructor
	//! @param &chest: address of chest object
	Chest(Chest &chest);
	//! Chest Constructor
	//! @param vectorOfItems: vector of pointers to Item objects
	Chest(vector<Item*> vectorOfItems);
	//! Destructor
	~Chest();

	//! Creates a copy of the chest with its data
	virtual Chest* Chest::clone();

	virtual const std::string print() const; //! Print the map representation of the chest
private:
	// Allowing the operator << of the ostream to acces the private data of the Chest
	friend ostream& operator<<(ostream& stream, const Chest& chst);
};

