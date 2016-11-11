//!
//! @file 
//! @brief Implementation file for Chest class
//!

//!
//! The chest is a subkind of item container. It inherits from the item container a vector for stored items.
//! It has the ability to clone itself and takes a vector of items. The chest 
//! 

#include "Chest.h"
#include "ItemContainer.h"

//! Default constructor
Chest::Chest()
{
	ItemContainer(ContainerType::CHEST, vector<Item*>(0)); //! Create an empty item container of type chest
}

//! Copy constructor
//! @param chest a reference to chest
Chest::Chest(Chest &chest): ItemContainer(ContainerType::CHEST, chest.getContents()) {

	//! Call the copy constructor of the item container to copy the chest contents
}

//! Parametrized constructor
//! @param vectorOfItems contents of the chest
Chest::Chest(vector<Item*> vectorOfItems) : ItemContainer(ContainerType::CHEST, vectorOfItems)
{

}

//! Destructor
Chest::~Chest()
{
}

//! Method to clone the chest
Chest* Chest::clone()
{
	return new Chest(*this);
}

//! Overload output stream operator for  achest
ostream& operator<<(ostream& stream, const Chest& chst){

	cout << "==== CHEST ====\n";
	const ItemContainer& chr = chst; //! cast the chest to item container reference and output the contents
	stream << chr;
	return stream;

}

//Prints the output of a chest
const std::string Chest::print() const {
	return "C";
}