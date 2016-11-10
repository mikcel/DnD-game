#include "Character.h"
#include "CharacterElement.h"

class Enemy : public CharacterElement
{
	virtual const std::string print() const;
public:
	Enemy::Enemy(Character& newCharacter);
};