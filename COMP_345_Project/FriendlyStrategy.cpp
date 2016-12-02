#include "FriendlyStrategy.h"

/**
* Obtains the map representation of the current character
* @return the symbol that will represent the curretn character on the map
*/
std::string FriendlyStrategy::print() const
{
	return "A";
}

/**
* Obtains a human-readable name for the strategy
* @return a string that represents the type of the strategy
*/
std::string FriendlyStrategy::getStrategyName()
{
	return "Ally";
}

/**
* Executes the attack phase of the character turn
* Because this is a friendly strategy, the character will not attack anyone
* @param map the map on which the game is played
* @param mo the map observer
* @param meo the map elements toggler
* @return true if the player wants to continue to play, false otherwise
*/
bool FriendlyStrategy::executeAttack(Map& map, MapObserver& mo, MapElementsToggler& meo)
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
			case ' ':
			{
				cout << endl << characterElement->getCharacter().getName() << " did not attack anyone on this turn." << endl;
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