//! 
//! @file 
//! @brief File containing two namespaces defining enums used in this solution.
//!		   Mainly used by the Character and Fighter classes.
//!

//!
//! The namespace contained in this file is mainly for the Character & Fighter classes use so that their data members
//!	can hold constant data values. The enumerated type used are for Character Size, Abilites and Fighter Style.
//! These enumerated types were designed to restrict data for class data members and for better coding, for e.g comparisons and readability.
//! Defining these enumerated types in namespaces allows the use of hem outside of the respective classes' scope
//! Two namespaces were coded to differentiate between Character and Fighter enum types.
//! Moreover, two functions are defined for the output of each enumerated type to the console. (output operator overridden)
//!

#pragma once //Define only once when used

#include <iostream>
using namespace std;

//! Namespace containing 2 enumerated types for defining Characters data members. (size and for indexing the 2 abilities arrays)
namespace chr{

	//! An enumerated type for the size of the Character. 
	//! Only 4 sizes are available and size modifier is calculated based on the size.
	enum Size { FINE, TINY, HUGE, COLOSSAL }; 

	//! Use of an enum type for indexing array of abilities scores and abilities modifiers for better comprehension 
	//! of the position of the abilities in the array (e.g. getting a modifier of a specific ability). Numbers are assign to
	//! each enum element for array indexing
	enum Abilities { STR = 0, DEX = 1, CONS = 2, INTEL = 3, WISD = 4, CHA = 5 }; 

}

//! Namespace for Fighter style enumerated type.
namespace fight{

	//!An enumerated type for the Fighter's Style that will help in determining Fighter's stats.
	enum Style{ ARCHERY, DEFENSE, DUELING };

}

namespace item{

	//! enum type used to identify item types
	enum itemTypes { HELMET = 0, ARMOR = 1, SHIELD = 2, RING = 3, BELT = 4, BOOTS = 5, WEAPON = 6, UNSPECIFIED = 7 };

}

namespace itemCnt{

	//! enum types for the type of containers
	enum containerTypes { WORN_ITEM, BACKPACK, CHEST };

}

namespace buff{

	//! enum type to indicate the type of buff
	enum buffTypes { INTELLIGENCE, WISDOM, ARMOR_CLASS, STRENGTH, CHARISMA, CONSTITUTION, DEXTERITY, ATTACK_BONUS, DAMAGE_BONUS };

}

//! Overloading output stream operator for outputting Size
ostream& operator<<(ostream& stream, chr::Size size);

//! Overloading the output stream operator to have a specific output for each Character object
ostream& operator<<(ostream& stream, chr::Abilities ability);

ostream& operator<<(ostream& stream, fight::Style style);

ostream& operator<<(ostream& stream, item::itemTypes type);

ostream& operator<<(ostream& stream, buff::buffTypes buffType);
