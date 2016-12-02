//! 
//! @file 
//! @brief Implementation file for the Logger Class.  
//! 

#include "Logger.h"
#include <ostream>
#include "Time_Utils.h"

using namespace std;

/**
* Initializes a logger
*/
Logger::Logger(){};

/**
* Initializes a logger with a given output stream
* @param targetOutput Pointer to the output stream
*/
Logger::Logger(ostream* targetOutput) : output(targetOutput){};

/**
* Log a message.
* In the output stream, prints out the current time followed by the provider and the message.
* @param provider Message provider
* @param msg Message to be logged
* @return true if the log was output
*/
bool Logger::log(string provider, string msg)
{
	if (output != nullptr)
	{
		string currentTime = TimeUtils::getCurrentTime();

		*output << currentTime << "- " << provider << " : " << msg << endl;
		return true;
	}
	return false;
}

/**
* Sets the Logger output stream
* @param stream Output stream
* @return true if the output stream was correctly set
*/
bool Logger::setOutputStream(ostream& stream)
{
	if (stream.good())
	{
		output = &stream;
		return true;
	}
	return false;

}

/**
* Gets the logger output stream
* @return pointer to the output stream used by the logger
*/
std::ostream* Logger::getOstream() const
{
	return output;
}

