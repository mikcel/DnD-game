//! 
//! @file 
//! @brief Header file for the StrategyTest class
//! 

#pragma once

//! @file 
//! @brief Implementation file for the DiceTest class  
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
#include <string>
#include "Game.h"
#include "Item.h"
#include "Character.h"
#include "HumanPlayerStrategy.h"
#include "AggressorStrategy.h"
#include "FriendlyStrategy.h"
#include "CharacterController.h"
#include "MapController.h"

using namespace CppUnit;
using namespace std;

//! Test Class for the Dice class
class StrategyTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(StrategyTest);
	CPPUNIT_TEST(allyTransformsToEnemy); //test the transformation of the ally to an enemy if he is attacked
	CPPUNIT_TEST(allyAndEnemyMovement); //test if the enemies and the allies are moving towards the character
	CPPUNIT_TEST_SUITE_END();
protected:
	void allyTransformsToEnemy();
	void allyAndEnemyMovement();
};
