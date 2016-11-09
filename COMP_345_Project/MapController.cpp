#include "MapController.h"
#include "Character.h"
#include "Chest.h"
//#include "FolderUtils.h"
#include <sstream>
#include <fstream>
#include <iostream>

MapController::MapController()
{
	currentMap = NULL;
}
MapController::MapController(Map* currentMap)
{
	this->currentMap = currentMap;
}


MapController::~MapController()
{
	
	//deletion of pointer is already handled
}
Map* MapController::getCurrentMap() {
	return currentMap;
}

void MapController::setCurrentMap(Map* newMap) {
	currentMap = new Map(newMap);
}
void MapController::createMap() {
	//string widthS, heightS;
	int width, height;
	bool isInvalid = false;
	Map * m = nullptr;
	string mapName;
	cout << "Enter the name of new map." << endl;
	cin >> mapName;
	do {

		if (isInvalid)
		{
			cout << "Invalid values!" << endl;
		}

		isInvalid = false;

		cout << "Enter the desired dimensions of the map" << endl;
		cout << "Width: "<<endl;
		cin >> width;
		cout << "Height: " <<endl;
		cin >>height;
		cout << endl;

		//stringstream(widthS) >> width;
		//stringstream(heightS) >> height;

		try {
			m = new Map(width, height, mapName);
		}
		catch (invalid_argument e)
		{
			isInvalid = true;
		}

	} while (isInvalid);

	cout << m->print();

	currentMap = m;
	editMap(true);
}
void MapController::editMap(bool creatingNewMap) {
	if (!creatingNewMap) {
		if (!cacheMap()) {
			return;
		}
	}
	Map* m = currentMap;
	bool isInvalid = false;
	cout << "LEGEND: F Floor, W Wall, X Enemy, C Chest, () Start point, [] End point" << endl;
	cout << "Enter Q at any time to quit the application" << "\n" << endl;

	string xS, yS, eS;
	int x, y;

	while (true) //For as long as the user wants to edit the map
	{
		cout << "Edit a new tile" << endl;
		xS.clear();
		yS.clear();
		eS.clear();
		x = y = -1;

		//Enter Element
		do {
			if (isInvalid)
			{
				cout << "Invalid element!" << endl;
			}

			cout << "Element (S for start point, L for end point, F for Floor, W for Wall, X for enemy, C for Chest, F for floor): ";
			cin >> eS;
			if (eS == "Q")
			{ 
				if (m->isValid()) {
					saveMap();
				}
				else {
					cout << "\nMap is not valid. All changes are discarded." << endl;
				}
				delete m;
				return;
			}

			isInvalid = eS != "S" && eS != "L" && eS != "F" && eS != "W" && eS != "X" && eS != "C" && eS != "F";
		} while (isInvalid);

		//Enter X
		do {
			if (isInvalid)
			{
				cout << "Invalid X!" << endl;
			}

			cout << "X: ";
			cin>> xS;

			if (xS == "Q")
			{
				if (m->isValid()) {
					saveMap();
				}
				else {
					cout << "\nMap is not valid. All changes are discarded." << endl;
				}
				delete m;
				return;
			}
			stringstream(xS) >> x;

			isInvalid = x < 0;
		} while (isInvalid);

		//Enter Y
		do {
			if (isInvalid)
			{
				cout << "Invalid Y!" << endl;
			}

			cout << "Y: ";
			cin >> yS;

			if (yS == "Q")
			{
				if (m->isValid()) {
					saveMap();
				}
				else {
					cout << "\nMap is not valid. All changes are discarded." << endl;
				}
				delete m;
				return;
			}
			stringstream(yS) >> y;

			isInvalid = y < 0;
		} while (isInvalid);

		bool success = false;

		//Actions performed based on the element type
		if (eS == "S") //Start point
		{
			success = m->setStartPoint(x, y);
		}
		else if (eS == "L") //End point
		{
			success = m->setEndPoint(x, y);
		}
		else if (eS == "F") //Floor
		{
			success = m->setTileType(x, y, Type::FLOOR);
		}
		else if (eS == "W") //Wall
		{
			success = m->setTileType(x, y, Type::WALL);
		}
		else if (eS == "X") //Enemy
		{
			Character * e = new Character();
			success = m->setElementAt(x, y, *e);
			delete e;
		}
		else if (eS == "C") //Chest
		{
			Chest * e = new Chest();
			success = m->setElementAt(x, y, *e);
			delete e;
		}
		else if (eS == "F")//floor
		{
			success = m->removeElementAt(x, y);
		}
		//Action result
		if (success) //If the tile was successfully edited
		{
			cout << "The action was SUCCESFULLY performed" << endl;
		}
		else //The was an issue during the tile edition
		{
			cout << "The action was NOT performed due to an INVALID parameter" << endl;
		}

		cout << m->print() << endl;
		cout << "Map validity: " << (m->isValid() ? "VALID" : "INVALID") << endl << endl;
	}


}
void MapController::saveMap() {
	ofstream outMapFile("SaveFiles/Maps/"+currentMap->getName()+".txt");
	outMapFile << currentMap->serializeMapToString();
	outMapFile.close();

	cout << "Map was Saved!" << endl;
}
bool MapController::cacheMap() {
	string mapEditName;
	string mapFileLocation;

	ifstream mapFile;
	mapFile.open("");
	int couldNotFindMap = 0;
	while (!mapFile) {
		cout << "Enter the name of the map you would like to edit." << endl;

		cout << "Here is a list of all the existing maps:" << endl;
		//vector<string> allFiles = getAllFilesInsideFolder("SaveFiles\\Maps");
		//for (string& file : allFiles)
		//{
			//cout << file << endl;
		//}

		cin >> mapEditName;
		cout << mapEditName << endl;

		mapFileLocation = "SaveFiles/Maps/" + mapEditName + ".txt";
		mapFile.open(mapFileLocation);

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
		currentMap = readMapFile(mapFileLocation, mapEditName);
		return true;
	}
	else {
		return false;
	}
}
Map* MapController::readMapFile(string mapFileLocation, string mapName) {
	string fileLine;
	ifstream mapFile;
	mapFile.open(mapFileLocation);

	getline(mapFile, fileLine);
	int newWidth = stoi(fileLine);
	getline(mapFile, fileLine);
	int newHeight = stoi(fileLine);

	int tmpX;
	int tmpY;
	Map* tmpMap = new Map(newWidth, newHeight, mapName);
	
	while(!mapFile.eof()){
		getline(mapFile, fileLine);
		if (fileLine == "start") {
			//cout << "FOUND start" << endl;
			getline(mapFile, fileLine);
			tmpX = stoi(fileLine);
			getline(mapFile, fileLine);
			tmpY= stoi(fileLine);
			tmpMap->setStartPoint(tmpX,tmpY);
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
			tmpMap->setTileType(tmpX, tmpY, WALL);
		}

		else if (fileLine == "enemy") {
			//cout << "FOUND enenmy" << endl;

			getline(mapFile, fileLine);
			tmpX = stoi(fileLine);
			getline(mapFile, fileLine);
			tmpY = stoi(fileLine);
			tmpMap->setElementAt(tmpX, tmpY, Character());
		}
		else if (fileLine == "chest") {
			//cout << "FOUND chest" << endl;

			getline(mapFile, fileLine);
			tmpX = stoi(fileLine);
			getline(mapFile, fileLine);
			tmpY = stoi(fileLine);
			tmpMap->setElementAt(tmpX, tmpY, Chest());
		}

	}
	//cout << "PRINT" << endl;
	mapFile.close();
	cout<< tmpMap->print()<<endl;
	return tmpMap;
}