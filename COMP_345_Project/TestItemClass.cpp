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
#include "Weapon.h"
using namespace CppUnit;
using namespace std;

//! Test Class for the ItemContainer class
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
class TestItemClass : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestItemClass);
	CPPUNIT_TEST(testValidItem);
	CPPUNIT_TEST(testInvalidItem);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testValidItem();
	void testInvalidItem();
};

//!Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestItemClass);//most important

//! test method to thest the validateItem() method of the Item class
//! Test Case: calling validateItem() on a valid item should return true 
void TestItemClass::testValidItem()
{	
	Buff b1 = Buff();
	Buff b2 = Buff(BuffType::ATTACK_BONUS, 3);

	b1.setBuffAmount(2);
	b1.setBuffType(BuffType::DAMAGE_BONUS);

	Weapon* i1 = new Weapon();

	i1->setItemType(ItemType::WEAPON);
	i1->setItemName("Iron Axe");
	i1->setBuffs(vector<Buff>{b1, b2});
	i1->setRange(2);
	CPPUNIT_ASSERT(i1->validateItem() == true);
	CPPUNIT_ASSERT(i1->validateWeapon() == true);
	
	delete i1;
}

//! test method to thest the validateItem() method of the Item class
//! Test Case: calling validateItem() on an invalid item should return false 
void TestItemClass::testInvalidItem(void)
{
	Buff b3 = Buff(BuffType::INTELLIGENCE, 4);
	Buff b4 = Buff(BuffType::STRENGTH, 4);

	Item* i2 = new Item(ItemType::ARMOR, "Ice Armor", vector<Buff>{b3, b4});

	CPPUNIT_ASSERT(i2->validateItem() == false);

	delete i2;
}

