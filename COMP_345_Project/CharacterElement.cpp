#include "CharacterElement.h"
#include "Character.h"

CharacterElement::CharacterElement(Character& newCharacter) : character(new Character(newCharacter))
{
	//return new CharacterElement(characterCopy);
}

CharacterElement* CharacterElement::clone()
{
	return new CharacterElement(*this);
}

Character& CharacterElement::getCharacter()
{
	return *character;
}

CharacterElement::CharacterElement()
{
	
}