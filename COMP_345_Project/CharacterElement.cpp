#include "CharacterElement.h"
#include "Character.h"
#include "Fighter.h"

//! Creates an new instance of the CharacterElement and sets the Character
//! @param newCharacter the Character to be set
CharacterElement::CharacterElement(Character& newCharacter)
{
	if (dynamic_cast<Fighter*>(&newCharacter))
		character = new Fighter(dynamic_cast<Fighter&>(newCharacter));
	else
		character = new Character(newCharacter);
}

//! Creates a copy of the current CharacterElement
//! @return a new dyanamically allocated instance that represents a copy of the current CharacterElement
CharacterElement* CharacterElement::clone()
{
	return new CharacterElement(*this);
}

//! Getter to obtain a reference to the current Character
//! @return reference to a Character
Character& CharacterElement::getCharacter()
{
	return *character;
}

//! Default contructor that doesn't set the Character
CharacterElement::CharacterElement()
{
	character = nullptr;
}

int CharacterElement::attack(CharacterElement& target){

	return this->character->attack(target.getCharacter());

}
//! Constructor with name
//! Used to facilitate map construction from a map file
CharacterElement::CharacterElement(string chrName) :character(new Character(chrName))
{
}