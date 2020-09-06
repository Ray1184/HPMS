/*!
 * File FileSystem.cpp
 */

#include "FileSystem.h"

bool hpms::FileSystem::init = false;
std::vector<std::string> hpms::FileSystem::mountedPaths = std::vector<std::string>();