//! 
//! @file 
//! @brief Header file for the Enemy Class.  
//! 

#include "Character.h"
#include "CharacterElement.h"

//! Class that represents an enemy that is situated on the map
class Enemy : public CharacterElement
{
	virtual const std::string print() const; //! Print the map representation of the enemy
public:
	Enemy::Enemy(); //! Constructor to create a new Enemy instance without a Character object
	
	//! Constructor with name
	//! Used to facilitate map construction from a map file
	Enemy::Enemy(string enName);
	void createCharacterWithLevel(int level, string enemyName); // Add a new Character object with randomly generated abilities to the enemy
	virtual Enemy* Enemy::clone(); //! Create a copy of the current Enemy instance
};