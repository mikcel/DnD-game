//! @file 
//! @brief Header file for the Loggable class 
//!

//!
//! The loggable class is the base class of all the loggable. It is an abstract class. 
//! A loggable class is a class that can send logs. Loggers can be attached to it and when a log will be sent, the loggers will log it.
//! The pure virtual function provider has to be redefined in the classes that inherit from Loggable as when a log is sent, it has to include its provider, being the actual class sending the log.
//! In the observer pattern, the Loggable class is the Subject of the Loggers, which act as Observers.
//!

#pragma once
#include "Logger.h"
#include <list>
#include <string>

//! Abstract representation of an observable object (also called subject)
class Loggable {
public:
	void attach(Logger&); //! Adds a logger to the loggers list
	void detach(Logger&); //! Removes a logger from the loggers list
	void log(std::string msg); //! Sends a log
	virtual std::string provider() = 0; //! Provides a string describing the provider class of the log
	const std::list<Logger*> & getLoggers() const; //! Returns a readonly list of the loggers
private:
	std::list<Logger*> loggers; //! List of loggers
};