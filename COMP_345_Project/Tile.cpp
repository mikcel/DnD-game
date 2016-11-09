//! @file 
//! @brief Implementation file for the Tile class
//!

#include "Tile.h"
#include <typeinfo>
#include "Character.h"
#include "Chest.h"
/**
* Initializes a tile of type FLOOR without any element
*/
Tile::Tile() : Tile(Type::FLOOR){};

/**
* Initializes a tile of a given type without any element
* @param newType Type of the tile
*/
Tile::Tile(Type newType)
{
	type = newType;
	element = nullptr;
}

/**
* Validates if a tile can be traversed (if it is of type FLOOR)
* @return true if the tile is of type FLOOR
*/
bool Tile::isTraversible()
{
	return type == Type::FLOOR;
}

/**
* Validates if a tile is free (does not contain any element)
* @return true if the tile does not contain any element
*/
bool Tile::isFree()
{
	return this->element == nullptr;
}

/**
* Get the tile type
* @return Tile's type
*/
Type Tile::getType()
{
	return type;
}

/**
* Set the tile type
* @param newType New tile type
*/
void Tile::setType(Type newType)
{
	type = newType;
}

/**
* Get the tile's element pointer
* @return Tile element pointer
*/
Element * Tile::getElement() 
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
* @return 'W' if the tile is a wall, 'E' if the tile holds an element, 'F' otherwise
*/
string Tile::print()
{
	if (!isTraversible()) return "W";
	else if (!isFree()) {
		if (dynamic_cast<Character*>(element)) {
			return "X";
		}
		else if (dynamic_cast<Chest*>(element)) {
			return "C";
		}
	}
	else return "F";
}
