#pragma once

#include "Character.h"
#include "Element.h"

class CharacterElement : public Element
{
protected:
	Character* character;
public:
	CharacterElement(Character& newCharacter);
	CharacterElement();
	void setCharacter(Character* newCharacter);
	virtual CharacterElement* clone();
	Character& getCharacter();
};