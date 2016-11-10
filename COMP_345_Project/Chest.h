//! @file Chest.h
//! @brief Class for Chest objects which inherits from Element and Iteam Container
//! Used to create item containers for the map.

#pragma once
#include "Element.h"
#include "ItemContainer.h"
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

	virtual Chest* Chest::clone();
};

