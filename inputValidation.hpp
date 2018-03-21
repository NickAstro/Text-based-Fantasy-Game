/******************************************************************************* 
** Program name: inputValidation.hpp
** Author: Louis Nicastro
** Date: 1/14/2018
** Description: Header file for inputValidation function
*******************************************************************************/ 

#ifndef INPUTVALIDATION_HPP
#define INPUTVALIDATION_HPP

#include <vector>
#include <string>
using std::string;

int intValidation(int, int);

string getUserInput();
bool checkForNotEmptyEntry(string stringIn);
bool firstCharNegativeSign(string stringIn);

#endif