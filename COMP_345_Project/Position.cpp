//! @file 
//! @brief Implementation file for the Position class
//!

#include "Position.h"

Position::Position(Position& position) : x(position.x), y(position.y)
{
	
}

/**
* Initializes an unset position at (0,0)
*/
Position::Position() : Position(0,0){}

/**
* Initializes a position at a given posiyion with a given isSet state
* @param newX X coordinate
* @param newY Y coordinate
* @param newIsSet true if the position is set
*/
Position::Position(int newX, int newY) : x(newX), y(newY)
{
}

/**
* Override of the == operation. Validates that both positions have the same X and Y coordinate and the same isSet state.
* @param p2 Position to compare
*/
const bool Position::operator==(const Position & p2)
{
	return x == p2.x && y == p2.y;
}
