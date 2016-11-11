//! @file 
//! @brief Header file for the Element class  
//!

#pragma once
#include "Position.h"
#include "Observable.h"
#include <string>

//! Represents a generic element found in the map. This will later be used for the characters, doors, chests and other elements on a map.
class Element
{
public:
	Element(); //! Element default constructor
	Element(const Element& element); //! Element copy constructor
	virtual Element* clone(); //! Element clone function
	const bool operator ==(const Element &e2); //! Override the == operator for an Element
	virtual const std::string print() const;
	Position getPosition();
protected:
	Position position; //! Position of the element
	friend class Map;
};