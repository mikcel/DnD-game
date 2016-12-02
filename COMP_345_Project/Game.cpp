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
#include "MapController.h"
#include "GameLogger.h"

using namespace std;

//! Creates a new instance of the Game class
//! @param m a pointer to the map that will be used in the current game
Game::Game(Campaign* c)
{
	campaign = c;
}

//! Starts a new game with the playerined as parameter
//! @param player to be used in the current game
void Game::play(Character* player)
{
	vector<string> mapNames = *campaign->getCampaignMapNames();
	bool wantToquit = false;

	for (int i = 0; i < mapNames.size(); i++){

		log("Loading map : " + mapNames[i] + ".");
		Map* map = readMapFile("SaveFiles/Maps/" + mapNames[i] + ".txt", mapNames[i]);
		log("Map loaded");
		system("pause");

		GameLogger::instance().recordMap(map); //The map was loaded and ready to be recorded.

		log("Map setup start.");
		CharacterElement tempP(*player, new HumanPlayerStrategy());
		CharacterElement * p = map->placePlayer(tempP);
		log("Map setup ended.");

		GameLogger::instance().recordCharacters(); //The characters were placed and ready to be recorded.

		//Let's run the game
		bool finishedMap = run(*map);
		log("Map ended.");

		if (finishedMap)
		{
			log("Map end phase start.");
			perfomEndGame(&player, *map);
			log("Map end phase finished.");

			wantToquit = false;
		}

		if (!gameContinues(!finishedMap, i + 1, mapNames))
		{
       			if (!p->getCharacter().isAlive()){
				log("Player died.");
			}
			else{
				log("Player quit.");
			}

			cout << "Exiting to main menu." << endl;
			system("pause");
			return;
		}

	}

	cout << "Congratulations! You have beaten the " << campaign->getCampaignName() << " campaign!\nEnjoy the spoils of a bountiful victory" << endl;
	log("Player " + player->getName() + " finished campaign " + campaign->getCampaignName() + ".");
	system("pause");
}

//! Determines if the player wants to continue the game
//! @param wantToQuit true is the player quit the map
//! @param nextMapIndex Index of the next map in the map names
//! @param mapNames Vector of the names of the maps of the current campaign
//! @return true if the user wants to keep playing
bool Game::gameContinues(bool wantToQuit, int nextMapIndex, vector<string>& mapNames)
{
	if (wantToQuit){
		return false;
	}

	if (nextMapIndex >= mapNames.size()){
		return true;
	}
	else{
		string userChoice = "";
		while (true)
		{
			cout << endl << "Do you want to play the next map: " + mapNames[nextMapIndex] + " ?(Y/N)" << endl;
			cin >> userChoice;
			if (userChoice == "Y"){
				return true;
			}
			else if (userChoice == "N"){
				return false;
			}
			else{
				cout << "Invalid input.";
			}
		}
	}
}

//! Represents the main game loop of the Dungeons&Dragons game
//! "Listens" to the input of the user and adjusts the game accordingly 
//! @param player to be used in the current game
bool Game::run(Map& map)
{
	//Set all of our observers
	MapObserver mo(map);
	map.Observable::attach(mo);

	MapElementsToggler meo(&map);

	#define KEY_UP 72
	#define KEY_DOWN 80
	#define KEY_LEFT 75
	#define KEY_RIGHT 77

	//Initial display of the map
	mo.printMap();
	
	bool isPlaying = true;
	int c = 0;

	vector<CharacterElement*> characterElementsHavingTurn;
	characterElementsHavingTurn.push_back(&(map.getPlayer()));
	for (Element* element : map.getElements())
	{
		CharacterElement* characterElement = dynamic_cast<CharacterElement*>(element);
		if (characterElement)
		{
			characterElementsHavingTurn.push_back(characterElement);
		}
	}

	for (int i = 0;; i++)
	{
		int chrIdx = i % characterElementsHavingTurn.size();
		if (characterElementsHavingTurn[chrIdx]->getCharacter().getCurrentHitPoints() != 0){

			bool wantsToContinuePlaying = characterElementsHavingTurn[chrIdx]->getCharacterStrategy()->executeTurn(map, mo, meo);
			if (!wantsToContinuePlaying)
			{
				return false;
			}
			if (isGameOver(map))
			{
					break;
				}
			}
		}

	return true;
}

//! Method that is executed at the end of the game
//! Adjusts the level of the Player and returns the user to the main menu
void Game::perfomEndGame(Character** p, Map& map)
{
	Character* currentChar = &(map.getPlayerPointer()->getCharacter());
	cout << "CONGRATULATIONS!!! YOU REACHED THE EXIT ALIVE!!!" << endl;
	cout << "IT'S TIME FOR " << currentChar->getName() << " TO GO UP A LEVEL!!!" << endl << endl;

	system("pause");
	cout << endl;


	currentChar->incrementLevel();
	log("Player " + currentChar->getName() + " level increased to " + to_string(currentChar->getLevel()) + ".");

	cout << *currentChar;

	CharacterController cc(currentChar);
	cc.saveCharacter();
	log("Character " + currentChar->getName() + " saved.");

	*p = currentChar->clone();
}

//! Checks if the game is over (the player has reached the end point)
//! @return true if the game over, false otherwise
bool Game::isGameOver(Map& map)
{
	return map.isEndPoint(map.getPlayer().getPosition()); //|| map.getPlayer().getCharacter().getCurrentHitPoints() == 0;
}

//!Return the provider string "Game"
std::string Game::provider()
{
	return "Game";
}