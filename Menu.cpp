/********************************************************************* 
** Program name: Menu.cpp
** Author: Louis Nicastro
** Date: 1/14/2018
** Description: Implementation file for Menu class. Class reads
* a text file looking for file sections. Sections are identified
* in the file as all caps words and they end with "END". Menu
* objects then return a vector of strings from that text file
* which can be printed and validated against.
*********************************************************************/ 

#include "Menu.hpp"

/********************************************************************* 
** Description: Menu contructor reads txt file and creates the 
* vector of strings
*********************************************************************/ 
Menu::Menu(string fileName, string section) {
	//create file object
	std::ifstream file;
	file.open(fileName);
	
	//TODO add filename validation here later
	
	//pass the file and find section in menu
	scrapeMenuText(file, section);

    //close the file
    file.close();
	
}

/********************************************************************* 
** Description: Menu contructor builds a menu in the following style
* 
* Header
* 1. Option one
* 2. Option two
* 
* Values start at 1 
*********************************************************************/ 
Menu::Menu(string header, vector<string> options) {
	int startingNum = 1;
	sectionText.push_back(header);
	string temp;
	
	for (unsigned int i = 0; i < options.size(); i++) {
		appendWithNum(startingNum, options[i]);
		startingNum++;
	}
}

/********************************************************************* 
** Description: Function takes file stream and relevant section text 
* to create section vector sectionText which will be parsed later.
*********************************************************************/ 
void Menu::scrapeMenuText(std::ifstream & file, string section) {
	string tempString = "";
	bool startOfSectionReached = false;
	bool endOfSectionReached = false;
	//int lastChar = 0;
	
	//Find section within text
	while(file.peek() != EOF && !endOfSectionReached) {
		
		//pull line of text, check if it matches section
		if(std::getline(file,tempString)) {
			/*
			//required conversion so that windows zipping can be handled
			lastChar = static_cast<int>(tempString[tempString.length() - 1]);
			if (lastChar == 13) {
				tempString = tempString.substr(0, tempString.length() - 1);
			}
			//not currently working as it throws a Conditional jump or move 
			//depends on uninitialised value(s) error on the if
			*/
			
			//search for start of section
			if (tempString == section) {
				startOfSectionReached = true;
			}
			
			//pull data from section (ignores section header)
			else if (startOfSectionReached) {
				//check if end reached
				if (tempString == "END") {
					endOfSectionReached = true;
				}
				else {
					//add section to vector, stopping at end of section
					sectionText.push_back(tempString);
				}
			}
		}
	}
}

/********************************************************************* 
** Description: Function prints menu to screen
*********************************************************************/ 
void Menu::printMenu() {
	//Print list to user
    for (unsigned int i = 0; i < sectionText.size(); i++) {
        cout << sectionText[i] << endl;
    }
    
    //TODO- convert this so that it doesn't print extra line
    //at end of section (don't like looks of it now)
}

/********************************************************************* 
** Description: Function gets user response and validates responses
* against defined min/max
*********************************************************************/  
int Menu::getUserResponse(int min, int max) {
	/*convert these to setters later on. add random number to 
	constructor to compare min/max against and set if not given 
	in constructor*/
	valMin = min;
	valMax = max;
	
	int userResponse;
	//data validation
    userResponse = intValidation(valMin, valMax);
    
    //return answer
    return userResponse;
}

/********************************************************************* 
** Description: Function appends existing sectionText vector with strings
*********************************************************************/  
void Menu::appendMenu(string stringIn) {
	sectionText.push_back(stringIn);
}

/********************************************************************* 
** Description: Function appends existing sectionText vector with strings
* with a prefix number ahead. Example. appendWithNum(1,"hello") would
* append "1. hello" to the vector
*********************************************************************/  
void Menu::appendWithNum(int num, string stringIn) {
	string str = "";
	//used http://www.cplusplus.com/reference/string/to_string/
	//used http://www.cplusplus.com/reference/string/string/append/
	str.append(std::to_string(num));
	str.append(". ");
	str.append(stringIn);
	
	sectionText.push_back(str);
}

