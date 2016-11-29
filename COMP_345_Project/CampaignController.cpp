//! 
//! @file 
//! @brief Implementation file of the campaign controller
//!

#include "CampaignController.h"
#include "FolderUtils.h"
#include <fstream>

//! Default consructor
CampaignController::CampaignController()
{
	currentCampaign = new Campaign(); //! Create a default campaign
}

//! Destructor
CampaignController::~CampaignController()
{
	if (currentCampaign != nullptr) { //! if current campaign is not null delete the current campaign
		delete currentCampaign;
	}
}

//! Method to edit the Campaign
//! @return -
void CampaignController::editCampaign() {
	cout << "==== CAMPAIGN EDITION ====" << endl << endl;

	if (cacheCampaign() == 1) {
		return;
	}

	cout<< "The current campaign status:\nTitle:" << (currentCampaign->getCampaignName())<<"\nMaps:"<<endl;

	//! get the campaign vector of map names and display to the screen
	vector<string> tempCampNames = *(currentCampaign->getCampaignMapNames());
	for (auto m : tempCampNames) {
		cout << m<<endl;
	}

	//! Display the menu
	cout << "Enter:" << endl;
	cout << "0 - To add a new map" << endl;
	cout << "1 - To remove a map" << endl;
	cout << "2 - To rename the campaign" << endl;
	cout << "Enter any other number to return to menu." << endl;

	string userChoiceString;
	int userChoice;
	cin >> userChoiceString; //! Ask the user for input
	try {
		userChoice = stoi(userChoiceString);
	}
	catch (...) {
		cout << "Invalid input, returning to main menu;" << endl;
		system("pause");
		return;
	}

	//! Check the users choice
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

//! Method to create a Campaign
//! @return -
void CampaignController::createCampaign(){
		cout << "==== CAMPAIGN CREATION ====" << endl << endl;
		string campName;
		cout << "Enter the name of the campaign you want to create." << endl;
		cin >> campName;
		vector<string>* chosenMaps = new vector<string>(0); //! Vector of chosen maps
		string mapEditName;
		ifstream mapFile;
		int continueTheMapSearch = 0;
		while (continueTheMapSearch != -1) { //! while need to continue searching for map
			mapFile.open("");
			while (!mapFile) { //! While cannot get one map
				cout << "Enter the name of the map you would like to add to the campaign." << endl;
				
				cout << "Here is a list of all the existing maps:" << endl; //! Show all the available saved maps
				vector<string> allFiles = getFilesInsideFolderNoExtension("SaveFiles\\Maps");
				for (string& file : allFiles)
				{
					cout << file << endl;
				}

				cout << "Enter the name:";
				cin >> mapEditName; //! Ask for map name
				mapFile.open("SaveFiles/Maps/" + mapEditName + ".txt");

				//! Check if map exists or not
				if (!mapFile) {
					//! If map does not exist, ask for new file name
					cout << "Map does not exist. Would you like to try a new file name?\nEnter 0 to continue\nEnter -1 to quit." << endl;
					cin >> continueTheMapSearch;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					if (continueTheMapSearch == -1) {
						break;
					}
				}
				else { //! If map file exists attach it to the campaign
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
		if (currentCampaign != NULL) { //! check if there is a campaign
			delete currentCampaign;
		}

		//! Create campaign for chosen maps and name
		currentCampaign = new Campaign(campName, chosenMaps);
		cout << "New campaign created:\n" << currentCampaign->getCampaignName() << "\nMaps: "<< endl;
		for (auto m : *(currentCampaign->getCampaignMapNames())) {
			cout << m << endl;
		}
		saveCampaign(); //! Save the campaign
}

//! Accessor method for current campaign
//! @return POinter to current campaign
Campaign* CampaignController::getCurrentCampaign() {
	return currentCampaign;
}

//! Setter for current campaign
//! @param currentCampaign pointer of new current campaign
void CampaignController::setCurrentCampaign(Campaign* currentCampaign) {
	this->currentCampaign->setCampaignMapNames(currentCampaign->getCampaignMapNames());
	this->currentCampaign->setCampaignName((currentCampaign->getCampaignName()));
}

//! Method to rename the current campaign
//! @return -
void CampaignController::renameCurrentCampaign()
{
	//! Ask for new name
	cout << "Enter the name you want to give to the campaign." << endl;
	string campName;
	cin >> campName;
	currentCampaign->setCampaignName(campName);
	cout << "Name updated: " << campName << endl;

}

//! Method to ask the user to select a campaign and set the current campaign
//! @return 1 -failure and 0 successful
int CampaignController::cacheCampaign() {
	string campEditName;
	ifstream campFile;
	campFile.open("");
	int couldNotFindCamp = 0;
	while (!campFile) { //! Asks for cmapaign name
		cout << "Enter the name of the campaign you would like to edit." << endl;

		cout << "Here is a list of all the existing campaigns:" << endl;
			//! Show all available file for campaigns
		vector<string> allFiles = getFilesInsideFolderNoExtension("SaveFiles\\Campaigns");
		for (string& file : allFiles)
		{
			cout << file << endl;
		}

		//! Enter the name of the saved file
		cout << "Enter the name:";
		cin >> campEditName;
		campFile.open("SaveFiles/Campaigns/" + campEditName + ".txt");

		if (!campFile) { //! If not correct
			cout << "Could not find campaign, try a different name.\nEnter 0 to continue.\nEnter -1 to quit." << endl;
			string couldNotFindCampStr;
			cin >> couldNotFindCampStr;
			
			try { //! If the name is not correct ask again
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
	//! Loading the current campaign if name is correct
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

//! Method to read a saved campaign file
//! @param campEditName string for file
//! @return pointer to campaign 
Campaign* readCampaignFile(string campEditName)
{
	ifstream campFile;
	campFile.open("SaveFiles/Campaigns/" + campEditName + ".txt");
	if (!campFile){
		return nullptr;
	}
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

//! Method to add map to the current campaign
//! @return -
void CampaignController::addMap()
{
	cout << "Current map list:" << endl;
	int i = 0; //! GEt the current map list in the campaign
	for (auto m : *(currentCampaign->getCampaignMapNames())) {
		cout << i << ": "<< m << endl;
		i++;
	}

	//! Ask for which index to index map
	cout << "\nEnter at which index you wish to add the new map.\nEnter 0 to continue.\nEnter -1 to quit." << endl;
	int indexToAdd;
	cin >> indexToAdd;
	if (indexToAdd <0 || indexToAdd> currentCampaign->getCampaignMapNames()->size())
	{
		return;
	}

	//! Asks for name f the map to add in the campaign at the entered index
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
	//! Show update campaign
		cout << "Update campaign:" << endl;
		for (auto m : *(currentCampaign->getCampaignMapNames())) {
			cout << m << endl;
		}

}

//! Method to remove a map from a campaign
//! @return -
void CampaignController::removeMap()
{
	int userChoice = 0;
	do {
		int i = 0; //! Display all the available maps
		for (auto m : *currentCampaign->getCampaignMapNames()) {
			cout << i << ": " << m << endl;
			i++;
		}
		//! Asks for the index for the map to remove
		cout << "\nEnter the index of the map you wish to remove.\nEnter -1 to exit." << endl;
		int indexToRemove;
		cin >> indexToRemove;
		//! Check index
		if(indexToRemove <0 || indexToRemove> currentCampaign->getCampaignMapNames()->size())
		{
			cout << "Index out of bounds. Action cancelled." << endl;
			return;
		}
		currentCampaign->getCampaignMapNames()->erase(currentCampaign->getCampaignMapNames()->begin() + indexToRemove);
		//! Show updated campaign
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

//! Method to save the campaign
//! @return -
void CampaignController::saveCampaign() 
{
	//! Put the campaign and all maps name in the file to save
	ofstream outputCampaign("SaveFiles/Campaigns/" +currentCampaign->getCampaignName()+".txt");
	for (auto m : *currentCampaign->getCampaignMapNames()) {
		outputCampaign << m << endl;
	}
	cout << "Campaign has been saved!" << endl;
}
