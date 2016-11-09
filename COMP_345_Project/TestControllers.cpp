//! @file 
//! @brief File containing the Test Class and the Test Methods
//!
#pragma once
#include <iostream>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include "MapController.h"
#include "CampaignController.h"
#include "Chest.h"
#include "Character.h"
using namespace CppUnit;
using namespace std;

//! Test Class for the ItemContainer class
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
class TestControllers : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestControllers);
	CPPUNIT_TEST(testMapSavingLoading);
	CPPUNIT_TEST(testCampaignSavingLoading);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp(void);
	void tearDown(void);
protected:
	void testMapSavingLoading(void);
	void testCampaignSavingLoading(void);
private:
	 MapController* mapController;
	 CampaignController* campaignController;

};

//!Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestControllers);//most important

//! test method to test the map controller I/O
//! Test Case: Reading from the map file should bring back the same name as the original map object
void TestControllers::testMapSavingLoading(void)
{
	Map* map1 = new Map(10, 10, "TestMap");
	map1->setStartPoint(0, 0);
	map1->setEndPoint(5, 5);
	map1->setElementAt(3, 2, Chest());
	map1->setElementAt(4, 2, Character());
	mapController->setCurrentMap(map1);
	mapController->saveMap();
	Map* mapReadFormFile = mapController->readMapFile("SaveFiles/Maps/TestMap.txt", "TestMap");
	CPPUNIT_ASSERT(mapReadFormFile->getName() == map1->getName());//saving and loading was successfull
//	delete map1;
//	delete mapReadFormFile;
}

//! test method to test Campaign controller I/O
//! Test Case: Reading from the campaign file should bring back the same name as the original campaign object
void TestControllers::testCampaignSavingLoading(void)
{
	Campaign* camp1 = new Campaign();
	vector<string>* maps = new vector<string>{ "TestMap1", "TestMap2" };
	camp1->setCampaignName("TestCamp");
	camp1->setCampaignMapNames(maps);
	campaignController->setCurrentCampaign(camp1);
	campaignController->saveCampaign();
	campaignController->setCurrentCampaign(campaignController->readCampaignFile("TestCamp"));
	CPPUNIT_ASSERT(camp1->getCampaignName() == campaignController->getCurrentCampaign()->getCampaignName());
	delete camp1;
	delete maps;
}

//! setUp() method 
void TestControllers::setUp(void)
{
	mapController =new MapController();
	campaignController = new CampaignController();
}

//! tearDown() method
void TestControllers::tearDown(void)
{
	delete mapController;
	delete campaignController;
}
