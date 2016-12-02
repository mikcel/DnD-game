//!
//! @file 
//! @brief Implementation file for Map Controller
//! 

//!
//! This class allows the creation and manipulation of a map. It also allows reading from a map file.
//!

#include "MapController.h"
#include "Character.h"
#include "Chest.h"
#include "FolderUtils.h"
#include "CharacterElement.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include "AggressorStrategy.h"
#include "FriendlyStrategy.h"
#include "HumanPlayerStrategy.h"
#include "ItemUtils.h"
using namespace std;

//! Default Constructor
MapController::MapController()
{
	currentMap = nullptr;
}

//! Parametrized constructor
//! @param Map pointer
MapController::MapController(Map* currentMap)
{
	this->currentMap = currentMap; //! Sets the current map pointer
}

//! Destructor
MapController::~MapController()
{

	//! deletion of pointer is already handled
}

//! Accessor for current Map
//! @return Map pointer
Map* MapController::getCurrentMap() {
	return currentMap;
}

//! Mutator for current Map
//! @param reference to a map object
void MapController::setCurrentMap(Map& newMap) {
	currentMap = new Map(newMap); //! Make a cdeep copy of the map passed
}

//! Method to create a Map
//! @return - 
void MapController::createMap() {
	cout << "==== MAP CREATION ====" << endl << endl;

	//string widthS, heightS;
	int width, height;
	bool isInvalid = false;
	Map * m = nullptr;
	string mapName;
	cout << "Enter the name of new map." << endl; //! Asks name of the map
	cin >> mapName;
	do {

		if (isInvalid) //! Check if values are valid
		{
			cout << "Invalid values!" << endl;
		}

		isInvalid = false;

		//! Asks for map dimensions
		cout << "Enter the desired dimensions of the map" << endl;
		cout << "Width: ";
		cin >> width;
		while (cin.fail() || width < 0) {
			cout << "Incorrect Input. Please enter a valid number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> width;
		}

		//Height
		cout << "Height: ";
		cin >> height;
		while (cin.fail() || height < 0) {
			cout << "Incorrect Input. Please enter a valid number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> height;
		}
		cout << endl;

		try {
			m = new Map(width, height, mapName);
		}
		catch (invalid_argument e)
		{
			isInvalid = true;
		}

	} while (isInvalid);

	currentMap = m;
	editMap(true); //! Call method to edit the map created
}

//! Method to edit a map
//! @param bool if creating currently creating a map
void MapController::editMap(bool creatingNewMap) {
	if (!creatingNewMap) {
		cout << "==== MAP EDITION ====" << endl << endl;
		if (!cacheMap()) {
			return;
		}
	}
	Map* m = currentMap;

	cout << m->print() << endl;

	//! Output the keys for editing the map
	bool isInvalid = false;
	cout << "LEGEND: F Floor, W Wall, X Enemy, C Chest, () Start point, [] End point" << endl;
	cout << "Enter Q at any time to save and quit the map " << (creatingNewMap ? "creation" : "edition") << ".\n" << endl;

	string xS, yS, eS;
	int x, y;

	while (true) //! For as long as the user wants to edit the map
	{
		cout << "Edit a new tile" << endl;
		xS.clear();
		yS.clear();
		eS.clear();
		x = y = -1;

		//! Enter Element
		do {
			if (isInvalid)
			{
				cout << "Invalid element!" << endl;
			}

			cout << "Element (S for start point, L for end point, F for Floor, W for Wall, X for enemy, A for friendly NPC , C for Chest, F for floor): ";
			cin >> eS;
			if (eS == "Q")
			{
				quit();
				return;
			}

			isInvalid = eS != "S" && eS != "L" && eS != "F" && eS != "W" && eS != "X" && eS != "A" && eS != "C" && eS != "F";
		} while (isInvalid);

		//! Enter X
		do {
			if (isInvalid)
			{
				cout << "Invalid X!" << endl;
			}

			cout << "X: ";
			cin >> xS;

			if (xS == "Q")
			{
				quit();
				return;
			}
			stringstream(xS) >> x;

			isInvalid = x < 0;
		} while (isInvalid);

		//! Enter Y
		do {
			if (isInvalid)
			{
				cout << "Invalid Y!" << endl;
			}

			cout << "Y: ";
			cin >> yS;

			if (yS == "Q")
			{
				quit();
				return;
			}
			stringstream(yS) >> y;

			isInvalid = y < 0;
		} while (isInvalid);

		bool success = false;

		//! Actions performed based on the element type
		if (eS == "S") //! Start point
		{
			success = m->setStartPoint(x, y);
		}
		else if (eS == "L") //! End point
		{
			success = m->setEndPoint(x, y);
		}
		else if (eS == "F") //! Floor
		{
			success = m->setTileType(x, y, TileType::FLOOR);
		}
		else if (eS == "W") //! Wall
		{
			success = m->setTileType(x, y, TileType::WALL);
		}
		else if (eS == "X") //! Enemy
		{
			CharacterElement enemy(chooseEnemy(), new AggressorStrategy());
			success = m->setElementAt(x, y, enemy);
		}
		else if (eS == "A") //! Friend
		{
			CharacterElement ally(chooseEnemy(), new FriendlyStrategy());
			success = m->setElementAt(x, y, ally);
		}
		else if (eS == "C") //! Chest
		{
			Chest * e = chooseChestItems();
			success = m->setElementAt(x, y, *e);
			delete e;
		}
		else if (eS == "F")//! floor
		{
			success = m->removeElementAt(x, y);
		}
		//! Action result
		if (success) //! If the tile was successfully edited
		{
			cout << "The action was SUCCESFULLY performed" << endl;
		}
		else //! The was an issue during the tile edition
		{
			cout << "The action was NOT performed due to an INVALID parameter" << endl;
		}

		cout << m->print() << endl;
		cout << "Map validity: " << (m->isValid() ? "VALID" : "INVALID") << endl << endl;
	}


}

//! Prompts the user to choose the items that will be added to the chest
//! @return pointer to newly created Chest
Chest* MapController::chooseChestItems()
{
	vector<string> itemName = getFilesInsideFolderNoExtension("SaveFiles/Items");
	vector<Item*> chosenItems;
	string userInputStr = "0";
	while (userInputStr != "-1"){

		cout << "\nEnter the index of the item name you want to add to the chest.(Enter -1 to stop adding to the chest)" << endl;
		int userChoice = 0;
		int index = 0;

		for (auto c : itemName){
			cout << index << ": " << c << endl;
			index++;
		}
		cin >> userInputStr;
		try{
			userChoice = stoi(userInputStr);
			if (userChoice > itemName.size() || userChoice < -1){
				cout << "Invalid input. Use listed indices." << endl;
				continue;
			}
			chosenItems.push_back(readItemFile(itemName[userChoice]));

		}
		catch (...){
			cout << "Invalid input.Try a different input" << endl;
			continue;
		}
	}
	return new Chest(chosenItems);

}

//! Prompts the user to choose the name of the enemy that will be added to the map
//! @return the name of the chosen enemy
string MapController::chooseEnemy()
{
	vector<string> characterNames = getFilesInsideFolderNoExtension("SaveFiles/Characters");
	string userInputStr = "0";
	while (userInputStr != "-1"){

		cout << "\nEnter the index of the character name you want to add to the map." << endl;
		int userChoice = 0;
		int index = 0;

		for (auto c : characterNames){
			cout << index << ": " << c << endl;
			index++;
		}
		cin >> userInputStr;
		try{
			userChoice = stoi(userInputStr);
			if (userChoice >(int) characterNames.size() || userChoice < 0){
				cout << "Invalid input. Use listed indices." << endl;
				continue;
			}
			return characterNames[userChoice];

		}
		catch (...){
			cout << "Invalid input.Try a different input" << endl;
			continue;
		}
	}
}

//! Method to save a character
//! @return -
void MapController::saveMap() {
	ofstream outMapFile("SaveFiles/Maps/" + currentMap->getName() + ".txt");
	outMapFile << currentMap->serializeMapToString(); //! Call serialize method for the map to save it
	outMapFile.close();

	cout << "Map was Saved!" << endl;
}

//! Method to read a map from a file
//! @return true if loaded properly, false otherwise
bool MapController::cacheMap() {
	string mapEditName;
	string mapFileLocation;

	ifstream mapFile;
	mapFile.open("");
	int couldNotFindMap = 0;
	while (!mapFile) {
		cout << "Enter the name of the map you would like to edit." << endl;

		//! Display a list of all the saved map files available
		cout << "Here is a list of all the existing maps:" << endl;
		vector<string> allFiles = getFilesInsideFolderNoExtension("SaveFiles\\Maps");
		for (string& file : allFiles)
		{
			cout << file << endl;
		}

		//! Prompt for the name of the map
		cout << "Enter the name: ";
		cin >> mapEditName;

		//! Retrieve the map
		mapFileLocation = "SaveFiles/Maps/" + mapEditName + ".txt";
		mapFile.open(mapFileLocation);

		//! If name is not correct
		if (!mapFile) {
			cout << "Could not find map, try a different name.\nEnter 0 to continue.\nEnter -1 to quit." << endl;
			cin >> couldNotFindMap;
			if (couldNotFindMap == -1) {
				break;
			}
		}
	}
	mapFile.close();
	if (couldNotFindMap != -1) {
		/*if (currentMap != nullptr) {
		delete currentMap;
		}*/

		//#####read map info
		currentMap = readMapFile(mapFileLocation, mapEditName); //! read the map info
		return true;
	}
	else {
		return false;
	}
}

//! Method to read a map from a file
//! @param string location of the file
//! @param string name of the map
//! @return pointer to a map object
Map* readMapFile(string mapFileLocation, string mapName) {
	string fileLine;
	ifstream mapFile;
	mapFile.open(mapFileLocation); //! Open the file for reading

	if (mapFile.fail())
	{
		mapFile.close();
		return nullptr;
	}

	getline(mapFile, fileLine);
	int newWidth = stoi(fileLine);
	getline(mapFile, fileLine);
	int newHeight = stoi(fileLine);

	int tmpX;
	int tmpY;
	Map* tmpMap = new Map(newWidth, newHeight, mapName); //! Make a temporary pointer to a map

	//! Read each element the way it was stored int the file
	while (!mapFile.eof()){
		getline(mapFile, fileLine);
		if (fileLine == "start") {
			//cout << "FOUND start" << endl;
			getline(mapFile, fileLine);
			tmpX = stoi(fileLine);
			getline(mapFile, fileLine);
			tmpY = stoi(fileLine);
			tmpMap->setStartPoint(tmpX, tmpY);
		}
		else if (fileLine == "end") {
			//cout << "FOUND end" << endl;

			getline(mapFile, fileLine);
			tmpX = stoi(fileLine);
			getline(mapFile, fileLine);
			tmpY = stoi(fileLine);
			tmpMap->setEndPoint(tmpX, tmpY);
		}
		else if (fileLine == "wall") {
			//cout << "FOUND wall" << endl;

			getline(mapFile, fileLine);
			tmpX = stoi(fileLine);
			getline(mapFile, fileLine);
			tmpY = stoi(fileLine);
			tmpMap->setTileType(tmpX, tmpY, TileType::WALL);
		}

		else if (fileLine == "enemy") {
			//cout << "FOUND enenmy" << endl;
			getline(mapFile, fileLine);
			CharacterElement characterElement(fileLine, new AggressorStrategy());
			getline(mapFile, fileLine);
			tmpX = stoi(fileLine);
			getline(mapFile, fileLine);
			tmpY = stoi(fileLine);
			tmpMap->setElementAt(tmpX, tmpY, characterElement);
		}
		else if (fileLine == "ally") {
			//cout << "FOUND ally" << endl;
			getline(mapFile, fileLine);
			CharacterElement characterElement(fileLine, new FriendlyStrategy());
			getline(mapFile, fileLine);
			tmpX = stoi(fileLine);
			getline(mapFile, fileLine);
			tmpY = stoi(fileLine);
			tmpMap->setElementAt(tmpX, tmpY, characterElement);
		}
		else if (fileLine == "chest") {
			//cout << "FOUND chest" << endl;
			getline(mapFile, fileLine);
			int itemAmount = stoi(fileLine);
			vector<Item*> tmpItemVec;
			for (int i = 0; i < itemAmount; i++){
				getline(mapFile, fileLine);
				tmpItemVec.push_back(readItemFile(fileLine));
			}

			getline(mapFile, fileLine);
			tmpX = stoi(fileLine);
			getline(mapFile, fileLine);
			tmpY = stoi(fileLine);
			tmpMap->setElementAt(tmpX, tmpY, Chest(tmpItemVec));
		}

	}
	//cout << "PRINT" << endl;
	mapFile.close();
	//cout<< tmpMap->print()<<endl;
	return tmpMap;
}

//! Method to quit while creating or ediing a map
//! @return -
void MapController::quit()
{
	if (currentMap->isValid()) { //! Check if map is valid before saving
		saveMap();
	}
	else {
		cout << "\nMap is not valid. All changes are discarded." << endl;
	}
	delete currentMap;
	system("pause");
}