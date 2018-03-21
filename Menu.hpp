/********************************************************************* 
** Program name: Menu.hpp
** Author: Louis Nicastro
** Date: 1/14/2018
** Description: Header file for Menu class
*********************************************************************/ 

#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
#include <fstream>
using std::string;
#include <vector>
using std::vector;
#include "inputValidation.hpp"

class Menu {
	private:
		vector<string> sectionText;
		int valMin;
		int valMax;
		void scrapeMenuText(std::ifstream &, string);

	public:
		//Contructor builds object by searching for Menu section
        Menu(string, string);
        
        Menu(string header, vector<string> options);
        
        //TODO Contructor with min/max built in
        //Menu(string, string, int, int);
        
        //TODO Set limits for validation
        //void setLimits(int min, int max);
        
        
        //print the menu
        void printMenu();
        //receive user response to question
        int getUserResponse(int, int);
        
        void appendMenu(string);
        void appendWithNum(int, string);

};
#endif