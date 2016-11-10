#pragma once
#include "Map.h"
#include "Player.h"

class Game
{
public:
	Game(Map* m);
	void play(Character* player);
private:
	Map* map;
	bool isGameOver();
	int run(Player*);
};