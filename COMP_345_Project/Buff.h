//! @file Buff.h
//! @brief Header file for buff class
//each Buff object will be its own enhancement

#include "Enums.h"

//! class to create Buff objects for the items
class Buff
{
public:
	//! Default constructor
	Buff();
	
	//! Constructor that takes type and amount of buff
	//! @param type: enum type of buff type
	//! @param amount: int of the magnitude of the buff
	
	Buff(buff::buffTypes buffType, int buffAmount);
	//!Destructor, nothing has to be done
	~Buff();

	//!method that returns the type of the buff
	//! return: enum type of the type of the buff
	buff::buffTypes getBuffType();
	
	//! method that returns the magnitude of the buff
	//! return: int of the amount the buff has
	int getBuffAmount();

	//!method that sets the type of a buff
	//! @param type: enum type of buff type
	void setBuffType(buff::buffTypes buffType);

	//!method that sets magnitude of the buff
	//! @param amount: int of the amount of the buff has
	void setBuffAmount(int buffAmount);
private:
	int buffAmount;
	buff::buffTypes buffType;
};

