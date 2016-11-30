#include "Game.h"
#include "Character.h"
#include "CharacterElement.h"
#include <typeinfo>
#include <conio.h>
#include "MapObserver.h"
#include "MapElementsToggler.h"
#include "Dice.h"
#include "CharacterController.h"
#include "HumanPlayerStrategy.h"

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
	CharacterElement tempP(*player, new HumanPlayerStrategy());
	CharacterElement * p = map->placePlayer(tempP);

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
bool Game::run(CharacterElement* p)
{
	//Set all of our observers
	MapObserver mo(*map);
	map->attach(mo);

	MapElementsToggler meo(map);

	#define KEY_UP 72
	#define KEY_DOWN 80
	#define KEY_LEFT 75
	#define KEY_RIGHT 77

	//Initial display of the map
	mo.printMap();
	
	bool isPlaying = true;
	int c = 0;

	vector<CharacterElement*> characterElementsHavingTurn;
	characterElementsHavingTurn.push_back(&(map->getPlayer()));
	for (Element* element : map->getElements())
	{
		CharacterElement* characterElement = dynamic_cast<CharacterElement*>(element);
		if (characterElement)
		{
			characterElementsHavingTurn.push_back(characterElement);
		}
	}

	for (int i = 0;; i++)
	{
		bool wantsToContinuePlaying = characterElementsHavingTurn[i % characterElementsHavingTurn.size()]->getCharacterStrategy()->executeTurn(*map, mo, meo);
		if (!wantsToContinuePlaying)
		{
				return false;
		}
		if (isGameOver())
		{
				break;
			}
		}

	return true;
}






//! Checks if the game is over (the player has reached the end point)
//! @return true if the game over, false otherwise
bool Game::isGameOver()
{
	return map->isEndPoint(map->getPlayer().getPosition()) || map->getPlayer().getCharacter().getCurrentHitPoints() == 0;
}

//! Method that is executed at the end of the game
//! Adjusts the level of the Player and returns the user to the main menu
void Game::perfomEndGame()
{
	Character* currentChar = &(map->getPlayer().getCharacter());
	cout << "CONGRATULATIONS!!! YOU REACHED THE EXIT ALIVE!!!" << endl;
	cout << "IT'S TIME FOR " << currentChar->getName() << " TO GO UP A LEVEL!!!" << endl << endl;

	system("pause");
	cout << endl;

	currentChar->incrementLevel();

	cout << *dynamic_cast<Fighter*>(currentChar);

	CharacterController cc(currentChar);
	cc.saveCharacter();
}

Map* Game::getMap()
{
	return map;
}