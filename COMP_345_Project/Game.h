#pragma once
#include "Map.h"
#include "CharacterElement.h"

class CharacterElement;

class Game
{
public:
	Game(Map* m); //! Constructor of the Game class
	bool play(Character* player); // Starts a new game
	Map* getMap();
private:
	Map* map; // A pointer to the mapo used in the curretn game
	bool isGameOver(); // Checks if the game has finished
	bool run(CharacterElement*); // Is executed while that game hasn't finished running
	void perfomEndGame(); // Is executed at the end of the game	
};