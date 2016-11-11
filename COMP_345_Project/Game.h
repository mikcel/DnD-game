#pragma once
#include "Map.h"
#include "Player.h"

class Game
{
public:
	Game(Map* m); //! Constructor of the Game class
	void play(Character* player); // Starts a new game
private:
	Map* map; // A pointer to the mapo used in the curretn game
	bool isGameOver(); // Checks if the game has finished
	int run(Player*); // Is executed while that game hasn't finished running
	void perfomEndGame(); // Is executed at the end of the gmae
};