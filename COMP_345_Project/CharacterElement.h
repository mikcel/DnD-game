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
	//! Constructor with name
	//! Used to facilitate map construction from a map file
	CharacterElement(string chrName);
	void setCharacter(Character* newCharacter); // Setter for the current Character
	virtual CharacterElement* clone(); // Copies the current CharacterElement
	Character& getCharacter(); // Getter for the current Character
};