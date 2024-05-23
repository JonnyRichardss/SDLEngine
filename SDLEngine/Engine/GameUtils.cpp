#include "GameUtils.h"
#include <fstream>
#include <sstream>
using namespace std;

vector<string> StringSplit(string input, char delim) {
	vector<string> words;
	stringstream ss(input);
	string word;
	while (getline(ss, word, delim)) {
		words.push_back(word);
	}
	return words;
}
bool ReadFile(string filePath, vector<string>& output) {
    
    std::ifstream file(filePath);
    if (file.fail())
        return false;
    if (file.is_open()) {
        char buffer[1024];
        while (!file.eof()) {
            buffer[0] = '\0';
            file.getline(buffer, 1024);
            output.push_back(buffer);
        }
        file.close();
    }
    return true;
}
bool ReadFileFirstLine(string filePath, string& output) {
    std::ifstream file(filePath);
    if (file.fail())
        return false;
    if (file.is_open()) {
        char buffer[1024];
        file.getline(buffer, 1024);
        output.append(buffer);
        file.close();
    }
    return true;
}
bool WriteFile(string filePath,vector<string> lines)
{
    ifstream Ifile(filePath);
    char lastc = NULL;
    if (Ifile.is_open()) {
        //this whole dooda is so that i always print onto the next clear line - no appending to filled lines OR adding blank lines
        Ifile.seekg(-1, ios::end); // seek to end

        Ifile.get(lastc);
        Ifile.close();
    }
    ofstream Ofile(filePath,ios_base::app);
    if (Ofile.is_open()) {
        if (lastc != NULL && lastc != '\n' )
            Ofile << '\n';
        for (string line : lines) {
            Ofile << line << '\n';
        }
        Ofile.close();
    }
    else return false;

    return true;
}
