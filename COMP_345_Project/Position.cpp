//! @file 
//! @brief Implementation file for the Position class
//!

#include "Position.h"

/**
* Position copy constructor
*/
Position::Position(const Position& position) : x(position.x), y(position.y)
{
}

/**
* Initializes a position at (0,0)
*/
Position::Position() : Position(0, 0) {}

/**
* Initializes a position at given coordinates
* @param newX X coordinate
* @param newY Y coordinate
*/
Position::Position(int newX, int newY) : x(newX), y(newY)
{
}

/**
* Override of the == operation. Validates that both positions have the same X and Y coordinates.
* @param p2 Position to compare
*/
const bool Position::operator==(const Position & p2)
{
	return x == p2.x && y == p2.y;
}
