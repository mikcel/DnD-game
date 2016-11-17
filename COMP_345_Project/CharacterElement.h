#pragma once

#include "Character.h"
#include "Element.h"

//! Represents an element on the map that is a character
class CharacterElement : public Element
{
protected:
	Character* character; //! A pointer to an instance of a Character
public:
	CharacterElement(Character& newCharacter); //! Constructor that assigns the current Character of the CharacterElemnt
	CharacterElement(); // Default contructor that doesn't assign any Character
	void setCharacter(Character* newCharacter); // Setter for the current Character
	virtual CharacterElement* clone(); // Copies the current CharacterElement
	Character& getCharacter(); // Getter for the current Character
	int attack(CharacterElement& target);
};