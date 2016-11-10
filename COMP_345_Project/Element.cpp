//! @file 
//! @brief Implementation file for the Element class
//!

#include "Element.h"

using namespace std;

/**
* Element copy constructor
* @param element Element to copy
*/
Element::Element(const Element& element) : position(element.position)
{
}

/**
* Initializes an element at position (0,0)
*/
Element::Element() : position(0, 0)
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

/**
* Clone an element
*/
Element* Element::clone()
{
	return new Element(*this);
}

/**
* Prints a basic representation of an element
* @return a string of the character '\xFe'
*/
const string Element::print() const
{
	return "E";
}

Position Element::getPosition()
{
	return position;
}