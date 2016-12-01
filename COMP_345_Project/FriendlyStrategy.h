#pragma once

#include "AIPlayerStrategy.h"

class AIPLayerStrategy;

//! Represents aa friendly strategy of the character that will advance towards 
//! the human player but will not attack him
class FriendlyStrategy : public AIPLayerStrategy
{
protected:
	virtual bool executeAttack(Map& map, MapObserver& mo, MapElementsToggler& meo, vector<CharacterElement*>& chrElems); //! Executes the attack of the friendly character
public:
	virtual std::string print() const; //! Obtains the map representation of the CharacterElement
	virtual std::string getStrategyName(); //! Obtains human-readble the name of the CharacterStrategy
};