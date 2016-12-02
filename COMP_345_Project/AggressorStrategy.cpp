//! @file 
//! @brief Implementation file for the AggressorStrategy class
//!

#include "AggressorStrategy.h"

/**
* Obtains the map representation of the current character
* @return the symbol that will represent the curretn character on the map
*/
std::string AggressorStrategy::print() const
{
	return characterElement->getCharacter().isAlive() ? "X" : "D";
}

/**
* Obtains a human-readable name for the strategy
* @return a string that represents the type of the strategy
*/
std::string AggressorStrategy::getStrategyName()
{
	return "Enemy";
}

/**
* Executes the attack phase of the character turn
* Because teh character is an agressor, he will try to attack the player if he is near him
* @param map the map on which the game is played
* @param mo the map observer
* @param meo the map elements toggler
* @return true if the players wants to continue to play, false otherwise.
*/
bool AggressorStrategy::executeAttack(Map& map, MapObserver& mo, MapElementsToggler& meo)
{
 	mo.setPrintTurnInfo(TurnType::AI_ATTACK);
	mo.printMap();

	bool isPlaying = true;

	while (true)
	{
		char c = _getch();
		if (isPlaying)
		{
			switch (c)
			{
			case ' ': // The aggressor (enemy) tries to attack the player if possible
			{
				Position thisCharacterPosition = characterElement->getPosition();
				Position humanPlayerCharacterPosition = map.getPlayer().getPosition();
				if (isTileNextToOrDiagonal(thisCharacterPosition.x, thisCharacterPosition.y, humanPlayerCharacterPosition.x, humanPlayerCharacterPosition.y))
				{
					if (!characterElement->attack(map.getPlayer())) //! If player died
					{
						meo.showPrevious();
						cout << "You died. Game over." << endl;
						system("pause");
						return false;
					}
					meo.showPrevious();
				}
				else
				{
					cout << endl << characterElement->getCharacter().getName() << " did not attack anyone on this turn." << endl;
				}
				cout << endl;
				system("pause");
				return true;
			}

				break;
			case 'q': //Quit the application
			case 'Q': //Quit the application
				return false;
				break;
			case 'T': //Toggles the view of the map elements
			case 't': //Toggles the view of the map elements
				meo.show();
				break;
			case 'p': //Toggles the view of the map elements
				meo.showPlayer();
				break;
			case 'e': //Toggles the view of the map elements
				meo.showEnemies();
				break;
			case 'c': //Toggles the view of the map elements
				meo.showChests();
				break;
			}
		}
		else if (c != 224 && c != KEY_UP && c != KEY_DOWN && c != KEY_RIGHT && c != KEY_LEFT)
		{
			if (system("CLS")) system("clear");
			mo.printMap();
			isPlaying = true;
		}
	}

	return true;
}