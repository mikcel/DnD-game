#pragma once

#include "CharacterStrategy.h"

//! Represents a human-controlled strategy of the character
class HumanPlayerStrategy : public CharacterStrategy
{
	CharacterElement* chooseAttackTarget(Map& map, MapObserver& mo, MapElementsToggler& meo); //! Chooses an attack target for the human player
protected:
	virtual bool executeMovementTurn(Map& map, MapObserver& mo, MapElementsToggler& meo); //! Executes the movement phase of the turn
	virtual bool executeAttack(Map& map, MapObserver& mo, MapElementsToggler& meo, vector<CharacterElement*>& chrElems); //! Executes the attack phase of the turn
public:
	virtual std::string print() const; //! Obtains the map representation of the CharacterElement
	virtual std::string getStrategyName(); //! Obtains human-readble the name of the CharacterStrategy
};