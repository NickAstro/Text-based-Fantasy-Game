/******************************************************************************* 
** Program name: Game.hpp
** Author: Louis Nicastro
** Date: 3/12/2018
** Description: Header file for game class. This class controls the game flow
* and active characters and spaces. 
*******************************************************************************/ 

#ifndef GAME_HPP
#define GAME_HPP

//from http://blog.sarah-maas.com/2018/03/13/colors/
#define SET_BOLD_RED        "\033[1;31m"
#define RESET_COLOR         "\033[0m"

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
#include <ctime>    
#include <cstdlib>  

#include "Space.hpp"
#include "DerivedSpaces.hpp"
#include "Lift.hpp"
#include "Menu.hpp"
#include "inputValidation.hpp"

class Game {
    
    private:
        std::vector<Space*> map;
        Lift* lift;
        bool gameOver = false;
        Menu* mainMenu;
        Menu* preInteractionMenu;
        Menu* txtMap;
        string spacer = string(80,'-');
        

    public:
        Game();
        ~Game();
        void play();
        void setUpMap();
        void updateMap();
        void printStatus();
        bool welcome();
        void makeTurn();
        
        void showLiftLoc();
        bool isAdjacent(Space* current, Space* check);
        std::vector<Space*> printAdjacent(Space* current);
        void selectNewPosition(std::vector<Space*> &options);
        void moveLift(Space* newSpace);
        void move();
        
        void inspectAndPickUp();
        void showPack();
        
        void showMap();
        
        bool useItem(Item* item);
        
};

#endif  