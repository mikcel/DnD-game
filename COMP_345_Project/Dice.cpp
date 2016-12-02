//! @file 
//! @brief Implementation file for the Dice class  
//!
#include <ctime>
#include <stdexcept>
#include <regex>
#include <string>
#include "dice.h"

using namespace std;

Dice* Dice::dice_instance = 0;

// Regex to test the validity of the string
const std::regex Dice::dice_regex("^([1-9][0-9]*)d(4|6|8|10|12|20|100)(\\+(0|([1-9][0-9]*)+))?$");

// Variable to remember if the seed for the random generation is already set

Dice::Dice() : is_already_initialized(false){};

/*
*	Initializes an instance of the Dice if it isn't already and returns it.
*	@return Reference to the singleton dice.
*/
Dice& Dice::instance()
{
	if (dice_instance == nullptr)
	{
		dice_instance = new Dice();
	}
	return *dice_instance;
}


//! Implementation of the rolling dice
//! @param string : a string of the form "xdy[+z]".
//! @return an integer which is the addition of the value of all dice and return -1 when the expression does not follow he right format 
int Dice::roll(string expression)
{
	// Set the seed for the random generation to the current time in seconds
	// Is executed only the first time that the roll() method is called
	// Allows to have a different result each time that the program is run
	if (!is_already_initialized)
	{
		is_already_initialized = true;
		srand(time(0));
	}

	// Check if the string parameter is of the correct format
	if (!std::regex_match(expression, Dice::dice_regex))
	{
		return -1;
	}

	// Find the index of the char containing 'd'
	auto d_index_iterator = find(expression.begin(), expression.end(), 'd');
	std::string number_of_dice_string(expression.begin(), d_index_iterator);
	int number_of_dice = atoi(number_of_dice_string.c_str());

	// Find if the string contains an addition bonus by checking if it contains '+'
	auto add_iterator = find(expression.begin(), expression.end(), '+');
	bool contains_add = add_iterator != expression.end();

	// Obtain the dice type
	std::string dice_type_string(d_index_iterator + 1, contains_add ? add_iterator : expression.end());
	int dice_type = atoi(dice_type_string.c_str());

	// Obtain the the addition bonus value
	int additional_add = 0;
	if (contains_add)
	{
		std::string additional_add_string(add_iterator + 1, expression.end());
		additional_add = atoi(additional_add_string.c_str());
	}

	// Calculating the total by tossing the y dice x number of times
	int total = 0;
	for (size_t i = 0; i < number_of_dice; i++)
	{
		int current_random = abs(rand()); // Obtain a positive random variable
		int dice_toss = (current_random % dice_type) + 1;
		log("Dice tossed. Value: " + to_string(dice_toss));
		total += dice_toss;// Calculate the result of the current toss and add it to the total
	}

	// Add the bonus (z) to the total
	total += additional_add;

	log("All dices tossed. Total: " + to_string(total));

	return total;
}

//!Return the provider string "Dice"
string Dice::provider()
{
	return "Dice";
}