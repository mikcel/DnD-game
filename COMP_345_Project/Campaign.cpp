#pragma once
#include "Campaign.h"


Campaign::Campaign()
{
	campaignName = "unspecified";
	campaignMapNames = new vector<string>(0);
}
Campaign::Campaign(string campaignName, vector<string>* campaignMapNames) {
	this->campaignName = campaignName;
	this->campaignMapNames = campaignMapNames;
 }

Campaign::~Campaign()
{
	delete campaignMapNames;
}

vector<string>* Campaign::getCampaignMapNames(){
	return campaignMapNames;
}
string Campaign::getCampaignName() {
	return campaignName;
}
void Campaign::setCampaignMapNames(vector<string>* campaignMapNames) {
	vector<string>* tmpVec = new vector<string>(0);
	for (auto m : *campaignMapNames) {
		tmpVec->push_back(m);
	}
	this->campaignMapNames = tmpVec;
}
void Campaign::setCampaignName(string campaignName) {
	this->campaignName = campaignName;
}