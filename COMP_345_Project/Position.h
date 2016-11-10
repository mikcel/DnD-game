//! @file 
//! @brief Header file for the Position class  
//!
#pragma once

//! Represents a position with a x and y and an initialization state. A non initialized position counts as if the element didn't have a position.
class Position
{
public:
	Position(); //! Creates a new unset position at (0,0)
	Position(const Position& position); //! Position copy constructor
	Position(int newX, int newY); //! Fully parametrized constructor for a Position
	int x; //! X coordinate
	int y; //! Y coordinate
	const bool operator ==(const Position &p2); //! Override the == operator for a position
};