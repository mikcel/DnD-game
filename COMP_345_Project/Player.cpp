#include "Player.h"
#include <string>

const std::string Player::print() const
{
	return "P";
}

Player::Player(Character& newCharacter) : CharacterElement(newCharacter)
{ 
	
}

Player* Player::clone()
{
	return new Player(*this);
}