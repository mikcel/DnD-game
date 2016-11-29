#include "Game.h"
#include "Character.h"
#include "Player.h"
#include <typeinfo>
#include <conio.h>
#include "MapObserver.h"
#include "MapElementsToggler.h"
#include "Dice.h"
#include "CharacterController.h"
#include "Chest.h"

using namespace std;

//! Creates a new instance of the Game class
//! @param m a pointer to the map that will be used in the current game
Game::Game(Map* m)
{
	map = m;
}

//! Starts a new game with the playerined as parameter
//! @param player to be used in the current game
bool Game::play(Character* player)
{
	Player tempP(*player);
	Player * p = map->placePlayer(tempP);

	//Let's run the game
	if (run(p))
	{
		perfomEndGame();
		return false;
	}
	else{
		return true;
	}
}

//! Represents the main game loop of the Dungeons&Dragons game
//! "Listens" to the input of the user and adjusts the game accordingly 
//! @param player to be used in the current game
bool Game::run(Player* p)
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
	mo.printMap();
	
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
				return false;
				break;
			case 'T': //Toggles the view of the map elements
			case 't': //Toggles the view of the map elements
				meo.show();
				isPlaying = false;
				break;
			case 'p': //Toggles the view of the map elements
				meo.showPlayer();
				isPlaying = false;
				break;
			case 'e': //Toggles the view of the map elements
				meo.showEnemies();
				isPlaying = false;
				break;
			case 'c': //Toggles the view of the map elements
				meo.showChests();
				isPlaying = false;
				break;
			}
		}
		else if(c != 224 && c != KEY_UP && c != KEY_DOWN && c != KEY_RIGHT && c != KEY_LEFT){
			if (system("CLS")) system("clear");
			mo.printMap();
			isPlaying = true;
		}

	}
	return true;
}






//! Checks if the game is over (the player has reached the end point)
//! @return true if the game over, false otherwise
bool Game::isGameOver()
{
	return map->isEndPoint(map->getPlayer().getPosition()) || map->getPlayer().getCharacter().getCurrentHitPoints()==0;
}

//! Method that is executed at the end of the game
//! Adjusts the level of the Player and returns the user to the main menu
void Game::perfomEndGame()
{
	Character& currentChar = map->getPlayer().getCharacter();
	cout << "CONGRATULATIONS!!! YOU REACHED THE EXIT ALIVE!!!" << endl;
	cout << "IT'S TIME FOR " << currentChar.getName() << " TO GO UP A LEVEL!!!" << endl << endl;

	system("pause");
	cout << endl;


	currentChar.incrementLevel(true);

	cout << currentChar;

	CharacterController cc(&currentChar);
	cc.saveCharacter();
}