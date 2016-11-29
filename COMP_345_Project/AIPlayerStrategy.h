//! @file 
//! @brief Header file the AIPLayerStrategy class
//!

#pragma once

#include "CharacterStrategy.h"

// A strategy class that regroups the common functionalities between the
// FriendlyStrategy and the AggressorStrategy
class AIPLayerStrategy : public CharacterStrategy
{
private:	
	bool isInDiagonalDistance(std::pair<int, int> lhs, std::pair<int, int> rhs); //! Checks if the two points are diagonal
	std::pair<int, int> calculateDiagonalIntermediateTile(std::pair<int, int> lhs, std::pair<int, int> rhs); //! Calculate the intermediate point between two diagonal points
protected:
	virtual bool executeMovementTurn(Map& map, MapObserver& mo, MapElementsToggler& meo); //! Executes the movement phase on of turn on the AIPLayerStrategy
public:
	bool performMovementStepAI(Map& map, std::list<std::pair<int, int>>& pathTowardsHumanPlayer); //! Performs a movement step towards the character
	std::list<std::pair<int, int>> calculateShortestPath(Map& map); //! Calculates the path to the character
};