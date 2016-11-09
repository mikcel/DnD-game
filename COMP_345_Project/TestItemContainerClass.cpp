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
#include "ItemContainer.h"
#include "Weapon.h"
#include "Enums.h"
using namespace CppUnit;
using namespace std;


//! Test Class for the ItemContainer class
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
class TestItemContainerClass : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestItemContainerClass);
	CPPUNIT_TEST(testAddItem);
	CPPUNIT_TEST(testGetItem);
	CPPUNIT_TEST(testValidItem);
	CPPUNIT_TEST(testInvalidItem);
	CPPUNIT_TEST(testEquipItem);
	CPPUNIT_TEST(testUnequipItem);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp(void);
	void tearDown(void);
protected:
	void testAddItem(void);
	void testGetItem(void);
	void testValidItem(void);
	void testInvalidItem(void);
	void testEquipItem(void);
	void testUnequipItem(void);
private:
	ItemContainer *ItemContainerObject;

};

//!Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestItemContainerClass);//most important

//! test method to test the AddItem() method of the ItemContainer class 
//! Test Case: the size of the container is increased by one after adding an item to it
void TestItemContainerClass::testAddItem(void)
{
	Item* i1 = new Item(ItemType::BELT, "Leather Belt", vector<Buff>{ Buff(BuffType::CONSTITUTION, 2), Buff(BuffType::CONSTITUTION, 2)});
	
	ItemContainer* c1 = new ItemContainer();
	c1->addItem(i1);
	CPPUNIT_ASSERT(c1->getContents().size() == 1); 
	delete c1;
	
}

//! test method to test the GetItem() method of the ItemContainer class 
//! Test Case: if we put an item of a certain type in the container,
//! getItem() will return this object
void TestItemContainerClass::testGetItem(void)
{
	
	Item* i1 = new Item(ItemType::BELT, "Leather Belt", vector<Buff>{Buff(BuffType::CONSTITUTION, 2), Buff(BuffType::CONSTITUTION, 2)});
	Weapon* i2 = new Weapon(ItemType::WEAPON, "Iron Sword", vector<Buff>{ Buff(BuffType::ATTACK_BONUS, 2), Buff(BuffType::DAMAGE_BONUS, 2)}, 1);
	ItemContainer* c1 = new ItemContainer(ContainerType::BACKPACK, vector<Item*> {i1, i2});
	string name = c1->getItem("Iron Sword")->getItemName();
	CPPUNIT_ASSERT(name.compare("Iron Sword") == 0);
	delete c1;
}

//! test method to thest the validateItem() method of the Item class
//! Test Case: calling validateItem() on a valid item should return true 
void TestItemContainerClass::testValidItem(void)
{
	Buff b1 =  Buff();
	Buff b2 = Buff(BuffType::ATTACK_BONUS, 3);

	b1.setBuffAmount(2);
	b1.setBuffType(BuffType::DAMAGE_BONUS);

	Weapon* i1 = new Weapon();

	i1->setItemType(ItemType::WEAPON);
	i1->setItemName("Iron Axe");
	vector<Buff> buffs1{ b1,b2 };
	i1->setBuffs(buffs1);
	i1->setRange(2);
	CPPUNIT_ASSERT(i1->validateItem() == true);
	CPPUNIT_ASSERT(i1->validateWeapon() == true);
	delete i1;
}

//! test method to test the validateItem() method of the Item class
//! Test Case: calling validateItem() on an invalid item should return true 
void TestItemContainerClass::testInvalidItem(void)
{
	Buff b3 = Buff(BuffType::INTELLIGENCE, 4);
	Buff b4 = Buff(BuffType::INTELLIGENCE, 4);

	Item* i2 = new Item(ItemType::ARMOR, "Ice Armor", vector<Buff>{b3, b4});

	CPPUNIT_ASSERT(i2->validateItem() == false);

	delete i2;
}

//! test method to test equipping an item from backpack to worn items
//! Test Case: calling equipItem() and the item should no longer be in the backpaack but rather in the worn items
void TestItemContainerClass::testEquipItem(void) {
	//new objects
	Item* i1 = new Item(ItemType::BELT, "Leather Belt", vector<Buff>{ Buff(BuffType::CONSTITUTION, 2), Buff(BuffType::CONSTITUTION, 2)});
	Weapon* i2 = new Weapon(ItemType::WEAPON, "Iron Sword", vector<Buff>{ Buff(BuffType::ATTACK_BONUS, 2), Buff(BuffType::DAMAGE_BONUS, 2)}, 1);
	ItemContainer* backpack = new ItemContainer(ContainerType::BACKPACK, vector<Item*> {i1, i2});
	ItemContainer* wornItems = new ItemContainer(ContainerType::WORN_ITEM, vector<Item*>(0));
	//testing that the item is in the original container
	CPPUNIT_ASSERT(backpack->getItem("Iron Sword")->getItemTypes() == ItemType::WEAPON);
	//equip function
	wornItems->equipItem("Iron Sword",backpack);
	//checks to see the object has actually moved
	CPPUNIT_ASSERT(wornItems->getItem("Iron Sword")->getItemName().compare("Iron Sword") == 0);
	CPPUNIT_ASSERT(backpack->getItem("Iron Sword")->getItemTypes() == ItemType::UNSPECIFIED);
	delete backpack;
	delete wornItems;
}

//! test method to test unequipping an item from worn items to backpack
//! Test Case: calling unequipItem() and the item should no longer be in the worn items but rather in the backpack
void TestItemContainerClass::testUnequipItem(void) {
	//instantiating new objects
	Item* i1 = new Item(ItemType::BELT, "Leather Belt", vector<Buff>{ Buff(BuffType::CONSTITUTION, 2), Buff(BuffType::CONSTITUTION, 2)});
	Weapon* i2 = new Weapon(ItemType::WEAPON, "Iron Sword", vector<Buff>{ Buff(BuffType::ATTACK_BONUS, 2), Buff(BuffType::DAMAGE_BONUS, 2)}, 1);
	ItemContainer* backpack = new ItemContainer(ContainerType::BACKPACK, vector<Item*>(0));
	ItemContainer* wornItems = new ItemContainer(ContainerType::WORN_ITEM, vector<Item*> {i1, i2});
	//unequip function call
	wornItems->unequipItem("Iron Sword", backpack);
	//tests
	CPPUNIT_ASSERT(backpack->getItem("Iron Sword")->getItemName().compare("Iron Sword") == 0);
	CPPUNIT_ASSERT(wornItems->getItem("Iron Sword")->getItemTypes() == ItemType::UNSPECIFIED);
	delete backpack;
	delete wornItems;
}


//! setUp() method 
void TestItemContainerClass::setUp(void)
{
	ItemContainerObject = new ItemContainer();
}

//! tearDown() method
void TestItemContainerClass::tearDown(void)
{
	delete ItemContainerObject;
}
