//! @file 
//! @brief Implementation file for the Observable class
//!

#include "Loggable.h"
#include <list>
#include <ostream>
#include "Logger.h"

using namespace std;

/**
* Attaches a logger to the loggers list if not already present
* @param o Reference to the logger to attach
*/
void Loggable::attach(Logger& l)
{
	if (find(loggers.begin(), loggers.end(), &l) == loggers.end())
	{
		loggers.push_back(&l);
	}
}

/**
* Detaches a logger from the loggers list
* @param o Reference to the logger to detach
*/
void Loggable::detach(Logger& l)
{
	loggers.remove(&l);
}

/**
* Sends a log to all the loggable's loggers
*/
void Loggable::log(string msg)
{
	for (Logger* l : loggers)
	{
		l->log(provider(), msg);
	}
}

/**
* Get a readonly list of the loggers
* @return Read-only list of the loggers
*/
const list<Logger*> & Loggable::getLoggers() const
{
	return loggers;
}