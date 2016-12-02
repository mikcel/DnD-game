//! 
//! @file 
//! @brief Header file for the PlayerConsoleSingleton Class.  
//! 

#pragma once

#include "ConsoleLogger.h"
#include <sstream>

class PlayerConsoleSingleton
{
	PlayerConsoleSingleton(); //! The private contructor of the singleton
	CConsoleLoggerEx consoleLogger; //! The reference to the console
	std::stringstream* stringStream; //! A pointer to teh current instace of the string stream

	static PlayerConsoleSingleton & instance(); //! Method to obtain the instance of the singleton
public:	
	static CConsoleLoggerEx & console(); //! Obtains a reference to the second console object
	static std::stringstream & stream(); //! Obtains the reference to the current string stream
	static void printStream(); // Prints everything inside the string stream to the second console
	static void clearConsole(); // Clears the second console
};