//! @file 
//! @brief Header file the AggressorStrategy class
//!

#pragma once

#include "CharacterStrategy.h"
#include "AIPLayerStrategy.h"

//! Represents an agressor strategy of the character that will advance towards 
//! the human player and attack him if he is on a reachable range 
class AggressorStrategy : public AIPLayerStrategy
{
protected:
	virtual bool executeAttack(Map& map, MapObserver& mo, MapElementsToggler& meo); //! Executes the attack phase of the turn
public:
	virtual std::string print() const; //! Obtains the map representation of the CharacterElement
	virtual std::string getStrategyName(); //! Obtains human-readble the name of the CharacterStrategy
};