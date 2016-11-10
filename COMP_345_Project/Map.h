//! @file 
//! @brief Header file for the Map class  
//!

#pragma once
#include "Tile.h"
#include "Element.h"
#include "Position.h"
#include <list>
#include <string>
#include "Observable.h"
#include "Player.h"

using namespace std;

//! Represents a map which a player can load and play.
//! The map holds the elements present on the map. The map is represented by a 2D array of tiles. These tiles can contain an element.
//! The actions performed on the tiles are all administered by the map.
//! The map must also contain a start and an end positions which represent where the player will appear when the map loads and where he must go.
//! The coordinate (0,0) is located at the top left corner of the map and the Y increase when going down the map (so bottom right corner is at coordinate (width -1, height -1).
class Map : public Observable
{
public:
	Map(int newWidth, int newHeight, std::string mapName); //! Constructor setting height and width of the map
	Map(Map *map);
	~Map(); //! Destructor

	bool setStartPoint(int x, int y); //! Sets the map starting address
	bool setEndPoint(int x, int y); //! Sets the map ending address
	void unsetStartPoint(); //! Unset the map starting address
	void unsetEndPoint(); //! Unset the map ending address
	bool isStartPoint(int x, int y) const; //! Returns true if the provided address is the one of the start point
	bool isEndPoint(int x, int y) const; //! Returns true if the provided address is the one of the end point

	const Tile& getTileAt(int x, int y) const; //! Gets the tile at the given address
	bool setTileType(int x, int y, TileType type); //! Changes the type of the tile at the given address

	Element* getElementAt(int x, int y) const; //! Gets a pointer to the element held by a tile
	Element* setElementAt(int x, int y, Element& element); //! Set the element of the tile at the given address
	bool moveElement(int xOffset, int yOffset, Element & element); //! Move the element from its current tile to another one based on the offset
	bool removeElementAt(int x, int y); //! Remove the element from the tile at the given address

	bool isFree(int x, int y) const; //! Returns true is the tile at the given address contains an element
	bool isTraversible(int x, int y) const; //! Returns true is the tile type allows a character to cross it

	const std::list<Element*> & getCharacters() const; //! Returns a the reference of the characters list

	Element* placePlayer(Player& newPlayer); //! Places the player at the start point

	bool isValid() const; //! Returns true if there exist a valid path between a start address and an ending address of the map
						  //! This function validates that there are a starting and ending point, that they are placed on a traversible
						  //! address and that there is a path made of traversible tiles from the starting point to the ending point

	std::string print() const; //! Prints a basic outline of the map

	std::string getName() const; //! Gets the name of the map
	void setName(std::string name); //! Sets the name of the map

	string serializeMapToString();
private:
	string name;
	Tile** mapArr; //! 2D Array of the tiles
	int height; //! Height of the map
	int width; //! Width of the map

	bool isStartSet;
	bool isEndSet;
	Position startPoint; //! Position of the start point of the map
	Position endPoint; //! Position of the end point of the map

	Player * player; //! Pointer to the player
	list<Element*> elements; //! List of all the characters in the map

	bool isOob(int x, int y) const; //! Returns true if the provided address is out of bounds
	bool validationRecursive(int x, int y, bool** explorationArray) const; //! Returns true if the address validated is the end point (used by the isValid function)
};
