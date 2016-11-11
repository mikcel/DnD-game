#include "Game.h"
#include "Character.h"
#include "Player.h"
#include <typeinfo>
#include <conio.h>
#include "MapObserver.h"
#include "MapElementsObserver.h"
#include "Dice.h"
#include "CharacterController.h"

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
	perfomEndGame();
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

	//Initial display of the map
	mo.update();
	
	bool isPlaying = true;
	int c = 0;
	while (!isGameOver())
	{
		c = _getch();
		if (isPlaying) {
			switch (c) {
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
				meo.toggle();
				isPlaying = false;
				break;
			}
		}
		else if(c == 't' || c == 'T') {
			isPlaying = true;
		}
	}
}

bool Game::isGameOver()
{
	return map->isEndPoint(map->getPlayer().getPosition());
}

void Game::perfomEndGame()
{
	Character& currentChar = map->getPlayer().getCharacter();
	cout << "CONGRATULATIONS!!! YOU REACHED THE EXIT ALIVE!!!" << endl;
	cout << "IT'S TIME FOR " << currentChar.getName() << " TO GO UP A LEVEL!!!" << endl << endl;

	system("pause");
	cout << endl;


	currentChar.incrementLevel(Dice::roll(currentChar.getHitDice()));

	cout << currentChar;

	CharacterController cc(&currentChar);
	cc.saveCharacter();

	cout << "Press any key to return to the main menu" << endl;
	cin.ignore(); // Wait for any key
}