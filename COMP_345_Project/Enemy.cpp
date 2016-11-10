#include "Enemy.h"
#include <string>

const std::string Enemy::print() const
{
	return "E";
}

Enemy::Enemy(Character& newCharacter) : CharacterElement(newCharacter)
{
	
}