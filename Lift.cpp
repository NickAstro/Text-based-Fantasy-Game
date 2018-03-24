/******************************************************************************* 
** Program name: Lift.hpp
** Author: Louis Nicastro
** Date: 3/12/2018
** Description: Header file for Lift class. Lift is the main character
* in the game and will be able to roam around the map
*******************************************************************************/ 

#include "Lift.hpp"


Lift::Lift() {
    //initialize a little stormlight with the meaning of life
    setStorm(42);
    
    //create vector of ideals to speak (if earned)
    ideals.push_back(new Menu("Menu.txt", "FIRST_IDEAL"));
    ideals.push_back(new Menu("Menu.txt", "SECOND_IDEAL"));
    ideals.push_back(new Menu("Menu.txt", "THIRD_IDEAL"));
    
    pack.push_back(new Item("Seeds"));
}

Lift::~Lift() {
    //free pack memory.
    for (unsigned int i = 0; i < pack.size(); i ++) {
        delete pack[i];
    }
    //free ideals
    for (unsigned int i = 0; i < ideals.size(); i ++) {
        delete ideals[i];
    }
}
        

/******************************************************************************* 
** Description: function moves the main character and adjusts stormlight 
* during the move so that some is used each time the player moves
*******************************************************************************/ 

void Lift::makeMove(Space* destination) {
    int stdStormlightDecrement = -5;
    
    //if staying in same location, no stormlight used
    if(location == destination) {
        return;
    }
    else {
        setLoc(destination);
        setStorm(stdStormlightDecrement);
    }
}

/******************************************************************************* 
** Description: function moves the main character and adjusts stormlight 
* during the move so that some is used each time the player moves.
* returns true if successful. otherwise, false
*******************************************************************************/ 

bool Lift::addItemToPack(Item* item) {
    if(pack.size() < packMaxSize) {
        pack.push_back(item);
        cout << item->getName() << " added to pack" << endl;
        return true;
    }
    else {
        cout << "Cannot add item. Pack is full" << endl;
        return false;
    }
}


/******************************************************************************* 
** Description: returns the current items in lift's pack as a vector. to be
* used in menu functions
*******************************************************************************/ 
std::vector<string> Lift::returnPack() {
    std::vector<string> packContents;
    
    
    if(pack.empty()) {
        //return empty vector
        return packContents;
    }
    else {
        for (unsigned int i = 0; i < pack.size(); i ++) {
            packContents.push_back(pack[i]->getName());
        }
    }
    
    return packContents;
    
}



/******************************************************************************* 
** Description: Prints the most recently earned ideal
*******************************************************************************/ 
void Lift::speakIdeal() {
    
    printf("%s",SET_BOLD_YELLOW);
    ideals[idealsEarned - 1]->printMenu();
    printf("%s",RESET_COLOR);
}


/******************************************************************************* 
** Description: Removes item from pack. Assumes data validated prior to using
*******************************************************************************/ 
void Lift::removeFromPack(Item* item) {
    int position = 0;
    
    for (unsigned int i = 0; i < pack.size(); i++) {
        if (item == pack[i] ) {
            pack.erase(pack.begin() + position);
        }
        position++;
    }
    
}