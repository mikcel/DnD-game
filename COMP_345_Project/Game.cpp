#include "Game.h"
#include "Character.h"
#include "Player.h"
#include <typeinfo>
#include <conio.h>
#include "MapObserver.h"
#include "MapElementsObserver.h"

using namespace std;

Game::Game(Map* m)
{
	map = m;
}

void Game::play(Character* player)
{
	Player tempP(*player);
	Player * p = map->placePlayer(tempP);

	//Let's run the game
	run(p);

}

int Game::run(Player* p)
{
	//Set all of our observers
	MapObserver mo(*map);
	map->attach(mo);

	MapElementsObserver meo(map);

	#define KEY_UP 72
	#define KEY_DOWN 80
	#define KEY_LEFT 75
	#define KEY_RIGHT 77
	#define KEY_T 114
	#define KEY_Q 113

	//Initial display of the map
	mo.update();

	int c = 0;
	while (!isGameOver())
	{
		c = 0;

		switch ((c = _getch())) {
		case KEY_UP: //Move the character up
			map->moveElement(0, -1, *p);
			break;
		case KEY_DOWN: //Move the character down
			map->moveElement(0, 1, *p);
			break;
		case KEY_LEFT: //Move the character left
			map->moveElement(-1, 0, *p);
			break;
		case KEY_RIGHT: //Move the character right
			map->moveElement(1, 0, *p);
			break;
		case 'q': //Quit the application
		case 'Q': //Quit the application
			return 0;
			break;
		case 'T': //Toggles the view of the map elements
		case 't': //Toggles the view of the map elements
			break;

		}
	}
}

bool Game::isGameOver()
{
	return map->isEndPoint(map->getPlayer().getPosition());
}