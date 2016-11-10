//! @file 
//! @brief Implementation file for the Tile class
//!

#include "Tile.h"

using namespace std;

/**
* Initializes a tile of type FLOOR without any element
*/
Tile::Tile() : Tile(TileType::FLOOR) {};

/**
* Initializes a tile of a given type without any element
* @param newType Type of the tile
*/
Tile::Tile(TileType newType)
{
	type = newType;
	element = nullptr;
}

/**
* Validates if a tile can be traversed (if it is of type FLOOR)
* @return true if the tile is of type FLOOR
*/
bool Tile::isTraversible() const
{
	return type == TileType::FLOOR;
}

/**
* Validates if a tile is free (does not contain any element)
* @return true if the tile does not contain any element
*/
bool Tile::isFree() const
{
	return this->element == nullptr;
}

/**
* Get the tile type
* @return Tile's type
*/
TileType Tile::getType() const
{
	return type;
}

/**
* Set the tile type
* @param newType New tile type
*/
void Tile::setType(TileType newType)
{
	type = newType;
}

/**
* Get the tile's element pointer
* @return Tile element pointer
*/
Element * Tile::getElement() const
{
	return element;
}

/**
* Set the tile element
* @param newElement Pointer to the new element
*/
void Tile::setElement(Element * newElement)
{
	element = newElement;
}

/**
* Remove the pointer the element of the tile and returns it.
* @return Pointer to the removed element
*/
Element * Tile::removeElement()
{
	Element * elementReturn = element;
	element = nullptr;
	return elementReturn;
}

/**
* Prints a basic representation of a tile
* @return 'W' if the tile is a wall, the print of its element if the tile holds one, 'F' otherwise
* @note Later on, the elements will have actual classes, with element being their virtual parent class.
*		At that point, the main character and all the other types of elements will be displayed differently.
*/
string Tile::print() const
{
	//TODO: Implement each types of elements
	if (!isTraversible()) return "W";
	else if (!isFree()) return element->print();
	else return "F";
}
