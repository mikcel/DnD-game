//! @file 
//! @brief Implementation file for the Element class
//!



#include "Element.h"
#include "Chest.h"
#include "Character.h"
Element::Element(Element& element) : position(element.position)
{
	
}

/**
* Initializes an element at position (0,0) and without having its position set
*/
Element::Element() : position(0,0)
{
}

/**
* Override of the == operation. Validates that both elements have the same position
* @param e2 Element to compare
*/
const bool Element::operator==(const Element & e2)
{
	return position == e2.position;
}

Element* Element::clone()
{
	if (dynamic_cast<Character*>(this)) {
		Character* charTemp = dynamic_cast<Character*>(this);
		return new Character(*charTemp);
		delete charTemp;
	}
	else if (dynamic_cast<Chest*>(this)) {
		Chest* chestTemp = dynamic_cast<Chest*>(this);
		return new Chest(*chestTemp);
		delete chestTemp;
	}
	else {
		return new Element(*this);
	}
	
}
