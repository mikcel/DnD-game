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

using namespace std;

//! main() function. Entry point of the program
//! It does the following: 
//! 1. Create a test suite object from the registry as populated by the code in the Test Classes
//! 2. Create a test runner that will execute all the tests in the registry
//! 3. (optionally) sets an outputter that will output the results
//! 4. Run the test cases. 
int main(int argc, char* argv[])
{
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
	Item* item1 = new Item(ItemType::BELT, "Leather Belt", vector<Buff>{ Buff(BuffType::CONSTITUTION, 2), Buff(BuffType::CONSTITUTION, 2)});
	Weapon* item2 = new Weapon(ItemType::WEAPON, "Iron Sword", vector<Buff>{ Buff(BuffType::ATTACK_BONUS, 2), Buff(BuffType::DAMAGE_BONUS, 2)}, 1);
	//cout << item1->serializeItem()<<endl;

	ItemContainer* backpack = new ItemContainer(ContainerType::BACKPACK, vector<Item*> {item1, item2});
	//cout << backpack->serializeItemContainer() << endl;

	delete backpack;
	//Driver code
	MapController* m1 = new MapController();
	CampaignController* c1 = new CampaignController();
	GameController* g1 = new GameController();




	string userOptionStr;
	while (true) {
		cout << "Enter the index of option you want to do:" << endl;

		cout << "0: To quit\n1: To create a new campaign\n2: To edit a campaign\n3: To create a new map\n4: To edit a map" << endl;

		cin >> userOptionStr;
		int userOption;
		try {
			userOption = stoi(userOptionStr);
		}
		catch (...) {
			cout << "Enter a valid input." << endl;
			continue;
		}


		if (userOption <= 0)
		{
			delete m1;
			delete c1;
			return 0;
			break;
		}
		//else if(userOption > NBR_OPTIONS){
		//	cout << "Enter a valid input." << endl;
		//}
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
			case 10:
				g1->play();
				break;
			}
			flushConsole();
		}
	}
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
