#include "StrategyTest.h"

//! cppunit test cases registration
CPPUNIT_TEST_SUITE_REGISTRATION(StrategyTest);

//! test method for the "read as saved" builder
//! Test Case: check if the map is loaded correctly and contains valid data
//! This method uses the sample map files Map1.txt, Map2.txt and Map3.txt that are inside the MapFiles folder
void StrategyTest::allyTransformsToEnemy()
{
	CharacterElement& player = *new CharacterElement("Player", new HumanPlayerStrategy());
	CharacterElement& enemy = *new CharacterElement("Enemy 1", new AggressorStrategy());
	CharacterElement& ally = *new CharacterElement("Ally 1", new FriendlyStrategy());

	// Checks if the character element have the right strategy
	CPPUNIT_ASSERT(dynamic_cast<HumanPlayerStrategy*>(player.getCharacterStrategy()) != nullptr);
	CPPUNIT_ASSERT(dynamic_cast<AggressorStrategy*>(enemy.getCharacterStrategy()) != nullptr);
	CPPUNIT_ASSERT(dynamic_cast<FriendlyStrategy*>(ally.getCharacterStrategy()) != nullptr);

	// Perform multiple attacks
	player.attack(enemy);
	player.attack(ally);
	enemy.attack(player);

	// Checks if only the strategy of the ally has changed to and aggressor strategy
	CPPUNIT_ASSERT(dynamic_cast<HumanPlayerStrategy*>(player.getCharacterStrategy()) != nullptr);
	CPPUNIT_ASSERT(dynamic_cast<AggressorStrategy*>(enemy.getCharacterStrategy()) != nullptr);
	CPPUNIT_ASSERT(dynamic_cast<AggressorStrategy*>(ally.getCharacterStrategy()) != nullptr);

	if (system("CLS")) system("clear");
}


//! test method for the "adjust to level" builder
//! Test Case: check if the map constructed with the "adjust to level" builder actually adjusts the level of all the items and characters that are on it
//! This method uses the sample map files Map1.txt and Map2.txt that are inside the MapFiles folder
void StrategyTest::allyAndEnemyMovement()
{
	// Create map and load its components
	string character_name = "Simon";
	string map_name = "map5.1";

	Character* character = readCharacterFile("SaveFiles/Maps/", character_name);
	Map* map = readMapFile("SaveFiles/Maps/" + map_name + ".txt", map_name);

	CharacterElement tempPlayer(*character, new HumanPlayerStrategy());
	map->placePlayer(tempPlayer);

	CharacterElement* player = &map->getPlayer();
	CharacterElement* enemy;
	CharacterElement* ally;
	for (Element* element : map->getElements())
	{
		CharacterElement* characterElement = dynamic_cast<CharacterElement*>(element);
		if (characterElement)
		{
			AggressorStrategy* aggressorStrategy = dynamic_cast<AggressorStrategy*>(characterElement->getCharacterStrategy());
			FriendlyStrategy* friendlyStrategy = dynamic_cast<FriendlyStrategy*>(characterElement->getCharacterStrategy());
			if (aggressorStrategy)
			{
				enemy = characterElement;
			}
			else if (friendlyStrategy)
			{
				ally = characterElement;
			}
		}
	}

	AggressorStrategy* aggressorStrategy = dynamic_cast<AggressorStrategy*>(enemy->getCharacterStrategy());
	FriendlyStrategy* friendlyStrategy = dynamic_cast<FriendlyStrategy*>(ally->getCharacterStrategy());

	Position playerPosition = player->getPosition();
	Position enemyStartPosition = enemy->getPosition();
	Position allyStartPosition = ally->getPosition();

	float distanceX;
	float distanceY;

	// Calculate the initial distance from the enemy to the player using Pythagorean theorem
	distanceX = enemyStartPosition.x - playerPosition.x;
	distanceY = enemyStartPosition.y - playerPosition.y;
	float startDistanceFromEnemyToPlayer = sqrt(distanceX * distanceX + distanceY * distanceY);

	// Calculate the initial distance from the ally to the player using Pythagorean theorem
	distanceX = allyStartPosition.x - playerPosition.x;
	distanceY = allyStartPosition.y - playerPosition.y;
	float startDistanceFromAllyToPlayer = sqrt(distanceX * distanceX + distanceY * distanceY);

	std::list<std::pair<int, int>> pathOfEnemy = aggressorStrategy->calculateShortestPath(*map);
	std::list<std::pair<int, int>> pathOfFriend = friendlyStrategy->calculateShortestPath(*map);

	for (int i = 0; i < 4; i++)
	{
		aggressorStrategy->performMovementStepAI(*map, pathOfEnemy);
		friendlyStrategy->performMovementStepAI(*map, pathOfFriend);
	}

	Position enemyEndPosition = enemy->getPosition();
	Position allyEndPosition = ally->getPosition();

	// Calculate the distance from the enemy to the player using Pythagorean theorem after 4 steps performed
	distanceX = enemyEndPosition.x - playerPosition.x;
	distanceY = enemyEndPosition.y - playerPosition.y;
	float endDistanceFromEnemyToPlayer = sqrt(distanceX * distanceX + distanceY * distanceY);

	// Calculate the distance from the ally to the player using Pythagorean theorem after 4 steps performed
	distanceX = allyEndPosition.x - playerPosition.x;
	distanceY = allyEndPosition.y - playerPosition.y;
	float endDistanceFromAllyToPlayer = sqrt(distanceX * distanceX + distanceY * distanceY);

	// Check if the distance between the player and the enemy as well as between the player and the ally
	// is smaller after the 4 steps executed
	CPPUNIT_ASSERT(startDistanceFromEnemyToPlayer > endDistanceFromEnemyToPlayer);
	CPPUNIT_ASSERT(startDistanceFromAllyToPlayer > endDistanceFromAllyToPlayer);
}