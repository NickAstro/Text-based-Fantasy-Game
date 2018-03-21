/******************************************************************************* 
** Program name: Food.hpp
** Author: Louis Nicastro
** Date: 3/12/2018
** Description: Implementation file for Food derived class. 
*******************************************************************************/ 
#include "Food.hpp"

Food::Food(string name, int stormPotential) : Item(name) {
    stormlightPotential = stormPotential;
    setType("FOOD");
}

Food::~Food() {
    
}