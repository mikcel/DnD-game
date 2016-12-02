//! @file 
//! @brief Header file for the GameLogger class 
//!

//!
//! The GameLogger class is a child of the Logger class.
//! The GameLogger class implemented as a singleton. In this case, a single instance is neccessary. Being accessible from anywhere, it can easily be used to
//! set the different Loggable sources required.
//! It contains a pointer to the Game, the Map and the Dice it observes. This way, it is easy to detach the GameLogger from the different Loggables it observes.
//! However, it doesn't contain a pointer to the different characters it observes. As the characters are deleted from the Map once they are killed, this could have resulted in dangling pointer in this Logger.
//! With the current implementation, the GameLogger is attached to the Map current characters and detached only from them. This way, this insures that there is not dangling pointers issues and that only the valid list of characters is observed.
//! The GameLogger, contrairy to the Logger, contains a ofstream. The GameLogger is made to output the different logs to a file. Due to our output using a console, this leaves only very limited possibilities and place to output logs.
//! Also, as there is a lot of them, it is neccessary for them not to interfere too much with the flow of the gameplay. In order to achieve this, the decision to output logs in a file was taken.
//! If the GUI offered a small window to output them, it would have been a different story, but it is not the case unfortunately.
//! The GameLoggers also have a list of auto logged types. This list describes the types of loggers that as they are recorded, they want to be attached to right away.
//! This allows the player to preset a list of loggables that will be attached before each game.
//! After a game, the GameLogger can be flushed to reset its Loggables and close its output file.
//!

#pragma once
#include "Logger.h"
#include <string>
#include <ostream>
#include <list>
#include <vector>
#include "Map.h"
#include "Game.h"
#include "Dice.h"
#include "Character.h"

enum class LogType { GAME, MAP, CHARACTERS, DICE}; //Enum of the different types of Loggable the GameLogger logs

class Game;

class GameLogger: public Logger
{
private:
	static GameLogger* gl_instance; //Singleton instance
	GameLogger(); //Private constructor

	std::ofstream* file; //Pointer to the output file
	Game* _game; //Pointer to the game logged
	Map* _map; //Pointer to the map logged
	Dice* _dice; //Pointer to the dice logged
	std::list<LogType> _autoLoggedTypes; //List of the auto logged types (types of Loggables we want to attach ourself to on record.

	bool isLogging(LogType); //Determines if the specified LogType must actually be logged 

public:
	static GameLogger& instance(); //Static instance getter
	void setOutputStream(std::string targetOutputFilename); //Output stream setter
	void flush(); //Flush the Loggables
	void recordGame(Game* game); //Record a game to attach to later
	void recordMap(Map* map); //Record a map to attach to later
	void recordDice(Dice* dice); //Record a dice to attach to later
	void recordCharacters(); //Record the map characters to attach to later
	/*
	EXPLANATION
	The recordCharacters function doesn't take any parameter. If a list was manually set, and one of its characters
	was deleted from the map, then there would be inconsistency between the characters in the GameLogger and the ones on the map. At first, I thought of only
	keeping a list of strings inside the GameLogger according to the providers the GameLogger wanted to actually react to, but then it would still remain uselessly
	attached to elements it does not want to actually observe. In order to apply the Observer pattern properly, I decided to use this strategy which still insures
	that the observed characters all exist.
	*/
	bool attachLogType(LogType); //Attach the GameLogger to the given type of Loggable
	bool detachLogType(LogType); //Detach the GameLogger to the given type of Loggable
	bool addAutoAttachLogtype(LogType); //Add a LogType to the list of auto logged types
	bool removeAutoAttachLogtype(LogType); //Remove a LogType from the list of auto logged types
	
	std::string currentLogTypes(); //String output of the auto logged types
};