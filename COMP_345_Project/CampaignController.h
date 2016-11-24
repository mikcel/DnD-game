//! @file CampaignController.h
//! @brief Class to create a Campaign controller that wraps a Campaign object


#pragma once
#include "Campaign.h"
#include <iostream>

using namespace std;
//! Class to create CampaignControllers that points to a campaign object
class CampaignController
{
public:
	//! Default constructor
	CampaignController();
	//! Destructor
	~CampaignController();
	//! method that prompts user to edit campaign parameters
	void editCampaign();
	//! method that prompts user for parameters to create a campaign
	void createCampaign();
	//! method to get back the pointer to the current campaign.
	//! @return: pointer to campaign object
	Campaign* getCurrentCampaign();
	//! method that sets a copy of the passing object to current campaign.
	//! @param currentCampaign: poiner to a campaign object.
	void setCurrentCampaign(Campaign* currentCampaign);
	//! method that prompts the user to rename the current comapaign.
	void renameCurrentCampaign();
	//! method that will save the campaign to a file (using the campaign name as the file name)
	void saveCampaign();

private:
	//! method that prompts the user to find the campaign files
	//! return: int to signify the state of the cache
	int cacheCampaign();
	//! method that prompts the user to add an existing map to the campaign list
	void addMap();	
	//! method that prompts the user to remove an exisitng map from the campaign list
	void removeMap();
	//! pointer to the campaign currently being editted/created.
	Campaign* currentCampaign;
};

//! method that reads a campaign file and sets it as current campaign
//! @param campEditName: string of file name
//! @return pointer to a newly create campaign object
Campaign* readCampaignFile(string campEditName);