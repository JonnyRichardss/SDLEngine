#pragma once
#ifndef USE_UTILS
#define USE_UTILS
#include <vector>
#include <string>

std::vector<std::string> StringSplit(std::string input, char delim);
//returns true if file is successfully read
bool ReadFile(std::string filePath, std::vector<std::string>& output);
/*
Watch out for this function - it's almost entirely useless apart from renaming log files to the first line of them LMAO
*/
bool ReadFileFirstLine(std::string filePath, std::string& output);
bool WriteFile(std::string filePath,std::vector<std::string> lines);
#endif // !USE_UTILS


