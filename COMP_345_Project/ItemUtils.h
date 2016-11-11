#pragma once
#include "Item.h"

//! Free function to create a new item
void createItem();

//! Free Function to edit an Item File
void editItem();

//! Free function that reads an item file
//! return: pointer to the newly read item
Item* readItemFile(string itemName);

//Load all the existing items
bool loadAllExistingItems(vector<Item*>& items);