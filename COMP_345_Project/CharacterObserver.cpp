//! 
//! @file 
//! @brief Implementation file for Character Observer

#include "CharacterObserver.h"
#include "Character.h"
#include <iostream>
using namespace std;

////! Default Constructor
//CharacterObserver::CharacterObserver(){
//	//! Blank by default
//}
//
////! Parametrized constructor
////! @param Character - pointer to character
//CharacterObserver::CharacterObserver(Character& chr){
//
//	_subject = &chr; //! Assign subject
//	_subject->attach(*this); //! Atach this observer to subject
//	display(); //Display the character's stats
//
//}
//
////! Destructor
//CharacterObserver::~CharacterObserver(){
//
//	_subject->detach(*this); //! Deletes the pointer
//
//}
//
////! Update method that calls the display method
//void CharacterObserver::Update(){
//
//	display();
//
//}
//
////! Display method clears the console and display the new Character's stats
//void CharacterObserver::display(){
//
//	system("cls");
//	cout << *_subject;
//
//}