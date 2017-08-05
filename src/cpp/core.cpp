#pragma once
#include "core.h"

void coreutils::makeJSON() {

	//Check READ/WRITE access
	string buf4BookmarkName;
	string buf4Link;
	string currentLine;
	string checkAccess = openFile();
	bool isInFirstLine = 1;
	int folderLevel = 1;
	int lastLineStatus = 0;

/*
	Values for lastLineStatus, USAGE: Mark what type the last line is

		Left Brace  ==> 0;
		Right Brace ==> 1;
		Folder Line	==> 2;
		Content Line ==> 3;
*/

	
	if (checkAccess != "Success") printf(checkAccess.c_str());
	//Check READ/WRITE access END
	
//Init Message Start
	writer << R"("Bookmarks" :)";
//Init Message End

// Main Content Start
	while (getline(reader, currentLine)) {
		
		if (currentLine.find(R"(<DL><p>)") != string::npos) { //Left Brace (Region Start) Detection
			
			writer << " {\n"; //Left Brace
			isInFirstLine = 1; //Clean up status for next rotation

			lastLineStatus = 0;

		}

	   else if (currentLine.find(R"(</DL><p>)") != string::npos) {	//Right brace (Region End) Detection

			writer << "\n" <<outputTab(folderLevel)<<"}"; // Right Brace
			isInFirstLine = 1; //Clean up status for next rotation

			lastLineStatus = 1;

		}

		else if (currentLine.find(R"(<DT><H3)") != string::npos) { //Folder Name Line Detection
			
			if (lastLineStatus == 3 || lastLineStatus == 1) {writer << ",";}

			string folderName;
			folderName = getFolderName(currentLine);
			writer
				<< "\n"
				<< outputTab(folderLevel) << R"(")"
				<< folderName.c_str()
				<< R"(" :)";

			lastLineStatus = 2;

		}

		else if (currentLine.find(R"(<DT><A HREF=)") != string::npos) { //Content (Bookmark) Line Detection
			
			if (lastLineStatus == 1) { writer << ",\n"; }
			
			if (isInFirstLine) {
				writer <<outputTab(folderLevel + 1);
				isInFirstLine = 0;
			}

			else if (!isInFirstLine) {
				//system("pause");
				writer
					<< ","
					<< "\n" << outputTab(folderLevel + 1);
			}

			buf4BookmarkName = getMarkName(currentLine);
			buf4Link = getLink(currentLine);
			writer
				<< R"(")"
				<< buf4Link
				<< R"(" : )"
				<< R"(')"
				<< buf4BookmarkName
				<< R"(')";

			lastLineStatus = 3;

		}
	}
// Main Content END



	closeFile(); //Close File read/write session

}

inline void coreutils::closeFile() {
	writer.close();
	reader.close();
}

inline string coreutils::outputTab(int tabCount) {
	string outputBuffer;
	for (int i = 0; i < tabCount; i++) {
		outputBuffer += "	";
	}
	return outputBuffer;
}

inline string coreutils::openFile() {
	if (inputFile.size() == string::npos)  return generateErrorMessage("No source file specified."); 
	if (outputFile.size() == string::npos) return generateErrorMessage("No output file specified."); 
	
	reader.open(inputFile.c_str());
	writer.open(outputFile.c_str());
	if (!reader.is_open()) return generateErrorMessage("Source File access denied, please make sure it exists and is not occupied by other programs.");
	if (!writer.is_open()) return generateErrorMessage("No access rights to the output file.");
	
	return "Success";
}

inline string coreutils::generateErrorMessage(string originText) {
	string returnText = "[ERROR] " + originText + "\n";
	return returnText;
}


inline string coreutils::getLink(string originLine) {
	string resultLink;
	int startPos = originLine.find_first_of("HREF=", 0) +4;
	int endPos = originLine.find_first_of(" ",startPos);
	int rotateCount = 0;
	/*

	Just for testing purposes

	printf("%d\n%d", startPos, endPos);
	system("pause");
	*/
	for (int i = startPos + 2; i < endPos - 1; i++) { resultLink += originLine[i]; }

	return resultLink;
};


inline string coreutils::getMarkName(string originLine) {
	string resultMarkName;
	int endPos = originLine.find_last_of(R"(</A>)");
	int startPos = originLine.find_first_of(R"(>)",(originLine.find_first_of(">")+1));
	
	for (int i = startPos + 1; i < endPos - 3; i++) {resultMarkName += originLine[i];}
	
	return resultMarkName;
};

inline string coreutils::getFolderName(string originLine) {
	string resultFolderName;
	int endPos = originLine.find_last_of(R"(</H3>)");
	int startPos = originLine.find_first_of(R"(>)", (originLine.find_first_of(">") + 1));
	
	for (int i = startPos + 1; i < endPos - 4; i++) {resultFolderName += originLine[i];}

	return resultFolderName;
}