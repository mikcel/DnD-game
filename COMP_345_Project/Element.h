//! @file 
//! @brief Header file for the Element class  
//!

#pragma once
#include "Position.h"

//! Represents a generic element found in the map. This will later be used for the characters, doors, chests and other elements on a map.
class Element
{
public :
	Element();
	Element(Element& element);
	virtual Element* clone();
	const bool operator ==(const Element &e2); //! Override the == operator for an Element
private:
	Position position; //! Position of the element
	friend class Map;
};