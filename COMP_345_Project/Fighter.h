//!
//! @file 
//! @brief Header file of the Fighter class.
//!		   The Fighter Class inherits from the Character Class.
//!

//! The Fighter class is used to create Fighter players. It inherits all properties from the Character class.
//! It contains two variables : the default hit dice for any fighter and he fightint style for each fighter object.
//! The Fighter class is for defining a specific player Character. It also uses the enumerated type class for the fighting style.
//! 

#pragma once
#include "Character.h"
#include "Enums.h"
#include <fstream>
#include <string>
using namespace std;

//! Class that implements the fighter and inherits from the Character Class.
class Fighter : public Character{

public:

	//! Default constructor
	Fighter(); 

	Fighter(string chrName);

	//! A parametrized constructor getting name, an array containing the ability scores, the fighting style, the level and the size
	Fighter(string chrName, int chrAbilityScores[Character::NO_ABILITY], FightStyle chrStyle, int chrLevel, CharacterSize chrSize);
	
	//! Another parameterized constructor, passing the name, the 6 different abilities as integer, the fighting style, the level and the size to the respective
	//! data members both in the Fighter and Character class
	Fighter(string chrName, int str, int dex, int cons, int intel, int wisd, int cha, FightStyle chrStyle, int chrLevel = 1, CharacterSize chrSize = CharacterSize::TINY);
	
	Fighter(Fighter& copyFight);

	~Fighter(); //! Destructor

	FightStyle getStyle(); //! Accessor for fighting style
	FighterType getType();
	void setType(FighterType type);
	void setStyle(FightStyle chrstyle); //! Mutator for the Fighter's fighting style
	virtual bool attack(Character &chr); //! Method for attacking another player
	virtual Fighter* clone(); // Copies the current CharacterElement

	void saveCharacter();

private:

	FightStyle style = FightStyle::ARCHERY; //! Fighting style. default to archery
	FighterType type = FighterType::BULLY;

	//! Method to overload output stream operator for a Fighter
	friend ostream& operator<<(ostream& stream, const Fighter& fighter);

};