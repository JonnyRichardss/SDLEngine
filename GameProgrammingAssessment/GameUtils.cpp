#include "GameUtils.h"
#include <fstream>
#include <sstream>
using namespace std;

vector<string> Split(string input, char delim) {
	vector<string> words;
	stringstream ss(input);
	string word;
	while (getline(ss, word, delim)) {
		words.push_back(word);
	}
	return words;
};
vector<string> ReadFile(string filePath) {
    std::vector<std::string> output;
    char lineBuffer[1024];
    std::ifstream myFile(filePath);

    if (myFile.is_open()) {
        while (!myFile.eof()) {
            lineBuffer[0] = '\0'; //empty string
            myFile.getline(lineBuffer, 1024);
            output.push_back(lineBuffer);
        }
        myFile.close();
    }
    return output;
};