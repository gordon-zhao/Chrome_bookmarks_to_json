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
	inline string openFile();
	void makeJSON();
	inline string generateErrorMessage(string originText);
	inline string getLink(string originLine);
	inline string getMarkName(string originLine);
	inline string getFolderName(string originLine);
	void closeFile();
	inline string outputTab(int tabCount);
private:
	ifstream reader;
	ofstream writer;
};