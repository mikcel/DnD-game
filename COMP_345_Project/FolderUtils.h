//! 
//! @file 
//! @brief Header file for the FolderUtils
//! 

#pragma once

#include <vector>
#include <string>

//! Read all files inside specified folder with extension
std::vector<std::string> getFilesInsideFolder(std::string folder);

//! Read all files inside specified folder without extension
std::vector<std::string> getFilesInsideFolderNoExtension(std::string folder);
