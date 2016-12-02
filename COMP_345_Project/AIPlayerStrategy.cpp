//! 
//! @file 
//! @brief Implementation file for the AIPLayerStrategy class
//! 

#include "AIPLayerStrategy.h"

/**
* Executes a game turn on the AIPLayerStrategy
* @param map the map on which the game is played
* @param mo the map observer
* @param meo the map elements toggler
* @return true if the players wants to continue to play, false otherwise.
*/
bool AIPLayerStrategy::executeMovementTurn(Map& map, MapObserver& mo, MapElementsToggler& meo)
{
	int remainingSteps = NUMBER_OF_STEPS;

	mo.setPrintCharacterInfo(getStrategyName(), characterElement->getCharacter().getName());
	mo.setPrintTurnInfo(TurnType::AI_MOVE);
	mo.setPrintMovementInfo(remainingSteps);
	mo.printMap();

	std::list<std::pair<int, int>> pathTowardsHumanPlayer = calculateShortestPath(map);

	bool isPlaying = true;

	while (remainingSteps > 0)
	{
		char c = _getch();
		if (isPlaying)
		{
			switch (c)
			{
			case ' ':
				if (pathTowardsHumanPlayer.size() > 0)
				{
					--remainingSteps;
					mo.setPrintMovementInfo(remainingSteps);
					if (!performMovementStepAI(map, pathTowardsHumanPlayer))
					{
						return true;
					}
					meo.showPrevious();
				}
				else
				{
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

/**
* Calculates the path towards the player using the Bresenham's algorithm and is later adjusted
* to add additional tiles to when there is a diagonal movement
* @param map the map on which the path should be calculated
* @return a list that represents all the tiles that the player should go through to reach the human player
*/
std::list<std::pair<int, int>> AIPLayerStrategy::calculateShortestPath(Map& map)
{
	std::vector<std::pair<int, int>> pathTowardsHumanPlayer = bresenhamRightDirection(characterElement->getPosition().x, characterElement->getPosition().y, map.getPlayer().getPosition().x, map.getPlayer().getPosition().y);
	
	std::list<std::pair<int, int>> pathAdjusted;

	if (pathTowardsHumanPlayer.size() == 2 && !isInDiagonalDistance(pathTowardsHumanPlayer[0], pathTowardsHumanPlayer[1]))
	{
		return pathAdjusted;
	}

	// Between the very first tile and the second
	if (isInDiagonalDistance(pathTowardsHumanPlayer[0], pathTowardsHumanPlayer[1]))
	{
		pathAdjusted.push_back(calculateDiagonalIntermediateTile(pathTowardsHumanPlayer[0], pathTowardsHumanPlayer[1]));
	}

	// All the remaining tiles
	for (int i = 1; i < pathTowardsHumanPlayer.size() - 1; i++)
	{
		pathAdjusted.push_back(pathTowardsHumanPlayer[i]);
		if (isInDiagonalDistance(pathTowardsHumanPlayer[i], pathTowardsHumanPlayer[i + 1]))
		{
			pathAdjusted.push_back(calculateDiagonalIntermediateTile(pathTowardsHumanPlayer[i], pathTowardsHumanPlayer[i + 1]));
		}
	}

	return pathAdjusted;
}

/**
* Determines if  the two ppoints are at a single (1) diagonal distance from eachother
* @param lhs the first coordinate
* @param lhs the second coordinates
* @return true if the two tiles are at a diagonal distance
*/
bool AIPLayerStrategy::isInDiagonalDistance(std::pair<int, int> lhs, std::pair<int, int> rhs)
{
	return abs(lhs.first - rhs.first) == 1 && abs(lhs.second - rhs.second) == 1;
}

/**
* Calculates the intermediate point between two diagonal points
* @param lhs the first point
* @param rhs the second point
* @return true if the start point was succesfully set
*/
std::pair<int, int> AIPLayerStrategy::calculateDiagonalIntermediateTile(std::pair<int, int> lhs, std::pair<int, int> rhs)
{
	std::pair<int, int> result = lhs;

	result.first += rhs.first - lhs.first;

	return result;
}

/**
* Perform a step towards the human player on the map usign the path
* @param map the map on which the game is played
* @param pathTowardsHumanPlayer a list that represents the coordinates that the character should go through to reach the human player
* @return true if the character could successfuly move, false if he was blocked
*/
bool AIPLayerStrategy::performMovementStepAI(Map& map, std::list<std::pair<int, int>>& pathTowardsHumanPlayer)
{
	int xOffset = pathTowardsHumanPlayer.front().first - characterElement->getPosition().x;
	int yOffset = pathTowardsHumanPlayer.front().second - characterElement->getPosition().y;
	pathTowardsHumanPlayer.pop_front();
	if (map.moveElement(xOffset, yOffset, *characterElement))
	{
		return true;
	}
	return false;
}