//! @file 
//! @brief Header file for the Dice class  
//!
#pragma once

#include <string>
#include <regex>
#include "Loggable.h"

//! class that implements the rolling of Dice 
//! This class allows to roll dice following the D20 system and follows the xdy[+z] notation.
//! 
//! The dice rolling method accepts a string that specifies what type of dice should be rolled, 
//! how many times should this dice be rolled and the optional bonus that should be applied.
//! The roll() method first checks if the string passed as a parameter matches the regex of a
//! proper dice command string. If it does not, then the value -1 is returned immideatly. In 
//! the other case, the method tries to read the numbers inside the string (x, y and z) knowing
//! that they are separated with the 'd' and '+' characters. After determining all these values,
//! a loop is executed to randomly generated the results of multiple dice rolls. At the end, the
//! bonus z is added to the final result. Also, at the first execution of the method, the seed
//! of the random generation is set to the current number of seconds (time(0)). This allows to 
//! have different results each time the program is run.
//! 
//! The method uses the STL library to find the indexes of some elements inside the string and
//! to convert strings to integers. The reason why I used a library is because it allowed me to
//! reduce the size of my code. The reason why I used STL specifically is because it is the 
//! most known and widely used C++ library.
//!
//! Extends loggable to log every dice toss.

class Dice : public Loggable
{
private:
	static Dice* dice_instance; //Singleton instance of the Dice
	Dice(); //Private contructor
	static const std::regex dice_regex;
	bool is_already_initialized; // Variable to remember if the seed for the random generation is already set
public:
	static Dice& instance(); //Initializes the instance of the dice if it does not exists and returns it
	int roll(std::string expression);
	virtual std::string provider(); //Loggable provider
};