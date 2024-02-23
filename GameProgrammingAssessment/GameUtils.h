#pragma once
#ifndef USE_UTILS
#define USE_UTILS
#include <vector>
#include <string>

std::vector<std::string> StringSplit(std::string input, char delim);
bool ReadFile(std::string filePath, std::vector<std::string>& output);
bool ReadFileFirstLine(std::string filePath, std::string& output);
bool WriteFile(std::string filePath,std::vector<std::string> lines);
#endif // !USE_UTILS


