//! @file 
//! @brief Implementation file for the GameLogger class 
//!

#include "GameLogger.h"
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <Windows.h>

using namespace std;

GameLogger* GameLogger::gl_instance = 0;


/**
* Initializes a GameLogger
*/
GameLogger::GameLogger()
{
	_game = nullptr;
	_map = nullptr;
	_dice = nullptr;
	file = nullptr;

	_autoLoggedTypes.push_back(LogType::GAME);
	_autoLoggedTypes.push_back(LogType::MAP);
	_autoLoggedTypes.push_back(LogType::CHARACTERS);
	_autoLoggedTypes.push_back(LogType::DICE);

	CreateDirectory("Log", NULL);
}

/**
* Get the singleton instance of the GameLogger. Initializes it if it isn't already.
* @return Reference to the singleton GameLogger
*/
GameLogger& GameLogger::instance()
{
	if (gl_instance == nullptr)
	{
		gl_instance = new GameLogger();
	}
	return *gl_instance;
}

/**
* Flushes all the Loggables and closes the file
*/
void GameLogger::flush()
{
	_game = nullptr;
	_map = nullptr;
	_dice = nullptr;

	if (file != nullptr)
	{
		file->close();
		delete file;
		file = nullptr;
	}
}

/**
* Record the game and attach the Logger to it if Game is part of the autologged types
* @param game Pointer to the game to record
*/
void GameLogger::recordGame(Game* game)
{
	_game = game;
	if (find(_autoLoggedTypes.begin(), _autoLoggedTypes.end(), LogType::GAME) != _autoLoggedTypes.end())
	{
		attachLogType(LogType::GAME);
	}
}

/**
* Record the map and attach the Logger to it if Map is part of the autologged types
* @param map Pointer to the map to record
*/
void GameLogger::recordMap(Map* map)
{
	_map = map;
	if (find(_autoLoggedTypes.begin(), _autoLoggedTypes.end(), LogType::MAP) != _autoLoggedTypes.end())
	{
		attachLogType(LogType::MAP);
	}
}

/**
* Record the dice and attach the Logger to it if Dice is part of the autologged types
* @param dice Pointer to the dice to record
*/
void GameLogger::recordDice(Dice* dice)
{
	_dice = dice;
	if (find(_autoLoggedTypes.begin(), _autoLoggedTypes.end(), LogType::DICE) != _autoLoggedTypes.end())
	{
		attachLogType(LogType::DICE);
	}
}

/**
* Attaches to the characters fo the map if Characters is part of the autogged types
*/
void GameLogger::recordCharacters()
{
	if (find(_autoLoggedTypes.begin(), _autoLoggedTypes.end(), LogType::CHARACTERS) != _autoLoggedTypes.end())
	{
		attachLogType(LogType::CHARACTERS);
	}
}

/**
* Attaches the GameLogger to the given LogType is it has been recorded.
* Logs if the GameLogger was succesfully attached
* @param lt Logtype to attach the GameLogger to
* @return true if the GameLogger was attached to a Loggable
*/
bool GameLogger::attachLogType(LogType lt)
{
	bool hasBeenAttached = false;
	switch (lt)
	{
	case LogType::GAME:
		if (_game != nullptr)
		{
			_game->attach(*this);
			log("Game", "Start logging.");
			hasBeenAttached = true;
		}
		break;
	case LogType::MAP:
		if (_map != nullptr)
		{
			_map->Loggable::attach(*this);
			log("Map", "Start logging.");
			hasBeenAttached = true;
		}
		break;
	case LogType::CHARACTERS:
		if (_map != nullptr)
		{
			for (Element* che : _map->getElements())
			{
				CharacterElement* ce = dynamic_cast<CharacterElement*>(che);
				if (ce != nullptr)
				{
					ce->getCharacter().attach(*this);
				}
			}
			log("Character", "Start logging.");
			hasBeenAttached = true;
		}
		break;
	case LogType::DICE:
		if (_dice != nullptr)
		{
			_dice->Loggable::attach(*this);
			log("Dice", "Start logging.");
			hasBeenAttached = true;
		}
		break;
	}
	return hasBeenAttached;
}

/**
* Detaches the GameLogger from the given LogType is it has been recorded
* Logs if the GameLogger was succesfully detached
* @param lt Logtype to detach the GameLogger from
* @return true if the GameLogger was detached to a Loggable
*/
bool GameLogger::detachLogType(LogType lt)
{
	bool hasBeenDetached = false;
	switch (lt)
	{
	case LogType::GAME:
		if (_game != nullptr)
		{
			_game->detach(*this);
			log("Game", "Stop logging.");
			hasBeenDetached = true;
		}
		break;
	case LogType::MAP:
		if (_map != nullptr)
		{
			_map->Loggable::detach(*this);
			log("Map", "Stop logging.");
			hasBeenDetached = true;
		}
		break;
	case LogType::CHARACTERS:
		if (_map != nullptr)
		{
			for (Element* che : _map->getElements())
			{
				CharacterElement* ce = dynamic_cast<CharacterElement*>(che);
				if (ce != nullptr)
				{
					ce->getCharacter().detach(*this);
				}
			}
			log("Character", "Stop logging.");
			hasBeenDetached = true;
		}
		break;
	case LogType::DICE:
		if (_dice != nullptr)
		{
			_dice->Loggable::detach(*this);
			log("Dice", "Stop logging.");
			hasBeenDetached = true;
		}
		break;
	}
	return hasBeenDetached;
}

/**
* Set the GameLogger output stream from a filename
* Closes the current file if the file is opened.
* @param targetOutput Name of the output file
*/
void GameLogger::setOutputStream(string targetOutput)
{
	if (file != nullptr)
	{
		if (file->is_open()){
			file->close();
		}
		delete file;
	}

	file = new std::ofstream(targetOutput, ofstream::out);
	Logger::setOutputStream(*file);
}

/**
* Adds the LogType to the auto attach logtypes
* @param lt LogType to add
* @return true if the LogType was added
*/
bool GameLogger::addAutoAttachLogtype(LogType lt)
{
	if (find(_autoLoggedTypes.begin(), _autoLoggedTypes.end(), lt) == _autoLoggedTypes.end())
	{
		_autoLoggedTypes.push_back(lt);
		return true;
	}
	return false;
}

/**
* Removes the LogType from the auto attach logtypes
* @param lt LogType to remove
* @return true if the LogType was removed
*/
bool GameLogger::removeAutoAttachLogtype(LogType lt)
{
	if (find(_autoLoggedTypes.begin(), _autoLoggedTypes.end(), lt) != _autoLoggedTypes.end())
	{
		_autoLoggedTypes.remove(lt);
		return true;
	}
	return false;
}

/**
* Prints a string containing the current auto attached logtypes of the GameLogger
* @param lt LogType to remove
* @return true if the LogType was removed
*/
string GameLogger::currentLogTypes()
{
	if (_autoLoggedTypes.empty())
	{
		return "NONE.";
	}

	string s = "";
	for (LogType lt : _autoLoggedTypes)
	{
		switch (lt)
		{
		case LogType::GAME:
			s += "GAME";
			break;
		case LogType::MAP:
			s += "MAP";
			break;
		case LogType::CHARACTERS:
			s += "CHARACTERS";
			break;
		case LogType::DICE:
			s += "DICE";
			break;
		}
		s += " ";
	}
	return s;
}