#include "MathHelper.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>

/**
* Bresenham algorithm that takes into account the direction
* Adapted from http://www.etechplanet.com/codesnippets/computer-graphics-draw-a-line-using-bresenham-algorithm.aspx
* @param x1 x of the first point
* @param y1 y of the first point
* @param x2 x of the second point
* @param y2 y of the second point
* @return line calculated using the Bresenham algorithm
*/
std::vector<std::pair<int,int>> bresenhamRightDirection(int x1, int y1, int x2, int y2)
{
	std::vector<std::pair<int, int>> coordinates;

	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = abs(dx);
	dy1 = abs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}
		coordinates.push_back(std::make_pair(x,y));
		for (i = 0; x<xe; i++)
		{
			x = x + 1;
			if (px<0)
			{
				px = px + 2 * dy1;
			}
			else
			{
				if ((dx<0 && dy<0) || (dx>0 && dy>0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			coordinates.push_back(std::make_pair(x, y));
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}
		coordinates.push_back(std::make_pair(x, y));
		for (i = 0; y<ye; i++)
		{
			y = y + 1;
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx<0 && dy<0) || (dx>0 && dy>0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			coordinates.push_back(std::make_pair(x, y));
		}
	}

	// Custom modification to the alogorithm: revert the array if the first 
	// point in the created std::vector corresponds to (x2, y2) and the last
	// point in the std::vector corresponds to (x1, y1)
	if (coordinates[0].first == x2 && coordinates[0].second == y2
		&& coordinates[coordinates.size() - 1].first == x1 && coordinates[coordinates.size() - 1].second == y1)
	{
		std::reverse(coordinates.begin(), coordinates.end());
	}

	return coordinates;
}

/**
* Determines if two points are just next to eachother
* @param x1 x of the first point
* @param y1 y of the first point
* @param x2 x of the second point
* @param y2 y of the second point
* @return true if they are just next to eachother, false otherwise
*/
bool isTileNextTo(int x1, int y1, int x2, int y2)
{
	return (abs(x1 - x2) == 1 && y1 == y2) || (abs(y1 - y2) == 1 && x1 == x2);
}

/**
* Determines if two points are just next to eachother including diagonal points
* @param x1 x of the first point
* @param y1 y of the first point
* @param x2 x of the second point
* @param y2 y of the second point
* @return true if they are next to eachother, false otherwise
*/
bool isTileNextToOrDiagonal(int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	return (dx == 0 && dy == 1) || (dx == 1 && dy == 0) || (dx == 1 && dy == 1);
}