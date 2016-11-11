#include "GameController.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "FolderUtils.h"
#include "MapController.h"
#include "CharacterController.h"
#include "Game.h"

using namespace std;

//! Starts a new game
//! Prompts the user to select the character that he will play
//! and a campaign which maps he will play on
void GameController::play()
{
	cout << "--------GAME INITIALIZATION--------" << endl << endl;
	//We let the user select his character
	selectCharacter();

	//We let the user select his campaign
	selectCampaign();

	mapElementsObserver = new MapElementsObserver(map);

	//We are ready to launch the game
	launchGame();

	if (map != nullptr) {
		delete map;
		delete mapElementsObserver;
		map = nullptr;
	}

	
}

//! Prompts the user to select a character
//! Reads the characters from the txt files
void GameController::selectCharacter()
{
	cout << "===SELECT A CHARACTER===" << endl << endl;
	//Load all maps names
	string characterName;
	ifstream characterFile;
	vector<string> allFiles = getFilesInsideFolderNoExtension("SaveFiles\\Characters");
	while (character == nullptr) {

		cout << "Available characters:" << endl;
		for (string& file : allFiles)
		{
			cout << file << endl;
		}

		cout << endl << "Enter the name of the character you want to play as: ";
		cin >> characterName;
		character = readCharacterFile("SaveFiles/Maps/", characterName);

		if (character == nullptr)
		{
			cout << "The character " << characterName << " does not exist. Please enter a valid character name." << endl << endl;
		}
	}

	cout << "The character " << characterName << " was succefully loaded." << endl << endl;
}

//! Prompts the user to select a map
//! Reads the maps from the txt files
void GameController::selectCampaign()
{
	cout << "===SELECT A MAP===" << endl << endl;
	//Load all maps names
	string mapName;
	ifstream mapFile;
	vector<string> allFiles = getFilesInsideFolderNoExtension("SaveFiles\\Maps");
	while(map == nullptr) {

		cout << "Available maps:" << endl;
		for (string& file : allFiles)
		{
			cout << file << endl;
		}

		cout << endl << "Enter the name of the map you want to play: ";
		cin >> mapName;
		map = readMapFile("SaveFiles/Maps/" + mapName + ".txt", mapName);

		if (map == nullptr)
		{
			cout << "The map " << mapName << " does not exist. Please enter a valid map name." << endl << endl;
		}
	}

	cout << "The map " << mapName << " was succefully loaded." << endl << endl;


	
}

//! Creates a new instance of the Game class an launches it
void GameController::launchGame()
{
	Game g = Game(map);
	g.play(character);
}