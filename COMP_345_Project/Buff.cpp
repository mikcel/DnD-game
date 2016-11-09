//! @file Buff.cpp
//! @brief Class implementation of Buff class

#include "Buff.h"

//! Default constructor
Buff::Buff()
{
	buffAmount = 0;
	buffType = buff::buffTypes::ARMOR_CLASS;
}

//! Constructor that takes type and amount of buff
//! @param type: enum type of buff type
//! @param amount: int of the magnitude of the buff
Buff::Buff(buff::buffTypes buffType, int buffAmount)
{	
	if (buffAmount < 1 || buffAmount>5) {
		buffAmount = 1;
	}
	this->buffType = buffType;
	this->buffAmount = buffAmount;
}
//!Destructor, nothing has to be done
Buff::~Buff()
{
}

//! method that returns the magnitude of the buff
//! return: int of the amount the buff has
int Buff::getBuffAmount() 
{
	return buffAmount;
}

//!method that returns the type of the buff
//! return: enum type of the type of the buff
buff::buffTypes Buff::getBuffType()
{
	return buffType;
}

//!method that sets the type of a buff
//! @param type: enum type of buff type
void Buff::setBuffType(buff::buffTypes buffType)
{
	this->buffType = buffType;
}

//!method that sets magnitude of the buff
//! @param amount: int of the amount of the buff has
void Buff::setBuffAmount(int buffAmount)
{	
	if (buffAmount < 1 || buffAmount>5) {
		buffAmount = 1;
	}
	this->buffAmount = buffAmount;
}