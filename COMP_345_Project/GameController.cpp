#include "GameController.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "FolderUtils.h"
#include "MapController.h"
#include "CharacterController.h"
#include "Game.h"
#include "CampaignController.h"
#include "GameLogger.h"
#include "Time_Utils.h"

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

	//We are ready to launch the game
	launchGame();


	if (campaign != nullptr) {
		delete campaign;
		campaign = nullptr;
	}

	if (character != nullptr)
	{
		delete character;
		character = nullptr;
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
		while (cin.fail())
		{
			cout << "Incorrect Input. Please enter a correct character name: ";
			cin.clear();
			cin >> characterName;
		}

		character = readCharacterFile(characterName);

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
	cout << "===SELECT A CAMPAIGN===" << endl << endl;
	//Load all Campaign names
	string campaignName;
	ifstream campaignFile;
	vector<string> allFiles = getFilesInsideFolderNoExtension("SaveFiles\\Campaigns");
	while (campaign == nullptr) {

		cout << "Available Campaigns:" << endl;
		for (string& file : allFiles)
		{
			cout << file << endl;
		}

		cout << endl << "Enter the name of the campaign you want to play: ";
		cin >> campaignName;
		/*bool validCampaign = false;
		for (string& file : allFiles)
		{
		if (campaignName == file){
		validCampaign = true;
		}
		}
		if (!validCampaign){
		cout << "The campaigns " << campaignName << " does not exist. Please enter a valid campaign name." << endl << endl;

		continue;
		}*/

		while (cin.fail())
		{
			cout << "Incorrect Input. Please enter a correct campaigns name: ";
			cin.clear();
			cin >> campaignName;
		}

		campaign = readCampaignFile(campaignName);

		if (campaign == nullptr)
		{
			cout << "The campaigns " << campaignName << " does not exist. Please enter a valid campaign name." << endl << endl;
		}
	}

	cout << "The campaign " << campaignName << " was succefully loaded." << endl << endl;
}

//! Creates a new instance of the Game class an launches it
void GameController::launchGame()
{
	Game g(campaign);

	//Writes the log file
	string currentTime = TimeUtils::getCurrentTime("%Y%m%d%H%M%S");

	GameLogger::instance().setOutputStream("Log\\" + currentTime + "_log.txt");
	GameLogger::instance().recordGame(&g); //The game was created and ready to be recorded.
	GameLogger::instance().recordDice(&Dice::instance()); //The dice is ready to be recorded.

	g.play(character);

	GameLogger::instance().flush();
}