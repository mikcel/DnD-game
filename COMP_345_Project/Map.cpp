//! @file 
//! @brief Implementation file for the Map class
//!

#include  "Map.h"
#include <typeinfo>
#include "Chest.h"
#include "Character.h"
#include  "Map.h"

using namespace std;
/**
* Initializes a map with a given width, height and name
* @throw invalid_argument if the width is smaller than 1
* @throw invalid_argument if the height is smaller than 1
* @throw invalid_argument if the size of the map is less than 2 tiles
* @param newWidth Map width
* @param newHeight Map height
* @param newName Map name
*/
Map::Map(int newWidth, int newHeight, string newName) : name(newName), width(newWidth), height(newHeight), isStartSet(false), isEndSet(false)
{
	if (newWidth < 1) {
		throw invalid_argument("newWidth must be greater than 0");
	}
	else if (newHeight < 1)
	{
		throw invalid_argument("newHeight must be greater than 0");
	}
	else if (newWidth * newHeight < 2)
	{
		throw invalid_argument("The map size must be at least of 2 tiles");
	}

	mapArr = new Tile*[width];

	for (int i = 0; i < width; ++i)
	{
		mapArr[i] = new Tile[height];
	}

	player = nullptr;
}

Map::Map(Map *map) :Map(width = map->width, height = map->height, name = map->getName())
{
	if (map->isStartSet) {
		startPoint = map->startPoint;
		isStartSet = true;
	}
	else {
		isStartSet = false;
	}
	if (map->isEndSet) {
		endPoint = map->endPoint;
		isEndSet = true;
	}
	else {
		isEndSet = false;
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			mapArr[i][j].setType(map->mapArr[i][j].getType());
			mapArr[i][j].setElement(map->mapArr[i][j].getElement());
		}
	}
}

/**
* Map destructor
*/
Map::~Map()
{
	while (!elements.empty()) delete elements.front(), elements.pop_front();

	for (int i = 0; i < width; ++i)
	{
		delete[] mapArr[i];
	}
	delete[] mapArr;

	delete player;
}

/**
* Set a given position as the start point of the map
* The start point must be on a free and traversible tile, so that it is logical that the player spawns there.
* @param x X coordinate
* @param y Y coordinate
* @return true if the start point was succesfully set
*/
bool Map::setStartPoint(int x, int y)
{
	if (!isFree(x, y) || !isTraversible(x, y) || isEndPoint(x, y)) return false;

	isStartSet = true;


	startPoint.x = x;
	startPoint.y = y;

	notify();
	return true;
}

/**
* Set a given position as the end point of the map.
* The endpoint can be placed on any traversible tile. It does not matter if there is an element on that tile.
* This will allow the creation of a map with a door on the end point of the map. In such a case, the player will
* not be able to navigate to the end point until he/she finds the key to open the door. This will allow a greater variety of objective for a map.
* @param x X coordinate
* @param y Y coordinate
* @return true if the end point was succesfully set
*/
bool Map::setEndPoint(int x, int y)
{
	if (!isTraversible(x, y) || isStartPoint(x, y)) return false;

	if (isEndPoint(x, y)) return true;

	isEndSet = true;

	endPoint.x = x;
	endPoint.y = y;

	notify();
	return true;
}

/**
* Unset the map start point
*/
void Map::unsetStartPoint()
{
	isStartSet = false;
	notify();
}

/**
* Unset the map end point
*/
void Map::unsetEndPoint()
{
	isEndSet = false;
	notify();
}

/**
* Get the tile at a given position
* @param x X coordinate
* @param y Y coordinate
* @return Tile at the given position
*/
const Tile& Map::getTileAt(int x, int y) const
{
	return mapArr[x][y];
}

/**
* Set the tile type at the given position
* If an element is already occupying this tile, the element is destroyed
* If the new type is not traversible and this tile was the start or the end point, the point is removed.
* @param x X coordinate
* @param y Y coordinate
* @param type Tile type
* @return true is the tile was correctly set
*/
bool Map::setTileType(int x, int y, TileType type)
{
	if (isOob(x, y)) return false;

	Tile * t = &mapArr[x][y];
	Element * elementRemoved = nullptr;

	if (t->getElement() != nullptr)
	{
		elementRemoved = t->removeElement();
		elements.remove(elementRemoved);
		delete elementRemoved;
	}

	t->setType(type);

	if (isStartPoint(x, y) && !isTraversible(x, y)) unsetStartPoint();
	if (isEndPoint(x, y) && !isTraversible(x, y)) unsetEndPoint();

	notify();
	return true;
}

/**
* Get a pointer to the element contained by the tile at a given position
* @param x X coordinate
* @param y Y coordinate
* @return Pointer to the element at the given position. nullptr if there is no element.
*/
Element * Map::getElementAt(int x, int y) const
{
	if (isOob(x, y)) return nullptr; //TODO: Throw exception

	return mapArr[x][y].getElement();
}

/**
* Set the element of the tile at a given position.
* The element is cloned and assigned its position based on the coordinates parameters.
* It is then added to the list of elements and placed at the right tile.
* @param x X coordinate
* @param y Y coordinate
* @param element Element to place at the given tile
* @return Pointer to the added element. nullptr if the element was not added succesfully.
*/
Element* Map::setElementAt(int x, int y, Element& element)
{
	if (isFree(x, y) && isTraversible(x, y) && !isStartPoint(x, y))
	{
		Element& copy = *element.clone();
		copy.position.x = x;
		copy.position.y = y;
		elements.push_back(&copy);
		mapArr[x][y].setElement(&copy);

		notify();
		return &copy;
	}
	return nullptr;
}

/**
* Move a given element of a x and y offset
* @param x X offset
* @param y Y offset
* @param element Element to move
* @return true if the element was succesfully moved.
*		  If the tile where the element was supposed to move is not free or not traversible, the element is not moved.
*/
bool Map::moveElement(int xOffset, int yOffset, Element & element)
{
	int startX = element.position.x;
	int startY = element.position.y;
	int endX = startX + xOffset;
	int endY = startY + yOffset;

	if (!isTraversible(endX, endY)) return false; //TODO: Throw Exception

	Tile & tileFrom = mapArr[startX][startY];
	Element * currentElement = tileFrom.getElement();

	if (currentElement != &element) return false; //TODO: Throw Exception

	if (!isFree(endX, endY)) return false; //TODO: Throw exception

	Tile & tileTo = mapArr[endX][endY];

	tileTo.setElement(tileFrom.removeElement());
	element.position.x = endX;
	element.position.y = endY;

	notify();
	return true;
}

/**
* Destroys the element at a given tile from the map
* @param x X coordinate
* @param y Y coordinate
* @return true if an element was succesfully destroyed
*/
bool Map::removeElementAt(int x, int y)
{
	if (!isOob(x, y) && !isFree(x, y))
	{
		Element * element = mapArr[x][y].removeElement();
		elements.remove(element);
		delete element;

		notify();
		return true;
	}
	return false;
}

/**
* Validates if a given position is the start point
* @param x X coordinate
* @param y Y coordinate
* @return true if the position is the one of the start point
*/
bool Map::isStartPoint(int x, int y) const
{
	return isStartSet && x == startPoint.x && y == startPoint.y;
}

/**
* Validates if a given position is the end point
* @param x X coordinate
* @param y Y coordinate
* @return true if the position is the one of the end point
*/
bool Map::isEndPoint(int x, int y) const
{
	return isEndSet && x == endPoint.x && y == endPoint.y;
}

/**
* Validates if the tile at given coordinates is traversible (the tile type is FLOOR)
* @param x X coordinate
* @param y Y coordinate
* @return true if the tile is traversible
*/
bool Map::isTraversible(int x, int y) const
{
	if (isOob(x, y)) return false; //TODO: Throw exception

	return mapArr[x][y].isTraversible();
}

/**
* Returns a reference to the list of all the characters on the map
*/
const list<Element*>& Map::getCharacters() const
{
	return elements;
}

/**
* Validates if a given tile is free (doesn't contain any element)
* @param x X coordinate
* @param y Y coordinate
* @return true if the tile is free
*/
bool Map::isFree(int x, int y) const
{
	if (isOob(x, y)) return true; //TODO: Throw exception

	return mapArr[x][y].isFree();
}

/**
* Validates if a given position is out of bounds
* @param x X coordinate
* @param y Y coordinate
* @return true if the position is out of bounds
*/
bool Map::isOob(int x, int y) const
{
	return (x < 0 || x >= width
		|| y < 0 || y >= height);
}

/**
* Validates if the map is valid
* For the map to be valid, there must be a start point and an end point.
* These two points must be on traversible tiles. The start point tile must also be free.
* The must also be a path between the start point and the end point containing only traversible tiles.
* In the pathfinding algorithm, the fact that a tile is free or not doesn't change the validity of a map.
* In fact, all the elements possibly making a tile non free can be moved by the character (enemy killed, door opened, chest opened)
* In this case, there is only a case not managed by this algorithm, which is a door separating the entry point and the end point without
* any accessible key to open it. This would make the algorithm much more complex and this could easily be validated if in order to make a map valid,
* the creator would have to playtest it. This would also validate a situation where there are simply too many enemies for the character to be
* capable to reach the end of the level without dying.
*/
bool Map::isValid() const
{
	if (!isStartSet || !isEndSet) return false;


	if (!isTraversible(startPoint.x, startPoint.y) || !isTraversible(endPoint.x, endPoint.y)) return false;
	if (!isFree(startPoint.x, startPoint.y)) return false;

	//We will use a breath-first search
	bool** explorationArray = new bool*[width]();
	for (int i = 0; i < width; ++i)
	{
		explorationArray[i] = new bool[height]();
	}

	bool result = validationRecursive(startPoint.x, startPoint.y, explorationArray);

	for (int i = 0; i < width; ++i)
	{
		delete[] explorationArray[i];
	}
	delete[] explorationArray;

	return result;
}

/**
* Recursive function used in the map validation. Validates if a given point is the end point and
* recursively lauches the same validation in the surrounding tiles.
* @param x X coordinate to validate
* @param y Y coordinate to validate
* @param explorationArray 2D array of booleans. A true bool means that the position has already been explored.
* @return true if the end tile was found
*/
bool Map::validationRecursive(int x, int y, bool** explorationArray) const
{
	if (isOob(x, y))
	{
		return false;
	}

	if (explorationArray[x][y])
	{
		return false;
	}

	explorationArray[x][y] = true;

	if (!isTraversible(x, y))
	{
		return false;
	}

	if (isEndPoint(x, y))
	{
		return true;
	}

	return validationRecursive(x + 1, y, explorationArray)
		|| validationRecursive(x - 1, y, explorationArray)
		|| validationRecursive(x, y + 1, explorationArray)
		|| validationRecursive(x, y - 1, explorationArray);
}

/**
* Copies the given character and places it at the start point position
* @param newPlayer Reference to the player character
* @return Pointer to the actual player character. nullptr if the player was not successfully placed
*/
Element* Map::placePlayer(Element& newPlayer)
{
	if (isValid())
	{
		Element& copy = *newPlayer.clone();
		copy.position.x = startPoint.x;
		copy.position.y = startPoint.y;
		player = &copy;
		mapArr[startPoint.x][startPoint.y].setElement(&copy);

		notify();
		return &copy;
	}
	return nullptr;
}

/**
* Prints out a basic version of the map based on each of its tiles. The start point is surounded with () and the end point with [];
*/
string Map::print() const {
	string mapOutput;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			string tile = getTileAt(x, y).print();
			if (isStartPoint(x, y))
			{
				tile = "(" + tile + ")";
			}
			else if (isEndPoint(x, y))
			{
				tile = "[" + tile + "]";
			}
			else {
				tile = " " + tile + " ";
			}
			mapOutput.append(tile + " ");
		}
		mapOutput.append("\n");
	}
	return mapOutput;
}

/**
* Get the map name
* @return Map name
*/
string Map::getName() const
{
	return name;
}

/**
* Sets the map name
* @param mapName Map name
*/
void Map::setName(string newName)
{
	notify();
	name = newName;
}

string Map::serializeMapToString()
{
	string serialMap = "";
	serialMap += to_string(width);
	serialMap += "\n";
	serialMap += to_string(height);
	serialMap += "\n";
	
	serialMap += "start";
	serialMap += "\n";
	serialMap += to_string(startPoint.x);
	serialMap += "\n";
	serialMap += to_string(startPoint.y);
	serialMap += "\n";

	serialMap += "end";
	serialMap += "\n";
	serialMap += to_string(endPoint.x);
	serialMap += "\n";
	serialMap += to_string(endPoint.y);
	serialMap += "\n";


	bool somethingToWrite = false;
	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			somethingToWrite = false;
			if (mapArr[i][j].getType() == TileType::WALL) {
				serialMap += "wall\n";
				somethingToWrite = true;
			}
			else if (dynamic_cast<Character*>(mapArr[i][j].getElement())) {
				serialMap += "enemy\n";
				somethingToWrite = true;
			}
			else if (dynamic_cast<Chest*>(mapArr[i][j].getElement())) {
				serialMap += "chest\n";
				somethingToWrite = true;
			}

			if (somethingToWrite) { 
				serialMap += to_string(i);//width
				serialMap += "\n";
				serialMap += to_string(j);//height
				serialMap += "\n";
			}
		}
	}
	return serialMap;
}