//! 
//! @file 
//! @brief Implementation file for MathHelper
//! 

#pragma once

#include <vector>

// Adapted from http://www.etechplanet.com/codesnippets/computer-graphics-draw-a-line-using-bresenham-algorithm.aspx
std::vector<std::pair<int, int>> bresenhamRightDirection(int x1, int y1, int x2, int y2); // Bresenham algorith, that may be used to calculate the path between two points

bool isTileNextTo(int x1, int y1, int x2, int y2); // Checks if two tiles are next to eachother
bool isTileNextToOrDiagonal(int x1, int y1, int x2, int y2); // Checks if two tiles are next to eachother including diagonals