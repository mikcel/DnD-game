#pragma once
#include "Character.h"
#include "CharacterElement.h"

class Player : public CharacterElement
{
	virtual const std::string print() const;
public:
	Player::Player(Character& newCharacter);
	virtual Player* Player::clone();
	friend class Map;
};