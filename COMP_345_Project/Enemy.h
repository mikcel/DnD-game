#include "Character.h"
#include "CharacterElement.h"

class Enemy : public CharacterElement
{
	virtual const std::string print() const;
public:
	Enemy::Enemy();
	void createCharacterWithLevel(int level);
	virtual Enemy* Enemy::clone();
};