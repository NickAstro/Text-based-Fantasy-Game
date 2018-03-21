/******************************************************************************* 
** Program name: Food.hpp
** Author: Louis Nicastro
** Date: 3/12/2018
** Description: Header file for Food class. 
*******************************************************************************/ 

#ifndef FOOD_HPP
#define FOOD_HPP

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "Item.hpp"
#include "Menu.hpp"

class Food : public Item {
    
    private:
        int stormlightPotential;

    public:
        Food(string name, int stormPotential);
        ~Food();
        void setPotential(int potential) {stormlightPotential = potential;}
        int getPotential() {return stormlightPotential;}
        
};

#endif  