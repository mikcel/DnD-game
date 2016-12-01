//! @file 
//! @brief Implementation file for the MapTest class  
//!

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
#include "MapTest.h"
#include "Map.h"
#include "MapObserver.h"
using namespace CppUnit;	

//! method called before every test case in this test class
/*Generates the following map:
	0 1 2 3 4
0	F W W F F
1	W W W F F
2	F F W F F
3	F F W F F
4	F F F F F
*/
void MapTest::setUp()
{

	map = new Map(5,5,"");
	map->setTileType(0, 2, TileType::WALL);
	map->setTileType(1, 2, TileType::WALL);
	map->setTileType(2, 2, TileType::WALL);
	map->setTileType(3, 2, TileType::WALL);
	
	map->setTileType(0, 1, TileType::WALL);
	map->setTileType(1, 1, TileType::WALL);
	map->setTileType(1, 0, TileType::WALL);

}

//! method called after every test case in this test class
void MapTest::tearDown()
{
	delete map;
}

//! test method to test the isFree() and isTraversible() method of the Map class 
//! Test Case: the returned value should be false for isFree but true for isTraversible after filling the cell
//! Tested item: Map::isFree() Map::isTraversible()
void MapTest::testMapCellContainsElement()
{
	// context: fill a cell
	map->setElementAt(2, 1, Element());

	//test: isFree() should return false after the cell having been filled
	CPPUNIT_ASSERT(false == map->isFree(2, 1));
	//test: isTraversible() should return true after the cell having been filled
	CPPUNIT_ASSERT(true == map->isTraversible(2, 1));
}

//! test method to test the isFree() and isTraversible() method of the Map class 
//! Test Case: the returned value should be false after filling the cell
//! Tested item: Map::isFree() Map::isTraversible()
void MapTest::testMapCellContainsWall()
{
	// context: fill a cell
	map->setTileType(1, 1, TileType::WALL);
	//test: isFree() should return true after the cell having been set to a wall
	CPPUNIT_ASSERT(true == map->isFree(1, 1));
	//test: isTraversible() should return false after the cell having been set to a wall
	CPPUNIT_ASSERT(false == map->isTraversible(1, 1));
}

//! test method to test the isFree() and isTraversible() method of the Map class 
//! Test Case: the returned value should be false for isFree() after filling the FLOOR cell but true for isTraversible()
//!			   the returned value should be true for both functions after emptying the FLOOR cell
//! Tested item: Map::isFree(), Map::isTraversible()
void MapTest::testMapCellEmpty()
{
	// context: make a cell containing an element
	map->setElementAt(2, 1,*(new Element()));
	// test: isFree() should return false if the cell was filled
	//		and isTraversible should be true as it 
	CPPUNIT_ASSERT(false == map->isFree(2, 1));
	CPPUNIT_ASSERT(true == map->isTraversible(2, 1));

	map->removeElementAt(2, 1);
	// test: isOoccupied() should return false if the cell was not filled
	CPPUNIT_ASSERT(true == map->isFree(2, 1));
	CPPUNIT_ASSERT(true == map->isTraversible(2, 1));
}

//! test method to test the isValid() method of the Map class
//! Test Case: the returned value should be false as there is no entry point
//! Tested item: Map::isValid()
void MapTest::testInvalidPathNoEntry()
{
	map->setEndPoint(4, 4);
	CPPUNIT_ASSERT(false == map->isValid());
}

//! test method to test the isValid() method of the Map class
//! Test Case: the returned value should be false as there is no exit point
//! Tested item: Map::isValid()
void MapTest::testInvalidPathNoExit()
{
	map->setStartPoint(4, 4);
	CPPUNIT_ASSERT(false == map->isValid());
}

//! test method to test the isValid() method of the Map class
//! Test Case: the returned value should be false as the entry point is on a wall
//! Tested item: Map::isValid()
void MapTest::testInvalidPathEntryOnWall()
{
	map->setTileType(1, 1, TileType::WALL);
	map->setStartPoint(1, 1);
	map->setEndPoint(4, 4);
	CPPUNIT_ASSERT(!map->isValid());
}

//! test method to test the isValid() method of the Map class
//! Test Case: the returned value should be false as the exit point is on a wall
//! Tested item: Map::isValid()
void MapTest::testInvalidPathExitOnWall()
{
	map->setTileType(1, 1, TileType::WALL);
	map->setStartPoint(4, 4);
	map->setEndPoint(1, 1);
	CPPUNIT_ASSERT(!map->isValid());
}

//! test method to test the isValid() method of the Map class
//! Test Case: Test Case: the returned value should be false as there is no valid path from the start to the end
//! Tested item: Map::isValid()
void MapTest::testInvalidPath()
{
	map->setStartPoint(2, 0);
	map->setEndPoint(0, 4);

	map->setTileType(4, 2, TileType::WALL); //We block off the only passage
	CPPUNIT_ASSERT(!map->isValid());
}

//! test method to test the isValid() method of the Map class
//! Test Case: the returned value should be true if there is a valid path in the map
//! Tested item: Map::isValid()
void MapTest::testValidPath()
{
	map->setStartPoint(2, 0);
	map->setEndPoint(0, 4);

	CPPUNIT_ASSERT(map->isValid());
}

//! test method to test the setElementAt() and removeElementAt() methods of the Map class
//! Test Case: The element once added is equal to the element added, but with a different pointer.
//!			   The element once deleted returns a null pointer.
//!			   Validates that the characters list is trully the data structure holding the Elements
//! Tested item: Map::setElementAt, getElementAt(), removeElementAt()
void MapTest::testSetRemoveGetElement()
{
	Element e;
	map->setElementAt(0,0, e);

	CPPUNIT_ASSERT(e == *(map->getElementAt(0, 0)));
	CPPUNIT_ASSERT((map->getElements()).back() == map->getElementAt(0, 0)); //! Validates that the characters list is where the Elements are trully held.
	CPPUNIT_ASSERT((map->getElements()).size() == 1);
	CPPUNIT_ASSERT(&e != map->getElementAt(0,0));
	
	map->removeElementAt(0, 0);
	CPPUNIT_ASSERT(map->getElementAt(0, 0) == nullptr);	
	CPPUNIT_ASSERT((map->getElements()).size() == 0);
}

//! test method to test the moveElement()
//! Test Case: The element is added and then moved to a different position.
//!				For the test to be successful the Element must now occupy the tile where it has been moved and still point to the same
//!				Element in the characters list.
//! Tested item: Map::moveElement()
void MapTest::testMoveElement()
{
	Element e;
	map->setElementAt(4, 4, e);

	CPPUNIT_ASSERT((map->getElements()).back() == map->getElementAt(4, 4));
	CPPUNIT_ASSERT((map->getElements()).size() == 1);
	CPPUNIT_ASSERT(map->getElementAt(4, 4) == (map->getElements()).back());
	CPPUNIT_ASSERT(map->getElementAt(3, 4) == nullptr);

	CPPUNIT_ASSERT(map->moveElement(-1,0,*(map->getElements()).back()));
	CPPUNIT_ASSERT((map->getElements()).size() == 1);
	CPPUNIT_ASSERT(map->getElementAt(4, 4) == nullptr);
	CPPUNIT_ASSERT(map->getElementAt(3, 4) == (map->getElements()).back());
}

//! test method to test the moveElement()
//! Test Case: The element is added and then moved to a different position.
//!				For the test to be successful the Element must not move as the new position would be oob.
//! Tested item: Map::moveElement()
void MapTest::testMoveElementOob()
{
	Element e;
	map->setElementAt(0, 0, e);

	CPPUNIT_ASSERT((map->getElements()).back() == map->getElementAt(0, 0));
	CPPUNIT_ASSERT((map->getElements()).size() == 1);

	CPPUNIT_ASSERT(!map->moveElement(-1, 0, *(map->getElements()).back()));
	CPPUNIT_ASSERT((map->getElements()).size() == 1);
	CPPUNIT_ASSERT(map->getElementAt(0, 0) == (map->getElements()).back());
}

//! test method to test the setTileType()
//! Test Case: An element is assigned to a tile. The tile type change destroys the element.
//! Tested item: Map::setTileType()
void MapTest::testSetTileDestroysElement()
{
	Element e;
	map->setTileType(0, 0, TileType::FLOOR);
	CPPUNIT_ASSERT(map->getTileAt(0, 0).getType() == TileType::FLOOR);

	map->setElementAt(0, 0, e);
	CPPUNIT_ASSERT(map->getTileAt(0, 0).getType() == TileType::FLOOR);
	CPPUNIT_ASSERT((map->getElements()).back() == map->getElementAt(0, 0));
	CPPUNIT_ASSERT((map->getElements()).size() == 1);

	map->setTileType(0, 0, TileType::WALL);
	CPPUNIT_ASSERT(map->getTileAt(0, 0).getType() == TileType::WALL);
	CPPUNIT_ASSERT(map->getElementAt(0, 0) == nullptr);
	CPPUNIT_ASSERT((map->getElements()).size() == 0);
}

//! test method to test the Map constructor
//! Test Case: A map is created with a width smaller than 1. An invalid_argument exception is thrown.
//! Tested item: Map::Map(int width, int height)
void MapTest::testConstructorInvalidWidth()
{
	bool isExceptionThrown = false;
	try 
	{
		Map m = Map(-1, 2,"");
	}
	catch (invalid_argument& e) {
		isExceptionThrown = true;
	}
	CPPUNIT_ASSERT(isExceptionThrown);
}

//! test method to test the Map constructor
//! Test Case: A map is created with a height smaller than 1. An invalid_argument exception is thrown.
//! Tested item: Map::Map(int width, int height)
void MapTest::testConstructorInvalidHeight()
{
	bool isExceptionThrown = false;
	try
	{
		Map m(2, -1, "");
	}
	catch (invalid_argument& e) {
		isExceptionThrown = true;
	}
	CPPUNIT_ASSERT(isExceptionThrown);
}

//! test method to test the Map constructor
//! Test Case: A map is created with a size smaller than 2 tiles. An invalid_argument exception is thrown.
//! Tested item: Map::Map(int width, int height)
void MapTest::testConstructorInvalidSize()
{
	bool isExceptionThrown = false;
	try
	{
		Map m(1, 1, "");
	}
	catch (invalid_argument& e) {
		isExceptionThrown = true;
	}
	CPPUNIT_ASSERT(isExceptionThrown);
}

//! test method to test Map Observer pattern
//! Test Case: A map is created and a MapObserver is attached to it. 
//! By changing a value in the map, the notify() and update() functions are called.
//! Tested item: Observable::attach(Observer), Observable::notify()
void MapTest::testObserverModificationCallUpdate()
{
	class MapObserverTest : public Observer
	{
	public :
		int timesInvoked;
		MapObserverTest() : timesInvoked(0) {};
		void update()
		{
			timesInvoked++;
		}
	}mot;

	map->Observable::attach(mot);

	map->setStartPoint(4, 0);
	CPPUNIT_ASSERT(mot.timesInvoked == 1);

	map->unsetStartPoint();
	CPPUNIT_ASSERT(mot.timesInvoked == 2);

	map->setEndPoint(4, 0);
	CPPUNIT_ASSERT(mot.timesInvoked == 3);

	map->unsetEndPoint();
	CPPUNIT_ASSERT(mot.timesInvoked == 4);

	map->setTileType(2, 3, TileType::WALL);
	CPPUNIT_ASSERT(mot.timesInvoked == 5);
	
	Element e;
	Element * e2 = map->setElementAt(4,0, e);
	CPPUNIT_ASSERT(mot.timesInvoked == 6);

	map->moveElement(-1, 0, *e2);
	CPPUNIT_ASSERT(mot.timesInvoked == 7);

	map->removeElementAt(3, 0);
	CPPUNIT_ASSERT(mot.timesInvoked == 8);

	map->setName("Other name");
	CPPUNIT_ASSERT(mot.timesInvoked == 9);
}

//! test method to test Map Observer pattern
//! Test Case: A map is created and a MapObserver is attached to it. 
//! By reading a value in the map, the notify is not called.
//! Tested item: Observable::attach(Observer), Observable::notify()
void MapTest::testObserverReadNoCallUpdate()
{
	class MapObserverTest : public Observer
	{
	public:
		bool wasInvoked;
		MapObserverTest() : wasInvoked(false) {};
		void update()
		{
			wasInvoked = true;
		}
	}mot;

	map->Observable::attach(mot);

	map->isStartPoint(4, 0);
	CPPUNIT_ASSERT(!mot.wasInvoked);

	map->isEndPoint(4, 0);
	CPPUNIT_ASSERT(!mot.wasInvoked);

	map->getTileAt(4, 0);
	CPPUNIT_ASSERT(!mot.wasInvoked);

	map->getElementAt(4, 0);
	CPPUNIT_ASSERT(!mot.wasInvoked);

	map->isFree(4, 0);
	CPPUNIT_ASSERT(!mot.wasInvoked);

	map->isTraversible(4, 0);
	CPPUNIT_ASSERT(!mot.wasInvoked);
	
	map->getElements();
	CPPUNIT_ASSERT(!mot.wasInvoked);

	map->isValid();
	CPPUNIT_ASSERT(!mot.wasInvoked);

	map->print();
	CPPUNIT_ASSERT(!mot.wasInvoked);

	map->getName();
	CPPUNIT_ASSERT(!mot.wasInvoked);
}

//! test method to test that the observers are properly added and removed from the observable's observer's list
//! Test Case: A map is created. It should not have any observers.
//! When an observer is attached, it should properly be added to the observers list.
//! When an observer is detached, it should properly be removed from the observers list.
//! Tested item: Observable::attach(Observer), Observable::detach(Observer), Observable::getObservers()
void MapTest::testObserverAttachDetachObservers()
{

	MapObserver mo(*map);
	CPPUNIT_ASSERT(map->getObservers().size() == 0);

	map->Observable::attach(mo);
	CPPUNIT_ASSERT(map->getObservers().size() == 1);
	CPPUNIT_ASSERT(map->getObservers().front() == &mo);

	map->Observable::detach(mo);
	CPPUNIT_ASSERT(map->getObservers().size() == 0);
}

//! test method to test Map Observer pattern
//! Test Case: A map is created and a MapObserver is attached to it. 
//! When detached, the update function fo the MapObserver is not called anymore
//! Tested item: Observable::attach(Observer), Observable::detach(Observer), Observable::notify(), Observer::update()
void MapTest::testObserverNotNotifiedWhenDetached()
{
	class MapObserverTest : public Observer
	{
	public:
		int timesInvoked;
		MapObserverTest() : timesInvoked(0) {};
		void update()
		{
			timesInvoked++;
		}
	}mot;
	
	map->Observable::attach(mot);
	map->setStartPoint(4, 0);
	CPPUNIT_ASSERT(mot.timesInvoked == 1);

	map->Observable::detach(mot);
	map->unsetStartPoint();
	CPPUNIT_ASSERT(mot.timesInvoked == 1);

	map->Observable::attach(mot);
	map->setEndPoint(4, 0);
	CPPUNIT_ASSERT(mot.timesInvoked == 2);
}