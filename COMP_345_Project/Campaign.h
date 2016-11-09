//! @file Campaign.h
//! @brief Class to define Campaign Objects that will list Maps
#pragma once
#include "Map.h"
#include <vector>

//! Class to create Campaigns.
class Campaign
{
public:
	//! Default constructor
	Campaign();
	//! Constructor
	//! @param campaignName: string of the campaign name/filename
	//! @param campaignMapNames: pointer to a vector of strings that are the name of the maps the user wants to include in the campaign.
	Campaign(string campaignName, vector<string>* campaignMapNames);
	//! Destructor
	~Campaign();
	//! method that returns the pointer of the vector of map names
	//! @return: pointer to a vector of strings
	vector<string>* getCampaignMapNames();
	//! method that returns the name of the campaign
	//! @return: string
	string getCampaignName();
	//! method that sets a copy of the names of the map the user wants to include in the campaign.
	//! @param campaignMapNames: pointer of a vector of strings
	void setCampaignMapNames(vector<string>* campaignMapNames);
	//! method that sets a string as the campaign name
	//! @param  campaignName: string
	void setCampaignName(string campaignName);
private:
	//! Map Names of the Campaign
	vector<string>* campaignMapNames;
	//! Campaign Name
	string campaignName;
};


