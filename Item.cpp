/******************************************************************************* 
** Program name: Item.cpp
** Author: Louis Nicastro
** Date: 3/13/2018
** Description: Implementation file for Item class. 
*******************************************************************************/ 
#include "Item.hpp"

Item::Item() {
    
}

Item::Item(string name) {
    setName(name);
    setType("ITEM");
}


Item::~Item() {
    
}

/******************************************************************************* 
** Description: Standard amount of potential from non-food items (0)
*******************************************************************************/ 
int Item::getPotential() {
    return 0;
}
        
