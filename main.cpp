/******************************************************************************* 
** Program name: main.cpp
** Author: Louis Nicastro
** Date: 3/12/2018
** Description: This is a text-based fantasy game based on the book, 
* Edgedancer, by Brandon Sanderson. A Make file is included. 
* 
* Compile with make and run with ./play
*******************************************************************************/ 

#include "Game.hpp"  
#include <ctime>
#include <cstdlib>

int main() {

    Game game;
    game.play();
    
    return 0;
}