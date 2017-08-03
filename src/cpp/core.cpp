#pragma once
#include "core.h"

void coreutils::makeJSON() {

	//Check READ/WRITE access
	string buf4BookmarkName;
	string buf4Link;
	string currentLine;
	string checkAccess = openFile();
	
	if (checkAccess != "Success") printf(checkAccess.c_str());
	//Check READ/WRITE access END
	
//Init Message Start
	writer << R"("Bookmarks":)" << "\n" << "	{\n";
//Init Message End

// Main Content Start
	while (getline(reader, currentLine)) {
		

		bool semicolonStat = 0;
		bool braceStat     = 0;
		
		if (currentLine.find(R"(<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=UTF-8")") != string::npos
			|| currentLine.find(R"(<TITLE>)") != string::npos
			|| currentLine.find(R"(<H1>)") != string::npos
			|| currentLine.find(R"(<DL><p>)") != string::npos
			) {
			continue;
		}


		//Folder-enabled Mode Start
		if (currentLine.find(R"(<DT><H3)") != string::npos) {
			

			string folderName;
			folderName = getFolderName(currentLine);
			writer 
				<< R"(		")" 
				<< folderName.c_str() 
				<< R"(" :)" 
				<< "\n		{\n";

			
			while (getline(reader,currentLine)) {

				if (currentLine.find(R"(<DT><A HREF=)") != string::npos) {
					if (semicolonStat == 1) {
						writer 
							<< ";" 
							<< "\n			";
					}
					if (semicolonStat == 0) {
						writer << "\n			";
						semicolonStat = 1;
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
				}
				if (currentLine.find(R"(</DL><p>)") != string::npos) {
					writer 
						<< "\n" 
						<< "		}" 
						<< "\n"; 
					break;
				}
			}
		}
		//Folder-enabled Mode END
		
		braceStat     = 0;
		semicolonStat = 0;


		//Raw Bookmark Mode Start
		if (currentLine.find(R"(<DT><A HREF=)") != string::npos) {
				
			if (semicolonStat == 1) {
					writer << ";" << "\n";
			}
			if (semicolonStat == 0) {
				writer << "\n";
				semicolonStat = 1;
			}
			buf4BookmarkName = getMarkName(currentLine);
			buf4Link = getLink(currentLine);
			writer << R"(		")" << buf4Link << R"(" : )" << R"(')" << buf4BookmarkName << R"(')";
			
		}
		//Raw Bookmark Mode END
	}
// Main Content END

//End Message Start
	writer << "\n}\n";
//End Message END
	

	closeFile(); //Close File read/write session

}

void coreutils::closeFile() {
	writer.close();
	reader.close();
}

string coreutils::openFile() {
	if (inputFile.size() == string::npos)  return generateErrorMessage("No source file specified."); 
	if (outputFile.size() == string::npos) return generateErrorMessage("No output file specified."); 
	
	reader.open(inputFile.c_str());
	writer.open(outputFile.c_str());
	if (!reader.is_open()) return generateErrorMessage("Source File access denied, please make sure it exists and is not occupied by other programs.");
	if (!writer.is_open()) return generateErrorMessage("No access rights to the output file.");
	
	return "Success";
}

string coreutils::generateErrorMessage(string originText) {
	string returnText = "[ERROR] " + originText + "\n";
	return returnText;
}


string coreutils::getLink(string originLine) {
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


string coreutils::getMarkName(string originLine) {
	string resultMarkName;
	int endPos = originLine.find_last_of(R"(</A>)");
	int startPos = originLine.find_first_of(R"(>)",(originLine.find_first_of(">")+1));
	
	for (int i = startPos + 1; i < endPos - 3; i++) {resultMarkName += originLine[i];}
	
	return resultMarkName;
};

string coreutils::getFolderName(string originLine) {
	string resultFolderName;
	int endPos = originLine.find_last_of(R"(</H3>)");
	int startPos = originLine.find_first_of(R"(>)", (originLine.find_first_of(">") + 1));
	
	for (int i = startPos + 1; i < endPos - 4; i++) {resultFolderName += originLine[i];}

	return resultFolderName;
}