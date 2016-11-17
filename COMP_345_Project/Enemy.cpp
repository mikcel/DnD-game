//! 
//! @file 
//! @brief Implementation file for the Enemy Class.  
//! 

#include "Enemy.h"
#include "Dice.h"
#include <string>
#include <cmath>
#include "CharacterController.h"
/**
* Returns a string representation of the Enemy on the map
* @return string representing the enemy
*/
const std::string Enemy::print() const
{
	return "X";
}

/**
* Create a new instance of the Enemy class
*/
Enemy::Enemy() : CharacterElement()
{
	
}

//! Constructor with name
//! Used to facilitate map construction from a map file
Enemy::Enemy(string enName) : CharacterElement(enName)
{

}

/**
* Create a copy of this Enemy
* @return a pointer to a dynamically allocated copy of the current Enemy instance
*/
Enemy* Enemy::clone()
{
	return new Enemy(*this);
}

/**
* Obtain a random value for a character that is inside the possible
* bounds (3 to 18 inclusive) following the Dungeons&Dragons rules
* @return string representing the player
*/
int calculateRandomAttributeValue()
{
	return (abs(rand()) % 16) + 3;
}

// List of all the possible names for the enemies
const std::string enemyNames[] = {"Capitan_D.D.", "El_Mafioso", "El_Italiano", "The_Donald", "Hugh_Mungus", "Mastro_Comico", "Batman", "Ken_Bone", "Nestea","Simon"};

/**
* Obtain a random enemy name from the array of all possible enemy names
* @return string representing a name of an enemy
*/
std::string calculateRandomName()
{
	return enemyNames[abs(rand()) % 13];
}

/**
* Create a Character instance and assign it to the Character of the current Enemy
* @param level the level to which the newly created Characted should be adapted
*/
void Enemy::createCharacterWithLevel(int level, string enemyName)
{
	if (character != nullptr) {
		delete character;
	}
	character = readCharacterFile("SaveFiles/Characters/" + enemyName + ".txt", enemyName);
	//new  Character(calculateRandomName(), "1d10", calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), 1);
	character->setLevel(1);
	for (int i = 1; i < level; i++)
	{
		character->incrementLevel();
	}
}