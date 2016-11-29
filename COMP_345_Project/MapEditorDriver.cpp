//! @file Main.cpp
//! @brief driver for testing

//! The structure of the program works as such: there are 2 controller classes,
//! a Map controller and a Campaign Controller. These 2 classes points to their respective objects.
//! Map controller points to a map object, the campaign controller points to a campaign object.
//! The idea behind the 2 controllers are to wrap their respective objects to simplify function calls
//! for the UI. You basically call one function of the controller object to automatically call multiple
//! functions of the original object (along with UI prompts).
//! There will always only be one controller object of each type: 1 Map Controller object and 1 Campaign Controller object for
//! the entire program.


//! Note: disregard Character, Enums, Fighter, Buff, Item, ItemContainer, Weapon classes.
//! These are classes from assignment one and are only there as place holder.
//! Map, Position, Element, Tile classes are also from assignment 1 but were modified to work with this assignment.

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <stdio.h>
#include "MapController.h"
#include "CampaignController.h"
#include "Item.h"
#include "Weapon.h"
#include "ItemContainer.h"
#include "MapEditorDriver.h"
#include "GameController.h"
#include "ItemUtils.h"
#include "CharacterController.h"

using namespace std;

//! main() function. Entry point of the program
//! It does the following: 
//! 1. Create a test suite object from the registry as populated by the code in the Test Classes
//! 2. Create a test runner that will execute all the tests in the registry
//! 3. (optionally) sets an outputter that will output the results
//! 4. Run the test cases. 
int main(int argc, char* argv[])
{
	srand(time(0));
//#define CPPTEST
#ifdef CPPTEST

	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),
		std::cerr));
	// Run the tests.
	bool wasSucessful = runner.run();

	//getchar();

#endif // CPPTEST

	//Driver code
	MapController* m1 = new MapController();
	CampaignController* c1 = new CampaignController();
	GameController* g1 = new GameController();
	CharacterController* chr = new CharacterController();

	string userOptionStr;

	cout << "===============================================" << endl;
	cout << "THE" << endl;
	cout << "SOMEWHAT" << endl;
	cout << "COOL" << endl;
	cout << "GAME" << endl;
	cout << "===============================================" << endl << endl;
	
	while (true) {
		cout << "=== OPTIONS ===" << endl;
		cout << "0: Quit" << endl << endl;
		cout << "1: Create a new campaign" << endl;
		cout << "2: Edit a campaign" << endl << endl;

		cout << "3: Create a new map" << endl;
		cout << "4: Edit a map" << endl << endl;

		cout << "5: Create a fighter" << endl;
		cout << "6: Edit a fighter" << endl << endl;

		cout << "7: Create an item" << endl;
		cout << "8: Edit an item" << endl << endl;

		cout << "9: Play" << endl;
		cout <<  "-----------------------------------------------" << endl << endl;
		
		cout << "Select an option:";
		cin >> userOptionStr;
		while (cin.fail())
		{
			cout << "Enter a valid input." << endl << endl;
			cin.clear();
			continue;
		}

		int userOption;
		try {
			userOption = stoi(userOptionStr);
		}
		catch (...) {
			cout << "Enter a valid input." << endl << endl;
			continue;
		}


		if (userOption <= 0)
		{
			delete chr;
			delete m1;
			delete c1;
			return 0;
			break;
		}
		else if(userOption > MAX_OPTIONS){
			cout << "Enter a valid input." << endl << endl;
		}
		else {
			flushConsole();
			switch (userOption) {
			case 1:
				c1->createCampaign();
				break;
			case 2:
				c1->editCampaign();
				break;
			case 3:
				m1->createMap();
				break;
			case 4:
				m1->editMap(false);
				break;
			case 5:
				chr->createCharacter();
				break;
			case 6:
				chr->editCharacter();
				break;
			case 7:
				createItem();
				break;
			case 8:
				editItem();
				break;
			case 9:
				g1->play();
				break;
			}
			flushConsole();
		}
	}
	delete chr;
	delete m1;
	delete c1;
}

void flushConsole()
{
	if (system("CLS"))
	{
		system("clear");
	}
}
