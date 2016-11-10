#include "Enemy.h"
#include <string>

const std::string Enemy::print() const
{
	return "E";
}

Enemy::Enemy(Character& newCharacter) : CharacterElement(newCharacter)
{
	
}

Enemy* Enemy::clone()
{
	return new Enemy(*this);
}