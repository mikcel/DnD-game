//! @file 
//! @brief Implementation file for the MapObserver class
//!

#include "MapObserver.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

/**
* Intializes a MapObserver with a map
* @param m Map observed (for the printing during the update)
*/
MapObserver::MapObserver(const Map& m) : map(m), timesUpdated(0){}

/**
* When notified, clears the console and prints the map
*/
void MapObserver::update()
{
	printMap();
}

/**
* Sets the type of character taht is currently having the turn in the game
* @param typeOfcharacter type of teh cahracter
* @param characterName name of teh character
*/
void MapObserver::setPrintCharacterInfo(std::string typeOfcharacter, std::string characterName)
{
	this->typeOfcharacter = typeOfcharacter;
	this->characterName = characterName;
}

/**
* Sets the current type of turn
* @param turnType type of the turn
*/
void MapObserver::setPrintTurnInfo(TurnType turnType)
{
	this->turnType = turnType;
}

/**
* Sets the reaming type of steps that the character has
* @param stepsRemnaining the number of steps remaining
*/
void MapObserver::setPrintMovementInfo(int stepsRemnaining)
{
	this->stepsRemnaining = stepsRemnaining;
}

/**
* Print map instructions and a view of the map
*/
void MapObserver::printMap()
{
	if (system("CLS")) system("clear");

	// ================ Draw map ================
	cout << "========= " << map.getName() << " =========" << endl << endl;
	cout << map.print() << endl;

	// ================ Write Info about current turn ================
	cout << "Current turn: " << typeOfcharacter << " named \"" << characterName << "\"" << endl;

	if (turnType == TurnType::HUMAN_PLAYER_MOVE || turnType == TurnType::AI_MOVE)
	{
		cout << "Current action: " << "Movement. Number of steps remaining: " << stepsRemnaining << endl;
	}
	else
	{
		cout << "Current action: " << "Attack" << endl;
	}

	// ================ Write Instructions ================

	// Human player
	cout << endl << "---- Instructions ----" << endl;

	if (turnType == TurnType::HUMAN_PLAYER_MOVE)
	{
		cout << "Enter : End Movement phase and go to Attack phase immediately" << endl;
	}
	else if (turnType == TurnType::HUMAN_PLAYER_ATTACK)
	{
		cout << "Enter : End turn immediately" << endl;
	}
	if (turnType == TurnType::HUMAN_PLAYER_MOVE)
	{
		cout << "Arrows : Move" << endl;
		cout << "Z : Loot nearby Chests or fallen Enemies." << endl;
		cout << "I : To manage your equipment." << endl;
	}
	else if (turnType == TurnType::HUMAN_PLAYER_ATTACK)
	{
		cout << "Z : Loot nearby Chests or fallen Enemies." << endl;
		cout << "A : Attack" << endl;
		cout << "I : To manage your equipment." << endl;
	}

	// AI
	if (turnType == TurnType::AI_MOVE || turnType == TurnType::AI_ATTACK)
	{
		cout << "Space : Watch next turn" << endl;
	}

	cout << "T : Display all map information" << endl;
	cout << "P : Display player information" << endl;
	cout << "E : Display NPCs information" << endl;
	cout << "C : Display chests information" << endl;
	cout << "Q : Quit (Progression will not be saved)" << endl;
}