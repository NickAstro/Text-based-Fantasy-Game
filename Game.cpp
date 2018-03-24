/******************************************************************************* 
** Program name: Game.cpp
** Author: Louis Nicastro
** Date: 3/12/2018
** Description: Implementation file for game class. This class controls the 
* game flow and active characters and spaces. 
*******************************************************************************/ 

#include "Game.hpp"  

/******************************************************************************* 
** Description: Constructor creates the initial spaces, main character, points
* objects as required. 
*******************************************************************************/ 
Game::Game() {
    mainMenu = new Menu("Menu.txt","MAIN_MENU");
    txtMap = new Menu("Menu.txt", "MAP");
    preInteractionMenu = new Menu("Menu.txt","PRE_INTER_MENU");
}

/******************************************************************************* 
** Description: Desctructor
*******************************************************************************/ 
Game::~Game() {
    for (unsigned int i = 0; i < map.size(); i++) {
        delete map[i];
    }
    
    delete lift;
    delete mainMenu;
    delete txtMap;
    delete preInteractionMenu;
}

/******************************************************************************* 
** Description: Displays welcome prompt. returns true of user decides to 
* play. otherwise, false. 
*******************************************************************************/ 
bool Game::welcome() {
    Menu m("Menu.txt","GAME_WELCOME");
    m.printMenu();
    int choice = m.getUserResponse(1,2);
    
    if(choice == 1) {
        return true;
    }
    else {
        return false;
    }
}

/******************************************************************************* 
** Description: Manages the iterative gameplay loop. 
*******************************************************************************/ 
void Game::makeTurn() {
    int select;
    //Display the header
    showLiftLoc();
    printStatus();
    
    //update map if required
    updateMap();
    
    //display ASCII artwork
    lift->getLoc()->printSpace();
    
    //Display proper menu, based on if interaction demanded
    if(!(lift->getLoc()->getHasInteracted())) {
        //print selection menu
        preInteractionMenu->printMenu();
        select = preInteractionMenu->getUserResponse(1,2);
        //Add Extra divider to separate space
        printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
        
        if (select == 1) {
            //to interact with space
            lift->getLoc()->interact(lift);
        }
        else {
            showMap();
        }
    }
    //interaction already occured. Show more options
    else {
        mainMenu->printMenu();
        select = mainMenu->getUserResponse(1,5);
        //Add Extra divider to separate space
        printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
        if (select == 1) {
            //to interact with space
            lift->getLoc()->interact(lift);
            
        }
        else if(select == 2) {
            inspectAndPickUp();
        }
        else if (select == 3) {
            showPack();
        }
        else if (select == 4) {
            move();
        }
        else {
            showMap();
        }
    }
    
    if(lift->getStorm() < 0 || !(lift->getIsAlive()) || lift->getWinner()) {
        gameOver = true;
    }
}

/******************************************************************************* 
** Description: Function controls the gamplay.
*******************************************************************************/ 
void Game::play() {
    setUpMap();
    //ask if user wants to play
    if(welcome()) {
        //if so, play. 
        showMap();
    
        //Show first ideal at start.
        lift->speakIdeal();
        
        while(!gameOver) {
            makeTurn();
        }
        if(lift->getWinner()) {
            cout << "\n\n**********YOU WIN!**********\n"; 
        }
        else {
            if(lift->getStorm() < 0) {
                Menu m("Menu.txt","OUT_OF_STORMLIGHT");
                m.printMenu();
            }
            
            cout << "\n\nYOU LOSE\n"; 
        }
    }
    else {
        cout << "\nOkay goodbye!\n";
    }
}


/******************************************************************************* 
** Description: Function fills the map vector and points spaces to proper 
* locations. Also creates player and places on the map
*******************************************************************************/ 
void Game::setUpMap() {
    
    //setup ASCI art files
    string imageFileName = "Menu.txt";
    
    string slumName = "SLUMS_ASCII";
    string indName = "GRAND_I_ASCII";
    string r232Name = "232_ASCII";
    string markName = "MARKET_ASCII";
    string hideName = "HIDEOUT_ASCII";
    string gateName = "GATES_ASCII";
    string guardName = "GUARD_ROOM_ASCII";
    string ampName = "AMP_ASCII";
    string orpName = "ORPHANAGE_ASCII";
    string roofName = "ROOF_ASCII_EMPTY";
        
    //Create the full map of Spaces
    map.push_back(new Slums(imageFileName, slumName));          //map[0]
    map.push_back(new Indicium(imageFileName,indName));         //map[1]
    map.push_back(new Room232(imageFileName, r232Name));         //map[2]
    map.push_back(new Market(imageFileName, markName));         //map[3]
    map.push_back(new Hideout(imageFileName, hideName));        //map[4]
    map.push_back(new Gates(imageFileName, gateName));          //map[5]
    map.push_back(new GuardRoom(imageFileName, guardName));      //map[6]
    map.push_back(new Ampitheatre(imageFileName, ampName));     //map[7]
    map.push_back(new Orphanage(imageFileName, orpName));        //map[8]
    map.push_back(new Roof(imageFileName, roofName));           //map[9]
    
    //Point objects on map to proper adjacent spaces
    map[0]->setTop(map[7]);
    map[0]->setUp(map[6]);          //scale wall required
    map[0]->setLeft(map[1]);
    map[0]->setRight(map[3]);
    
    
    map[1]->setRight(map[0]);
    
    map[3]->setRight(map[4]);
   
    map[3]->setBottom(map[5]);
    map[3]->setLeft(map[0]);
    
    map[4]->setLeft(map[3]);
    
    map[5]->setLeft(map[6]);
    map[5]->setTop(map[3]);
    
    map[6]->setDown(map[0]);
    map[6]->setRight(map[5]);
    
    map[7]->setBottom(map[0]);
    map[7]->setTop(map[8]);
    
    map[8]->setBottom(map[7]);
    map[8]->setUp(map[9]);
    
    map[9]->setDown(map[8]);
    
    //create player object, place in starting location
    lift = new Lift;
    lift->setLoc(map[5]);
    map[5]->setHasEntered(true);
    
}

/******************************************************************************* 
** Description: Function prints the current location of the player to the
* screen
*******************************************************************************/ 
void Game::showLiftLoc() {
    string stars = "**********";
    
    cout << endl<< stars << " You are currently at " << 
        lift->getLoc()->getName() << " " << stars << endl << endl;
}

/******************************************************************************* 
** Description: Function checks if a passed space is adjacent to a fixed space.
* First argument, current or fixed space. 
* Second argument, space in question.
* 
* Returns true if adjacent. Otherwise, false.
*******************************************************************************/ 
bool Game::isAdjacent(Space* current, Space* check) {
    //return false if checking for itself
    if(current == check) {
        return false;
    }
    //otherwise, check against all directions
    else {
        if(current->getLeft() == check) {
            return true;
        }
        else if(current->getRight()  == check) {
            return true;
        }
        else if(current->getTop() == check) {
            return true;
        }
        else if(current->getBottom() == check) {
            return true;
        }
        else if(current->getUp() == check) {
            return true;
        }
        else if(current->getDown() == check) {
            return true;
        }
        else {
            return false;
        }
    }
    
}

/******************************************************************************* 
** Description: Function prints the the spaces around a passed space and their
* direction. Allows for printing if a space is both next to and above/below.
* Values printed with a number option presented first
* 
* returns a vector of adjacent cells that can be used to move later on.
*******************************************************************************/ 
std::vector<Space*> Game::printAdjacent(Space* current) {
    //create menu object that will fill with numerical choices for directions
    Menu directions("Menu.txt","MOVE_OPTIONS");
    int dirChoice = 1;
    string choiceTxt;
    
    //create temp vector to hold the options for adjacent cells
    std::vector<Space*> moveOptions;
    
    for(unsigned int i = 0; i < map.size(); i++) {
        if(isAdjacent(current, map[i])) {
            //this section creates a custom menu for the user to choose from
            if(current->getLeft() == map[i]) {
                choiceTxt = "";
                choiceTxt.append(map[i]->getName());
                if(current  == map[4]) {
                    choiceTxt.append(" to the west out the front door.");
                }
                else {
                    choiceTxt.append(" to the west.");
                }
                directions.appendWithNum(dirChoice, choiceTxt);
                dirChoice++;
                moveOptions.push_back(map[i]);
            }
            if(current->getRight()  == map[i]) {
                choiceTxt = "";
                choiceTxt.append(map[i]->getName());
                if(current  == map[3]) {
                    choiceTxt.append(" to the east through the front door.");
                }
                else {
                    choiceTxt.append(" to the east.");
                }
                directions.appendWithNum(dirChoice, choiceTxt);
                dirChoice++;
                moveOptions.push_back(map[i]);
            }
            if(current->getTop() == map[i]) {
                choiceTxt = "";
                choiceTxt.append(map[i]->getName());
                choiceTxt.append(" to the north.");
                directions.appendWithNum(dirChoice, choiceTxt);
                dirChoice++;
                moveOptions.push_back(map[i]);
            }
            if(current->getBottom() == map[i]) {
                choiceTxt = "";
                choiceTxt.append(map[i]->getName());
                choiceTxt.append(" to the south.");
                directions.appendWithNum(dirChoice, choiceTxt);
                dirChoice++;
                moveOptions.push_back(map[i]);
            }
            if(current->getUp() == map[i]) {
                choiceTxt = "";
                choiceTxt.append(map[i]->getName());
                //CUSTOM - if in the market and need to climb the tree
                if(current == map[3]) {
                    choiceTxt.append("'s window by climbing this tree you made.");
                }
                else {
                    choiceTxt.append(" above you.");
                }
                directions.appendWithNum(dirChoice, choiceTxt);
                dirChoice++;
                moveOptions.push_back(map[i]);
            }
            if(current->getDown() == map[i]) {
                choiceTxt = "";
                choiceTxt.append(map[i]->getName());
                if(current  == map[4]) {
                    choiceTxt.append(" by climbing down the tree.");
                }
                //if in Guard room and need to jump out window
                else if (current == map[6]) {
                    choiceTxt.append(" by jumping out this Window. ");
                    choiceTxt.append("Wyndle should catch you.");
                }
                else {
                    choiceTxt.append(" below you.");
                }
                directions.appendWithNum(dirChoice, choiceTxt);
                dirChoice++;
                moveOptions.push_back(map[i]);
            }
        }
    }
    
    //add EXIT option
    choiceTxt = "Stay where you are.";
    directions.appendWithNum(dirChoice, choiceTxt);
    moveOptions.push_back(current);
        
    //print to screen and return the custom vector
    directions.printMenu();
    return moveOptions;
}

/******************************************************************************* 
** Description: Function moves lift to a new location as defined by 
* selectNewPosition
*******************************************************************************/ 
void Game::moveLift(Space* newSpace) {
    
    lift->makeMove(newSpace);
    newSpace->setHasEntered(true);
}

/******************************************************************************* 
** Description: Function gets user response on location choice. Moves lift
* to that location
*******************************************************************************/ 
void Game::selectNewPosition(std::vector<Space*> &options) {
    unsigned int userResponse;
    //get response from user from EXIT to number of choices. 
    userResponse = intValidation(1, options.size());
    
    //Conditional to kill lift if she enters the hangout through the door.
    if(lift->getLoc() == map[3]) {
        //if selected to enter through front door
        if (userResponse == 2) {
            //then kill lift
            Menu m("Menu.txt","HIDEOUT_WRONG_ENTRANCE");
            m.printMenu();
            //game over
            lift->setLiving(false);
        }
    }
    
    
    moveLift(options[userResponse - 1]);
    
    //Get some white Space
    cout << endl; 
    
}



/******************************************************************************* 
** Description: Function controls the displaying of movement options and actual
* movement of Lift.
*******************************************************************************/ 
void Game::move() {
    //print options to the screen, create vector of those options
    std::vector<Space*> options = printAdjacent(lift->getLoc());
    //move lift
    selectNewPosition(options);

}

/******************************************************************************* 
** Description: Function displays the amount of stormlight and 
* number of ideals to the screen. also updates booleans if needed in spaces
*******************************************************************************/ 
void Game::printStatus() {

    
    cout << "Current Stormlight: " << lift->getStorm() << "%" << endl;
    cout << "Ideals Spoken: " << lift->getIdeals() << endl;
    //pack capacity
    
    //Something about being hungry if under 20%
    //Commentary on current space
}


/******************************************************************************* 
** Description: Function displays the contents of current pack. Gives user
* option to use or discard items. Discarded items are placed into the current
* Space.
*******************************************************************************/ 
void Game::showPack() {
    std::vector<string> options = lift->returnPack();
    if(options.empty()) {
        options.push_back("Your pack is empty - Select to exit");
        Menu packMenu("Here's your pack:", options);
        packMenu.printMenu();
        packMenu.getUserResponse(1,1);
        return;
    }
    
    options.push_back("No thanks - Exit Menu");
    string packHead = "\nYour pack:\n";
    packHead.append("Select the item that you would like to use or throw away");    
    Menu packMenu(packHead, options);
        
    packMenu.printMenu();
    
    //Give user option to use item from pack
    unsigned int choice = packMenu.getUserResponse(1, options.size()); 
    
    //user decides to quit. 
    if(choice == options.size()) {
        return;
    }
    else {
        Item* itemChosen = lift->getItemByPosition(choice - 1);
        
        //ask user it they would like to use or discard selected item
        std::vector<string> useOrDiscard;
        string head = "Would you like to use or discard ";
        head.append(itemChosen->getName());
        head.append("?");
        
        useOrDiscard.push_back("Use");
        useOrDiscard.push_back("Discard");
        useOrDiscard.push_back("Neither - Exit");
        Menu useOrDiscardMenu(head, useOrDiscard);
        
        cout<< endl;
        useOrDiscardMenu.printMenu();
        
        //get response
        choice = useOrDiscardMenu.getUserResponse(1,3);
        if(choice == 3) {
            //exit
            return;
        }
        else if(choice == 1) {
            //use
            useItem(itemChosen);
        }
        else {
            //discard from pack into current space
            lift->removeFromPack(itemChosen);
            lift->getLoc()->addItem(itemChosen);
            
        }
    }
}

/******************************************************************************* 
** Description: Function Looks around the room for items
*******************************************************************************/ 
void Game::inspectAndPickUp() {
    
    //Create menu with header, options, and footer question
    string head = "You look around and see... ";
    string foot = "What item would you like to pick up?";
    
    std::vector<string> availableItems = lift->getLoc()->returnItems();
    
    Menu itemMenu(head, availableItems);
    itemMenu.appendMenu(foot);
    itemMenu.printMenu();
    
    //ask user to pick item
    unsigned int choice = itemMenu.getUserResponse(1, availableItems.size());
    
    //user chose to quit
    if(choice == availableItems.size()) {
        return;
    }
    //otherwise, pick up item
    else {
        //get item from space
        Item* item;
        item = lift->getLoc()->returnItemByPosition(choice - 1);
        
        //attempt to add to Lift's pack
        if(lift->addItemToPack(item)) {
            //remove from space
            lift->getLoc()->removeItem(item);
        }
    }
}

/******************************************************************************* 
** Description: Function prints the aerial map
*******************************************************************************/ 
void Game::showMap() {
    txtMap->printMenu();
}

/******************************************************************************* 
** Description: Function updates pointers on map based on game conditions
*******************************************************************************/ 
void Game::updateMap() {
    //allow access to room 232 if lift knows about it
    if(lift->getLearn232()) {
        map[1]->setDown(map[2]);
        map[2]->setUp(map[1]);
        
        //force the interaction in Indicium once lift arrives there again
        //Unless contacted Azir already already entered room 232
        if(!(lift->getAzir())) {
            map[1]->setHasInteracted(false);
        }
    }
    
    //once lift learns about who might be killer... 
    if(lift->getLearnAmp() && !(lift->getLoc() == map[7])) {
            map[7]->setHasInteracted(false);
    }
    if(lift->getLearnAmp() && !(lift->getLoc() == map[8])) {
            map[8]->setHasInteracted(false);

    }
    if(lift->getLearnAmp() && !(lift->getLoc() == map[9])) {
            map[9]->setHasInteracted(false);
    }

    //check if player has entered darkness's hideout
    if(map[4]->getEntered()) {
        //if so, update map
        delete txtMap;
        txtMap = new Menu("Menu.txt", "MAP_DARKNESS");
        //update name
        map[4]->setName("Darkness's Hideout");
    }
}

/******************************************************************************* 
** Description: Function attempts to use a chosen item in the current
* location. If current position allows it, item is used and removed from
* pack. Otherwise, returns false.
*******************************************************************************/ 
bool Game::useItem(Item* item) {
    Space* curSpace = lift->getLoc();
    
    //if in the market and try to use Seeds,
    if(curSpace == map[3] && item->getName() == "Seeds") {
        //check if you have enough stormlight
        if(lift->getStorm() > 20) {
            //grow a tree. Add additional way to get into the hideout
            map[4]->setDown(map[3]);
            map[3]->setUp(map[4]);
            //Add Extra divider to separate space
            printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
            cout << "\nYou grew a tree from seeds and stormlight and can now " << 
                "climb into the building above...\n-20% Stormlight" << endl;
            //use stormlight
            lift->setStorm(-20);
            //delete the item
            lift->removeFromPack(item);
            delete item;
            return true;
                                                    //Print some crazy growth image series if time
        }
        else {
            //Add Extra divider to separate space
            printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
            cout << "\nWyndle: \"This would be a great place to grow a tree if ";
            cout << "only you had more stormlight\"" << endl;
            return false;
        }
        
          
    }
    
    if(item->getName() == "Fancy looking book") {
        //Add Extra divider to separate space
        printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
        cout << "\nThis book is worthless. And you can't even read!" << endl;
        return false;
    }
    else if (item->getType() == "FOOD") {
        //Add Extra divider to separate space
        printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
        //then eat. Gain stormlight and remove item.
        cout << "\nTime to eat!" << endl;
        cout << "Stormlight increased " << item->getPotential() << "%" << 
            endl;
        lift->setStorm(item->getPotential());
        delete item;
        lift->removeFromPack(item);
        
        return true;
    }
    else {
        //Add Extra divider to separate space
        printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
        cout << "\nYou tried to use the " << item->getName() << 
            " but nothing happend" << endl;
        return false;
    }
}

