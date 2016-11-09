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

//! Class that implements the fighter and inherits from the Character Class.
class Fighter : public Character{

public:

	//! Default constructor
	Fighter(); 

	//! A parametrized constructor getting name, an array containing the ability scores, the fighting style, the level and the size
	Fighter(string chrName, int chrAbilityScores[Character::NO_ABILITY], fight::Style chrStyle, int chrLevel, chr::Size chrSize); 
	
	//! Another parameterized constructor, passing the name, the 6 different abilities as integer, the fighting style, the level and the size to the respective
	//! data members both in the Fighter and Character class
	Fighter(string chrName, int str, int dex, int cons, int intel, int wisd, int cha, fight::Style chrStyle, int chrLevel = 1, chr::Size chrSize = chr::Size::TINY);
	
	~Fighter(); //! Destructor

	fight::Style getStyle(); //! Accessor for fighting style
	void setStyle(fight::Style chrstyle); //! Mutator for the Fighter's fighting style
	void incrementLevel(int hitRoll); //! Fghter's overridden method from Chracter class to increment level
	int attack(Character &chr, int dmg); //! Method for attacking another player

private:

	static const string DEFAULT_HIT_DICE; //! Default hit dice for a Fighter
	fight::Style style = fight::ARCHERY; //! Fighting style. default to archery

	//! Method to overload output stream operator for a Fighter
	friend ostream& operator<<(ostream& stream, const Fighter& fighter);

};