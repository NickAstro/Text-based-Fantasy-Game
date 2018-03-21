/******************************************************************************* 
** Program name: Space.cpp
** Author: Louis Nicastro
** Date: 3/12/2018
** Description: Implementation file for Space class. 
*******************************************************************************/ 

#include "Space.hpp"
#include "Lift.hpp"

/******************************************************************************* 
** Description:  Constructor for space class
*******************************************************************************/ 
Space::Space(string imageLocation, string imageSectionHead) {
    setLeft(nullptr);
    setRight(nullptr);
    setUp(nullptr);
    setTop(nullptr);
    setBottom(nullptr);
    setDown(nullptr);
    
    image = new Menu(imageLocation, imageSectionHead);
}

Space::~Space() {
    for(unsigned int i = 0; i < items.size(); i ++) {
        delete items[i];
    }
    delete image;
}

/******************************************************************************* 
** Description: Adds an item to the item vector up to max size
*******************************************************************************/ 
void Space::addItem(Item* item) {
    items.push_back(item);
}

/******************************************************************************* 
** Description: Displays the ASCII image stored in menu class
*******************************************************************************/ 
void Space::printSpace() {
    image->printMenu();
}

/******************************************************************************* 
** Description: Updates the ASCII image stored in menu class
*******************************************************************************/ 
void Space::updateSpaceImage(Menu* newImage) {
    delete image;
    image = newImage;
}


/******************************************************************************* 
** Description: returns a vector of strings of items to display.
*******************************************************************************/ 
std::vector<string> Space::returnItems() {
    std::vector<string> availableItems;
    
    if(items.empty()) {
        availableItems.push_back("Nothing to pick up here - Enter 1 to Exit");
    }
    else {
        for (unsigned int i = 0; i < items.size(); i ++) {
            availableItems.push_back(items[i]->getName());
        }
        //include an exit option
        availableItems.push_back("None. Select to Exit");
    }
    
    return availableItems;
}



/******************************************************************************* 
** Description: returns a pointer to an item passed by position within 
* item vector
*******************************************************************************/ 
Item* Space::returnItemByPosition(int position) {
    return items[position];
}

/******************************************************************************* 
** Description: Removes an item from the item list
*******************************************************************************/ 
void Space::removeItem(Item* item) {
    int position = 0;
    
    for (unsigned int i = 0; i < items.size(); i++) {
        if (item == items[i]) {
            items.erase(items.begin() + position);
        }
        else {
            position++;
        }
    }
}