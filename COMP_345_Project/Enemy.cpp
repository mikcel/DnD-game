#include "Enemy.h"
#include "Dice.h"
#include <string>
#include <cmath>

const std::string Enemy::print() const
{
	return "E";
}

Enemy::Enemy() : CharacterElement()
{
	
}

Enemy* Enemy::clone()
{
	return new Enemy(*this);
}

int calculateRandomAttributeValue()
{
	return (abs(rand()) % 16) + 3;
}

const std::string names[] = {"Capitan_D.D.", "El_Mafioso", "El_Italiano", "Mikcel", "Celine", "The_Donald", "Hugh_Mungus", "Mastro_Comico", "Batman", "Ken_Bone", "Nestea","Itemsdonthavealevel","Not_Simon"};

std::string calculateRandomName()
{
	return names[abs(rand()) % 13];
}

void Enemy::createCharacterWithLevel(int level)
{
	character = new  Character(calculateRandomName(), "1d10", calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), 1);
	for (int i = 1; i < level; i++)
	{
		character->incrementLevel(Dice::roll("1d10"), false);
	}
}