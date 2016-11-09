//! @file 
//! @brief Header file for the Tile class
//!

#pragma once
#include "Element.h"
#include <string>

//! Represents the tile enums
namespace TileEnums {
	enum Type { FLOOR, WALL }; //! Type of tile
}

//! Represents a tile on a map. A tile has a type (currently a floor or a wall), and can hold an element.
//! The element is only a pointer to the actual element held in the Map elements list.
//! The destruction manageent is all made in the map.
using namespace TileEnums;
using namespace std;
class Tile
{
public:
	Tile(); //! Default constructor of a tile
	Tile(Type newType); //! Constructor of a tile with a type
	bool isTraversible(); //! Returns true if the tile has a type that can be traversed
	bool isFree(); //! Returns true if the tile doesn't hold any element
	Type getType(); //! Returns the type of the tile
	void setType(Type newType); //! Sets the type of the tile to the given type
	Element * getElement(); //! Returns a pointer to the element the tile holds
	void setElement(Element * newElement); //! Sets the element that the tile holds
	Element * removeElement(); //! Unlink the element from this tile
	string print(); //! Prints a basic version of the tile
private:
	Type type; //! Type of the tile
	Element * element; //! Pointer to the element held by the tile. This is a pointer as the storage of the elements is managed by the map.
};
