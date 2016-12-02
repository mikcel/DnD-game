#pragma once

#include "CharacterStrategy.h"

//! Represents a human-controlled strategy of the character
class HumanPlayerStrategy : public CharacterStrategy
{
	CharacterElement* chooseAttackTarget(Map& map, MapObserver& mo, MapElementsToggler& meo); //! Chooses an attack target for the human player
protected:
	virtual bool executeMovementTurn(Map& map, MapObserver& mo, MapElementsToggler& meo); //! Executes the movement phase of the turn
	virtual bool executeAttack(Map& map, MapObserver& mo, MapElementsToggler& meo); //! Executes the attack phase of the turn
public:
	virtual std::string print() const; //! Obtains the map representation of the CharacterElement
	virtual std::string getStrategyName(); //! Obtains human-readble the name of the CharacterStrategy
	void closestLootable(Map& map,MapElementsToggler& meo);//! lets player loot a chest or dead enemy
	void manageEquipment(Map& map, MapElementsToggler& meo); //! let the player manage their equipment.
private:
	//! Manages the equipment of the player between his worn items and his backpack
	void manageEquipmentChoiceHelper(int userChoice, CharacterElement* player, vector<Item*> worn, vector<Item*> stored, MapElementsToggler& meo);
	bool canReach(Position& characterPosition, Position& currentCharacterPosition, Map& map); //! Determines if the player can reach the enemy with his weapon
};