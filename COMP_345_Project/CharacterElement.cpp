#include "CharacterElement.h"
#include "Character.h"
#include "AggressorStrategy.h"
#include "FriendlyStrategy.h"
#include "HumanPlayerStrategy.h"
#include "CharacterController.h"

//! Creates an new instance of the CharacterElement and sets the Character
//! @param newCharacter the Character to be set
CharacterElement::CharacterElement(Character& newCharacter, CharacterStrategy* newCharacterStrategy)
	: characterStrategy(newCharacterStrategy)
{
	if (dynamic_cast<Fighter*>(&newCharacter))
		character = new Fighter(dynamic_cast<Fighter&>(newCharacter));
	else
		character = new Character(newCharacter);
		
	characterStrategy->setCharacterElement(this);
}

CharacterElement::~CharacterElement()
{
	delete characterStrategy;
}

CharacterElement::CharacterElement(CharacterElement& newCharacterElement)
{

	if (dynamic_cast<Fighter*>(newCharacterElement.character))
		character = new Fighter(*dynamic_cast<Fighter*>(newCharacterElement.character));
	else
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
//! @return true if target not died, false otherwise
bool CharacterElement::attack(CharacterElement& target){

	bool returnVal = this->character->attack(target.getCharacter());
	cout << endl << getCharacter().getName() << " has just attacked " << target.getCharacter().getName() << endl;

	if (dynamic_cast<FriendlyStrategy*>(target.getCharacterStrategy()))
	{
		string previousStrategyName = target.getCharacterStrategy()->getStrategyName();
		delete target.getCharacterStrategy();
		target.setCharacterStrategy(new AggressorStrategy());
		cout << endl << "Former " << previousStrategyName << " \"" << target.getCharacter().getName()
			<< "\"  has now become an " << target.getCharacterStrategy()->getStrategyName() << endl;
	}
	return returnVal;

}
//! Constructor with name
//! Used to facilitate map construction from a map file
CharacterElement::CharacterElement(string chrName, CharacterStrategy* newCharacterStrategy) : characterStrategy(newCharacterStrategy)
{

	character = readCharacterFile(chrName);

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
	character = readCharacterFile(Enemy2Name);
	//new  Character(calculateRandomName(), "1d10", calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), calculateRandomAttributeValue(), 1);
	character->setLevel(level);
}

const std::string CharacterElement::print() const
{
	return characterStrategy->print();
}