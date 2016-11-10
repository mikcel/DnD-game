//! @file 
//! @brief Header file for the MapTest class 
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
#include "Map.h"
using namespace CppUnit;
using namespace std;

//! Test Class for the Map class
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
class MapTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(MapTest); //declare the test suite
	CPPUNIT_TEST(testMapCellContainsElement);
	CPPUNIT_TEST(testMapCellContainsWall);
	CPPUNIT_TEST(testMapCellEmpty);
	CPPUNIT_TEST(testInvalidPathNoEntry);
	CPPUNIT_TEST(testInvalidPathNoExit);
	CPPUNIT_TEST(testInvalidPathEntryOnWall);
	CPPUNIT_TEST(testInvalidPathExitOnWall);
	CPPUNIT_TEST(testInvalidPath);
	CPPUNIT_TEST(testValidPath);
	CPPUNIT_TEST(testSetRemoveGetElement);
	CPPUNIT_TEST(testMoveElement);
	CPPUNIT_TEST(testMoveElementOob);
	CPPUNIT_TEST(testSetTileDestroysElement);
	CPPUNIT_TEST(testConstructorInvalidWidth);
	CPPUNIT_TEST(testConstructorInvalidHeight);
	CPPUNIT_TEST(testConstructorInvalidSize);
	CPPUNIT_TEST(testObserverModificationCallUpdate);
	CPPUNIT_TEST(testObserverReadNoCallUpdate);
	CPPUNIT_TEST(testObserverAttachDetachObservers);
	CPPUNIT_TEST(testObserverNotNotifiedWhenDetached);
	CPPUNIT_TEST_SUITE_END(); //end the tests declaration
public:
	void setUp();
	void tearDown();
protected:
	void testMapCellContainsElement();
	void testMapCellContainsWall();
	void testMapCellEmpty();
	void testInvalidPathNoEntry();
	void testInvalidPathNoExit();
	void testInvalidPathEntryOnWall();
	void testInvalidPathExitOnWall();
	void testInvalidPath();
	void testValidPath();
	void testSetRemoveGetElement();
	void testMoveElement();
	void testMoveElementOob();
	void testSetTileDestroysElement();
	void testConstructorInvalidWidth();
	void testConstructorInvalidHeight();
	void testConstructorInvalidSize();
	void testObserverModificationCallUpdate();
	void testObserverReadNoCallUpdate();
	void testObserverAttachDetachObservers();
	void testObserverNotNotifiedWhenDetached();
private:
	Map *map;
};

//! Register for running the tests
CPPUNIT_TEST_SUITE_REGISTRATION(MapTest);