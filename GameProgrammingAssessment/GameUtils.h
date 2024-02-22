#pragma once
#ifndef USE_UTILS
#define USE_UTILS
#include <vector>
#include <string>

std::vector<std::string> Split(std::string input, char delim);
std::vector<std::string> ReadFile(std::string filePath);
#endif // !USE_UTILS


