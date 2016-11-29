#include "CharacterElement.h"
#include "Character.h"
#include "AggressorStrategy.h"
#include "FriendlyStrategy.h"
#include "HumanPlayerStrategy.h"
#include "CharacterController.h"

//! Creates an new instance of the CharacterElement and sets the Character
//! @param newCharacter the Character to be set
CharacterElement::CharacterElement(Character& newCharacter, CharacterStrategy* newCharacterStrategy)
	: character(new Character(newCharacter)), characterStrategy(newCharacterStrategy)
{
	characterStrategy->setCharacterElement(this);
}

CharacterElement::~CharacterElement()
{
	delete characterStrategy;
}

CharacterElement::CharacterElement(CharacterElement& newCharacterElement)
{
	character = new Character(*newCharacterElement.character);

	if (dynamic_cast<HumanPlayerStrategy*>(newCharacterElement.characterStrategy))
	{
		characterStrategy = new HumanPlayerStrategy();
	}
	else if (dynamic_cast<FriendlyStrategy*>(newCharacterElement.characterStrategy))
	{
		characterStrategy = new FriendlyStrategy();
	}
	else if (dynamic_cast<AggressorStrategy*>(newCharacterElement.characterStrategy))
	{
		characterStrategy = new AggressorStrategy();
	}

	characterStrategy->setCharacterElement(this);
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

////! Default contructor that doesn't set the Character
//CharacterElement::CharacterElement()
//{
//	character = nullptr;
//}

void CharacterElement::attack(CharacterElement& target){

	//return this->character->attack(target.getCharacter());
	cout << endl << getCharacter().getName() << " has just attacked " << target.getCharacter().getName() << endl;

	if (dynamic_cast<FriendlyStrategy*>(target.getCharacterStrategy()))
	{
		string previousStrategyName = target.getCharacterStrategy()->getStrategyName();
		delete target.getCharacterStrategy();
		target.setCharacterStrategy(new AggressorStrategy());
		cout << endl << "Former " << previousStrategyName << " \"" << target.getCharacter().getName()
			<< "\"  has now become an " << target.getCharacterStrategy()->getStrategyName() << endl;
	}


}
//! Constructor with name
//! Used to facilitate map construction from a map file
CharacterElement::CharacterElement(string chrName, CharacterStrategy* newCharacterStrategy) :character(new Character(chrName)), characterStrategy(newCharacterStrategy)
{
}

CharacterStrategy* CharacterElement::getCharacterStrategy()
{
	return characterStrategy;
}

void CharacterElement::setCharacterStrategy(CharacterStrategy* newCharacterStrategy)
{
	characterStrategy = newCharacterStrategy;
	characterStrategy->setCharacterElement(this);
}

/**
* Create a Character instance and assign it to the Character of the current Enemy2
* @param level the level to which the newly created Characted should be adapted
*/
void CharacterElement::createCharacterWithLevel(int level, string Enemy2Name)
{
	if (character != nullptr) {
		delete character;
	}
	character = readCharacterFile("SaveFiles/Characters/" + Enemy2Name + ".txt", Enemy2Name);
	//new  Character(calculateRandomName(), "1d10", calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), 1);
	character->setLevel(1);
	for (int i = 1; i < level; i++)
	{
		character->incrementLevel(false);
	}
}

const std::string CharacterElement::print() const
{
	return characterStrategy->print();
}