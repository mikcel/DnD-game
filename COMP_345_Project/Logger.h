//! @file 
//! @brief Header file for the Logger class 
//!

//!
//! The logger class is the base class of all the loggers. 
//! It presents 2 constructors. The main role of a logger is to log the messages it receives from the different loggables it observes.
//! The messages are output in the output ostream it has.
//! In the observer pattern, the Logger is the Observer of the Loggable, which acts as the subject.
//!

#pragma once
#include <string>
#include <ostream>
#include <vector>

class Logger
{
private:
	std::ostream* output; //Stream to output the logs
public:
	Logger(); //Parameterless constructor
	Logger(std::ostream* targetOutput); //Constructor with the output stream
	virtual bool setOutputStream(std::ostream& targetOutput); //Output stream setter
	std::ostream* getOstream() const; //Output stream getter
	virtual bool log(std::string provider, std::string msg); //Virtual function to log the logs. Not purely virtual as all loggers will behave the same basic way to an update.
};

