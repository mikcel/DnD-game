//! 
//! @file 
//! @brief Implementation of the Campaign class
//! 

//! 
//! This class allows the creation of a campaign. A campaign contains a vector of Map names.  
//! 

#include "Campaign.h"

//! Default constructor 
Campaign::Campaign()
{
	campaignName = "unspecified"; //! sets campaign name to unspecified 
	campaignMapNames = new vector<string>(0); //! Vector of maps to 0 of size 
}

//! Paramatrized constructor
//! @param string representing campaign name
//! @param string a vector of string of map names
Campaign::Campaign(string campaignName, vector<string>* campaignMapNames) {
	this->campaignName = campaignName; //! Sets campaign name
	this->campaignMapNames = campaignMapNames; //! Sets the vector of maps
 }

//! Destructor
Campaign::~Campaign()
{
	delete campaignMapNames;
}

//! Accessor for vector of map names
//! @return the vector of map names
vector<string>* Campaign::getCampaignMapNames(){
	return campaignMapNames; 
}

//! Accessor for the campaign
//! @return the campaign name
string Campaign::getCampaignName() {
	return campaignName;
}

//! Mutator for the vector of map names
//! @param campaignMapNames vector of map names
void Campaign::setCampaignMapNames(vector<string>* campaignMapNames) {
	vector<string>* tmpVec = new vector<string>(0); //! Make a temporary vector to copy the contents of the vector passed
	for (auto m : *campaignMapNames) {
		tmpVec->push_back(m);
	}
	this->campaignMapNames = tmpVec; //! sets the vector of map names to the temporary vector
}

//! Mutator for the campaign name
//! @param campaignName the new campaign name
void Campaign::setCampaignName(string campaignName) {
	this->campaignName = campaignName;
}