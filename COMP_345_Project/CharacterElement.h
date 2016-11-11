#pragma once

#include "Character.h"
#include "Element.h"

class CharacterElement : public Element
{
	Character& character;
public:
	CharacterElement(Character& newCharacter);
	virtual CharacterElement* clone();
	Character& getCharacter();
};