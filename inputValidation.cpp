/******************************************************************************* 
** Program name: inputValidation.cpp
** Author: Louis Nicastro
** Date: 1/15/2018
** Description: Collection of functions to validate user input
* matches program intent. 
* 
* This Program shall grow over time, but * will start with validating 
* received integers against expected upper and lower bounds
*******************************************************************************/ 
#include <iostream>
#include <string>

using std::string;
#include "inputValidation.hpp"

/******************************************************************************* 
** Description: Gets input from user and validates for integer input. 
* Continues to ask for proper input until received, including checks
* against defined upper and lower bounds.
* 
* Some ideas from https://www.youtube.com/watch?v=jGQoRw8xYHo&t=162s
*******************************************************************************/ 
int intValidation(int min, int max) {
    string stringIn;
    int validatedInt, numValidChar, inputLength;
    bool withinBounds = false;

    do {
        //get string from user
        stringIn = getUserInput();
        //check for empty string
        while(!checkForNotEmptyEntry(stringIn)) {
            //re-enter function
            stringIn = getUserInput();
        }
    	
    	bool negValue = firstCharNegativeSign(stringIn);
    	
        //get length of reveived string
        inputLength = stringIn.length();
        
        //Valid characters
        char validInts[10] = {'0','1','2','3','4','5','6','7','8','9'};
        
        //loop through received string and count valid chars
        if (negValue) {
            //first value considered accepted
            numValidChar = 1;
            for (int i = 1; i < inputLength; i++) {
                //make unsigned to avoid warning signed/unsigned comparison
                for (unsigned int j = 0; j < sizeof(validInts); j++ ) {
                    if (stringIn[i] == validInts[j]) {
                        numValidChar++;
                    }
                }
            }
            //Don't allow just '-' at entry
            if (inputLength == 1) {
                numValidChar = 0;
            }
        }
        
        //otherwise, potentially a positive value
        else {
            numValidChar = 0;
            for (int i = 0; i < inputLength; i++) {
                //make unsigned to avoid warning signed/unsigned comparison
                for (unsigned int j = 0; j < sizeof(validInts); j++ ) {
                    if (stringIn[i] == validInts[j]) {
                        numValidChar++;
                    }
                }
            }
        }
        
        //If all inputed values are numbers, convert to string
        if (numValidChar == inputLength ) {
            //covert string to int
            validatedInt = std::stoi(stringIn);
            
            //test integer against bounds
            if (validatedInt > max) {
                std::cout << "Input too high. Enter at max " << max << ": ";
                }
            else if (validatedInt < min) {
                std::cout << "Input too low. Enter at least " << min << ": ";
                }
            else {
                withinBounds = true;
            }
        }
        
        //error for not integer
        else {
            std::cout << "Error: Please only enter integers: ";
        }
        
    } while (numValidChar != inputLength || !withinBounds);
    
    return validatedInt;
}

/******************************************************************************* 
** Description: Function to initially get user's input. Gets as string and 
* passes to checking functions as string.
*******************************************************************************/ 
string getUserInput() {
    string stringIn;
    getline(std::cin, stringIn);
    return stringIn;
}



/******************************************************************************* 
** Description: Function to check that the user didn't just hit enter upon 
* entry. Returns false and prompts user to reenter if enter alone pressed.
* Otherwise, true.
*******************************************************************************/ 
bool checkForNotEmptyEntry(string stringIn) {
    if (stringIn.empty()) {
        std::cout << "Invalid input.  Try again: "; 
        return false;
    }
    else {
        return true;
    }
        
}

/******************************************************************************* 
** Description: Function checks if the first char in string is a negative sign.
*******************************************************************************/ 
bool firstCharNegativeSign(string stringIn) {
    if (stringIn[0] == '-') {
        return true;
    }
    else {
        return false;
    }
        
}