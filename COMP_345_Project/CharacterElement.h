#pragma once

#include "Character.h"
#include "Element.h"
#include "CharacterStrategy.h"

class CharacterStrategy;

//! Represents an element on the map that is a character
class CharacterElement : public Element
{
	CharacterStrategy* characterStrategy;
protected:
	Character* character; //! A pointer to an instance of a Character
public:
	CharacterElement(Character& newCharacter, CharacterStrategy* newCharacterStrategy); //! Constructor that assigns the current Character of the CharacterElemnt
	//CharacterElement(); // Default contructor that doesn't assign any Character
	~CharacterElement();
	//! Constructor with name
	//! Used to facilitate map construction from a map file
	CharacterElement(string chrName, CharacterStrategy* newCharacterStrategy);
	CharacterElement(CharacterElement& newCharacterElement);
	void setCharacter(Character* newCharacter); // Setter for the current Character
	virtual CharacterElement* clone(); // Copies the current CharacterElement
	Character& getCharacter(); // Getter for the current Character
	bool attack(CharacterElement& target);
	CharacterStrategy* getCharacterStrategy();
	void setCharacterStrategy(CharacterStrategy* newCharacterStrategy);
	void createCharacterWithLevel(int level, string Enemy2Name);
	virtual const std::string print() const;
};