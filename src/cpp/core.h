#pragma once
#include<string>
#include<fstream>

using std::ifstream;
using std::ofstream;
using std::string;

class coreutils {
public:
	string inputFile;
	string outputFile;
	string openFile();
	void makeJSON();
	string generateErrorMessage(string originText);
	string getLink(string originLine);
	string getMarkName(string originLine);
	string getFolderName(string originLine);
	void closeFile();
private:
	ifstream reader;
	ofstream writer;
};