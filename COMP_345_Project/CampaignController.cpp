#include "CampaignController.h"
#include "FolderUtils.h"
#include <fstream>


CampaignController::CampaignController()
{
	currentCampaign = new Campaign();
}

CampaignController::~CampaignController()
{
	if (currentCampaign != nullptr) {
		delete currentCampaign;
	}
}

void CampaignController::editCampaign() {
	if (cacheCampaign() == 1) {
		return;
	}
	cout<< "The current campaign status:\nTitle:" << (currentCampaign->getCampaignName())<<"\nMaps:"<<endl;
	vector<string> tempCampNames = *(currentCampaign->getCampaignMapNames());
	for (auto m : tempCampNames) {
		cout << m<<endl;
	}
	cout << "Enter:\n0 To add a new map\n1 To remove a map\n2 To rename the campaign\nEnter any other number to return to menu." << endl;
	string userChoiceString;
	int userChoice;
	cin >> userChoiceString;
	try {
		userChoice = stoi(userChoiceString);
	}
	catch (...) {
		cout << "Invalid input, returning to main menu;" << endl;
		return;
	}
	switch (userChoice) {
	case 0:
		addMap();
		break;
	case 1:
		removeMap();
		break;
	case 2:
		renameCurrentCampaign();
		break;
	}
	saveCampaign();
}

void CampaignController::createCampaign(){
		string campName;
		cout << "Enter the name of the campaign you want to create." << endl;
		cin >> campName;
		vector<string>* chosenMaps = new vector<string>(0);
		string mapEditName;
		ifstream mapFile;
		int continueTheMapSearch = 0;
		while (continueTheMapSearch != -1) {
			mapFile.open("");
			while (!mapFile) {
				cout << "Enter the name of the map you would like to add to the campaign." << endl;
				
				cout << "Here is a list of all the existing maps:" << endl;
				vector<string> allFiles = getAllFilesInsideFolder("SaveFiles\\Maps");
				for (string& file : allFiles)
				{
					cout << file << endl;
				}

				cin >> mapEditName;
				mapFile.open("SaveFiles/Maps/" + mapEditName + ".txt");

				if (!mapFile) {
					cout << "Map does not exist. Would you like to try a new file name?\nEnter 0 to continue\nEnter -1 to quit." << endl;
					cin >> continueTheMapSearch;
					if (continueTheMapSearch == -1) {
						break;
					}
				}
				else {
					chosenMaps->push_back(mapEditName);
					cout << "Map has been added to campaign. Would you like to add a new map?\nEnter 0 to continue\nEnter -1 to quit." << endl;
					cin >> continueTheMapSearch;
					if (continueTheMapSearch == -1) {
						break;
					}
				}
				mapFile.close();
			}
		}
		if (currentCampaign != NULL) {
			delete currentCampaign;
		}
		currentCampaign = new Campaign(campName, chosenMaps);
		cout << "New campaign created:\n" << currentCampaign->getCampaignName() << "\nMaps: "<< endl;
		for (auto m : *(currentCampaign->getCampaignMapNames())) {
			cout << m << endl;
		}
		saveCampaign();
}


Campaign* CampaignController::getCurrentCampaign() {
	return currentCampaign;
}

void CampaignController::setCurrentCampaign(Campaign* currentCampaign) {
	this->currentCampaign->setCampaignMapNames(currentCampaign->getCampaignMapNames());
	this->currentCampaign->setCampaignName((currentCampaign->getCampaignName()));
}

void CampaignController::renameCurrentCampaign()
{
	cout << "Enter the name you want to give to the campaign." << endl;
	string campName;
	cin >> campName;
	currentCampaign->setCampaignName(campName);
	cout << "Name updated: " << campName << endl;

}

int CampaignController::cacheCampaign() {
	string campEditName;
	ifstream campFile;
	campFile.open("");
	int couldNotFindCamp = 0;
	while (!campFile) {
		cout << "Enter the name of the campaign you would like to edit." << endl;
		cin >> campEditName;
		campFile.open("SaveFiles/Campaigns/" + campEditName + ".txt");

		if (!campFile) {
			cout << "Could not find campaign, try a different name.\nEnter 0 to continue.\nEnter -1 to quit." << endl;
			string couldNotFindCampStr;
			cin >> couldNotFindCampStr;
			
			try {
				couldNotFindCamp = stoi(couldNotFindCampStr);
			}
			catch (...) {
				cout << "Invalid input, returning to main menu;" << endl;
				return 1;
			}
			if (couldNotFindCamp == -1) {
				break;
			}
		}
	}
	campFile.close();
	if (couldNotFindCamp != -1) {
		if (currentCampaign != NULL) {
			delete currentCampaign;
		}
		 currentCampaign = readCampaignFile(campEditName);
		return 0;
	}
	else {
		return 1;
	}
}

Campaign* CampaignController::readCampaignFile(string campEditName)
{
	ifstream campFile;
	campFile.open("SaveFiles/Campaigns/" + campEditName + ".txt");
	vector<string>* tempMapNamesVect = new vector<string>(0);
	string tempMapName;
	while (!campFile.eof()) {
		getline(campFile, tempMapName);
		if (tempMapName != "") {
			tempMapNamesVect->push_back(tempMapName);
		}
	}
	

	return new Campaign(campEditName, tempMapNamesVect);
}
void CampaignController::addMap()
{
	cout << "Current map list:" << endl;
	int i = 0;
	for (auto m : *(currentCampaign->getCampaignMapNames())) {
		cout << i << ": "<< m << endl;
		i++;
	}

	cout << "\nEnter at which index you wish to add the new map.\nEnter 0 to continue.\nEnter -1 to quit." << endl;
	int indexToAdd;
	cin >> indexToAdd;
	if (indexToAdd <0 || indexToAdd> currentCampaign->getCampaignMapNames()->size())
	{
		return;
	}

	string mapEditName;
	ifstream mapFile;
	int continueTheMapSearch=0;
	while(continueTheMapSearch != -1){
		mapFile.open("");
		while (!mapFile) {
			cout << "Enter the name of the map you would like to add to the campaign." << endl;
			cin >> mapEditName;
			mapFile.open("SaveFiles/Maps/" + mapEditName + ".txt");
			if (!mapFile) {
				cout << "Map does not exist. Would you like to try a different map name?\nEnter 0 to continue.\nEnter -1 to quit." << endl;
				cin >> continueTheMapSearch;
				if (continueTheMapSearch == -1) {
					break;
				}
			}
			else {
				currentCampaign->getCampaignMapNames()->insert(currentCampaign->getCampaignMapNames()->begin() + indexToAdd, mapEditName);
//				currentCampaign->getCampaignMapNames()->push_back(mapEditName);
				cout << "Map has been added to campaign. Would you like to add a new map?\nEnter 0 to continue.\nEnter -1 to quit." << endl;
				cin >> continueTheMapSearch;
				if (continueTheMapSearch == -1) {
					break;
				}
			}
			mapFile.close();
		}
	}
		cout << "Update campaign:" << endl;
		for (auto m : *(currentCampaign->getCampaignMapNames())) {
			cout << m << endl;
		}

}
void CampaignController::removeMap()
{
	int userChoice = 0;
	do {
		int i = 0;
		for (auto m : *currentCampaign->getCampaignMapNames()) {
			cout << i << ": " << m << endl;
			i++;
		}
		cout << "\nEnter the index of the map you wish to remove.\nEnter -1 to exit." << endl;
		int indexToRemove;
		cin >> indexToRemove;
		if(indexToRemove <0 || indexToRemove> currentCampaign->getCampaignMapNames()->size())
		{
			cout << "Index out of bounds. Action cancelled." << endl;
			return;
		}
		currentCampaign->getCampaignMapNames()->erase(currentCampaign->getCampaignMapNames()->begin() + indexToRemove);

		cout << "Update campaign:" << endl;
		i = 0;
		for (auto m : *currentCampaign->getCampaignMapNames()) {
			cout << i << ": " << m << endl;
			i++;
		}
		cout << "Enter remove another map?\nEnter 0 to continue.\nEnter -1 to quit." << endl;
		cin >> userChoice;
	} while (userChoice == 0);

	
}

void CampaignController::saveCampaign() 
{
	ofstream outputCampaign("SaveFiles/Campaigns/" +currentCampaign->getCampaignName()+".txt");
	for (auto m : *currentCampaign->getCampaignMapNames()) {
		outputCampaign << m << endl;
	}
	cout << "Campaign has been saved!" << endl;
}
