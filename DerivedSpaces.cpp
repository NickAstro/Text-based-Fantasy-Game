/******************************************************************************* 
** Program name: DerivedSpaces.cpp
** Author: Louis Nicastro
** Date: 3/12/2018
** Description: Implementation file for ALL 10 of the drived spaces.
*******************************************************************************/ 

#include "DerivedSpaces.hpp"

/******************************************************************************* 
** Description: Constructor/Destructor for Slums
*******************************************************************************/ 
Slums::Slums(string imageLocation, string imageSectionHead) : 
    Space(imageLocation, imageSectionHead) {
            
        setName("The Slums");
    
}

Slums::~Slums() {
    
}

/******************************************************************************* 
** Description: virtual function to allow user to interact with current space. 
*******************************************************************************/ 
void Slums::interact(Lift* lift) {
    
    if(!getSpokenToBoy()) {
        Menu m("Menu.txt","SLUMS_INTERACT1");
        m.printMenu();
        int choice = m.getUserResponse(1,2);
        //Add Extra divider to separate space
        printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
        
        //if you speak to the boy...
        if(choice == 1) {
            setSpokenToBoy(true);
            Menu m1("Menu.txt","SLUMS_SPEAK_TO_BOY1");
            m1.printMenu();
            
            lift->gainIdeal();
            lift->speakIdeal();
        }
        //otherwise, nothing happens
    }
    else {
        Menu m2("Menu.txt","SLUMS_SPEAK_TO_BOY2");
        m2.printMenu();
    }
    
    setHasInteracted(true);
}



/******************************************************************************* 
** Description: Constructor/Destructor for Market
*******************************************************************************/ 
Market::Market(string imageLocation, string imageSectionHead) : 
    Space(imageLocation, imageSectionHead) {
        
        setName("The Market");
    
}

Market::~Market() {
    
}

/******************************************************************************* 
** Description: virtual function to allow user to interact with current space. 
*******************************************************************************/ 
void Market::interact(Lift* lift) {
    if(!getHasInteracted()) {
        Menu m("Menu.txt","MARKET_INTERACT1");
        m.printMenu();
        lift->setStorm(-5);
    }
    else {
        Menu m1("Menu.txt","MARKET_INTERACT2");
        m1.printMenu();
    }
    
    setHasInteracted(true);
}


/******************************************************************************* 
** Description: Constructor/Destructor for GuardRoom
*******************************************************************************/ 
GuardRoom::GuardRoom(string imageLocation, string imageSectionHead) : 
    Space(imageLocation, imageSectionHead) {
        
        setName("The Guard Room");
        addItem(new Food("Delicious Pancakes", 20));
        addItem(new Item("Fancy looking book"));
}

GuardRoom::~GuardRoom() {
    
}

/******************************************************************************* 
** Description: virtual function to allow user to interact with current space. 
* Story is the same every time since guards will always be there and 
* will want to chase you away
*******************************************************************************/ 
void GuardRoom::interact(Lift* lift) {
    Menu m("Menu.txt", "GUARD_ROOM_INTERACT1");
    m.printMenu();
    
    //lose stormlight due to running
    lift->setStorm(-5);
    setHasInteracted(true);
}


/******************************************************************************* 
** Description: Constructor/Destructor for Hideout
*******************************************************************************/ 
Hideout::Hideout(string imageLocation, string imageSectionHead) : 
    Space(imageLocation, imageSectionHead) {
        setName("Unknown Building");
        addItem(new Food("Darkness\'s stormin' dinner", 30));
}

Hideout::~Hideout() {
    
}

/******************************************************************************* 
** Description: virtual function to allow user to interact with current space. 
*******************************************************************************/ 
void Hideout::interact(Lift* lift) {
    if(!getHasInteracted()){
        Menu m("Menu.txt","HIDEOUT_INTERACT1");
        m.printMenu();
        //update bool now that you're aware of plans in indicium
        lift->setLearn232(true);
    }
    else {
        Menu m("Menu.txt","HIDEOUT_INTERACT2");
        m.printMenu();
    }
    
    setHasInteracted(true);
}


/******************************************************************************* 
** Description: Constructor/Destructor for Gates
*******************************************************************************/ 
Gates::Gates(string imageLocation, string imageSectionHead) : 
    Space(imageLocation, imageSectionHead) {
        
        setName("The Main Gates");
    
}

Gates::~Gates() {
    
}

/******************************************************************************* 
** Description: virtual function to allow user to interact with current space. 
*******************************************************************************/ 
void Gates::interact(Lift* lift) {
    int change;
    
    if(!getHasInteracted()) {
        change = firstInteraction();
    }
    else {
        change = secondInteraction();
    }
    
    lift->setStorm(change);
    setHasInteracted(true);
}


/******************************************************************************* 
** Description: First interaction at gates
*******************************************************************************/ 
int Gates::firstInteraction() {    
    int stormlightGained = 0;
    
    Menu m("Menu.txt", "GATES_INTERACT1");
    m.printMenu();
    int answer = m.getUserResponse(1,2);
    //Add Extra divider to separate space
    printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
        
    if(answer == 1) {
        //gain stormlight from the grain
        stormlightGained += 10;
        Menu m1("Menu.txt", "GATES_INTERACT2");
        m1.printMenu();
    }
    else {
        //lose stormlight by delaying movement
        stormlightGained -= 35;
        Menu m2("Menu.txt", "GATES_INTERACT3");
        m2.printMenu();
    }
    
    return stormlightGained;
}

/******************************************************************************* 
** Description: Second interaction at gates. basic text.
*******************************************************************************/ 
int Gates::secondInteraction() {    
    int stormlightGained = 0;
    
    Menu m("Menu.txt", "GATES_INTERACT4");
    m.printMenu();
    
    return stormlightGained;
}





/******************************************************************************* 
** Description: Constructor/Destructor for Indicium
*******************************************************************************/ 
Indicium::Indicium(string imageLocation, string imageSectionHead) : 
    Space(imageLocation, imageSectionHead) {
        
        setName("The Grand Indicium");
        addItem(new Item("Spanreed"));
}

Indicium::~Indicium() {
    
}

/******************************************************************************* 
** Description: virtual function to allow user to interact with current space. 
*******************************************************************************/ 
void Indicium::interact(Lift* lift) {
    //if Lift knows about Room 232
    if(lift->getLearn232() && !getHasInteracted()) {
        Menu m("Menu.txt", "INDICIUM_INITIAL");
        m.printMenu();
        int choice = m.getUserResponse(1,2);
        //Add Extra divider to separate space
        printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
        
        //if you run, you get caught and die
        if(choice == 2) {
            Menu m("Menu.txt", "INDICIUM_RUN");
            m.printMenu();
            lift->setLiving(false);
        }
        else {
            Menu m("Menu.txt", "INDICIUM_AZIR");
            m.printMenu();
            lift->setContactAzir(true);
        }
    }
    else {
        Menu m("Menu.txt", "INDICIUM_STD");
        m.printMenu();
    }
    
    setHasInteracted(true);
}


/******************************************************************************* 
** Description: Constructor/Destructor for Room232
*******************************************************************************/ 
Room232::Room232(string imageLocation, string imageSectionHead) : 
    Space(imageLocation, imageSectionHead) {
        
        setName("Room 232");
    
}

Room232::~Room232() {
    
}

/******************************************************************************* 
** Description: virtual function to allow user to interact with current space. 
*******************************************************************************/ 
void Room232::interact(Lift* lift) {
    if(!getHasInteracted()) {
        Menu m("Menu.txt","232_INTERACT1");
        m.printMenu();
        //update lift such that she learned this.
        lift->setLearnAmpitheatre(true);
    }
    else {
        Menu m("Menu.txt","232_INTERACT2");
        m.printMenu();
    }
    setHasInteracted(true);
}


/******************************************************************************* 
** Description: Constructor/Destructor for Ampitheatre
*******************************************************************************/ 
Ampitheatre::Ampitheatre(string imageLocation, string imageSectionHead) : 
    Space(imageLocation, imageSectionHead) {
        
        setName("The Ampitheatre");
        addItem(new Item("Fancy clothes"));
}

Ampitheatre::~Ampitheatre() {
    
}

/******************************************************************************* 
** Description: virtual function to allow user to interact with current space. 
*******************************************************************************/ 
void Ampitheatre::interact(Lift* lift) {
    //if lift learned about where the radiant might be...
    if(lift->getLearnAmp()) {
        Menu m("Menu.txt","AMPITHEATRE_INTERACT1");
        m.printMenu();
    }
    //otherwise, normal first visit
    else if (!getSpokenToMan()){
        Menu m("Menu.txt","AMPITHEATRE_INTERACT2");
        m.printMenu();
        int choice = m.getUserResponse(1,2);
        //Add Extra divider to separate space
        printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
        
        if(choice == 1) {
            //user talks to old man
            Menu m1("Menu.txt","AMPITHEATRE_INTERACT3");
            m1.printMenu();
            //SET BOOL THAT YOUVE SPOKEN TO HIM 
            setSpokenToMan(true);
        }
        //otherwise, nothing
    }
    else {
        //user talks to old man
        Menu m1("Menu.txt","AMPITHEATRE_INTERACT4");
        m1.printMenu();
    }
    
    
    setHasInteracted(true);
}


/******************************************************************************* 
** Description: Constructor/Destructor for Orphanage
*******************************************************************************/ 
Orphanage::Orphanage(string imageLocation, string imageSectionHead) : 
    Space(imageLocation, imageSectionHead) {

        setName("The Orphanage");
    
}

Orphanage::~Orphanage() {
    
}

/******************************************************************************* 
** Description: virtual function to allow user to interact with current space. 
*******************************************************************************/ 
void Orphanage::interact(Lift* lift) {
    //if the game isn't about to end
    if(!(lift->getLearnAmp())) {
        //First interaction (3 meals to eat)
        if(getNumMeals() == 3) {
            Menu m("Menu.txt","ORPHANAGE_INITIAL_INTERACT");
            m.printMenu();
            int choice = m.getUserResponse(1,2);
            //Add Extra divider to separate space
            printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
        
            //user decides to eat first meal
            if(choice == 1) {
                eatMeal(lift);
            }
        }
        //otherwise, if game not at final stage and food remaining
        else if(getNumMeals() > 0 ) {
            if (getNumMeals() == 2) {
                Menu m("Menu.txt","ORPHANAGE_FOOD_INTERACT_2_OF_3");
                m.printMenu();
                int choice = m.getUserResponse(1,2);
                //Add Extra divider to separate space
                printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
        
                if(choice == 1) {
                    eatMeal(lift);
                }
            }
                
            else {
                Menu m("Menu.txt","ORPHANAGE_FOOD_INTERACT_3_OF_3");
                m.printMenu();
                int choice = m.getUserResponse(1,2);
                //Add Extra divider to separate space
                printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
        
                if(choice == 1) {
                    eatMeal(lift);
                }
            }
            
        }
        //otherwise, out of food
        else {
            Menu m("Menu.txt", "ORPHANAGE_OUT_OF_FOOD");
            m.printMenu();
            
        }
    }
    
    //otherwise, end of game scenes
    //Attempt to heal stump
    else if (lift->getIdeals() == 2) {
        
        Menu m("Menu.txt","ORPHANAGE_ATTACK");
        m.printMenu();
        int choice = m.getUserResponse(1,2);
        //Add Extra divider to separate space
        printf("%s%s%s\n", SET_BOLD_RED, spacer.c_str(), RESET_COLOR);
        
        //user decides to heal stump
        if(choice == 1) {
            //try to heal
            healStump(lift);
        }
        //otherwise, user on their own to figure it out
    }
    //stump is healed, reprompt to go to roof
    else {
        Menu m("Menu.txt","ORPHANAGE_HEAL2");
        m.printMenu();
    }
    
    
    setHasInteracted(true);
}


/******************************************************************************* 
** Description: Funtion displays meal text, updates stormlight, and decremets
* number of meals
*******************************************************************************/ 
void Orphanage::eatMeal(Lift* lift) {
    decNumMeals();
    //gain18% stormlight
    lift->setStorm(18);
    Menu m("Menu.txt","ORPHANAGE_MEAL");
    m.printMenu();
}


/******************************************************************************* 
** Description: Function attempts to heal STump. requires enough stormlight.
* Gains ideal if successful. Returns true if successful.
*******************************************************************************/ 
bool Orphanage::healStump(Lift* lift) {
    //>15 since you need 5 extra to get to the next space to win (10 + 5)
    if(lift->getStorm() > 15) {
        //heal her
        lift->setStorm(-10);
        Menu m("Menu.txt", "ORPHANAGE_HEAL");
        m.printMenu();
        
        lift->gainIdeal();
        lift->speakIdeal();
        return true;
    }
    else {
        Menu m("Menu.txt", "ORPHANAGE_FAIL");
        m.printMenu();
        return false;
    }
}

/******************************************************************************* 
** Description: Constructor/Destructor for Roof
*******************************************************************************/ 
Roof::Roof(string imageLocation, string imageSectionHead) : 
    Space(imageLocation, imageSectionHead) {
        
        setName("The Roof");
}


Roof::~Roof() {
    
}

/******************************************************************************* 
** Description: virtual function to allow user to interact with current space. 
*******************************************************************************/ 
void Roof::interact(Lift* lift) {
    
    //win game condition
    if(lift->getIdeals() == 3) {
        //text to convince darkness the voidbringers are back
        Menu m("Menu.txt", "ROOF_WIN");
        m.printMenu();
        //win game
        lift->setWinner(true);
    }
    //otherwise, normal nothing to see here text
    else if(!(lift->getLearnAmp())) {
        Menu m("Menu.txt", "ROOF_BASIC");
        m.printMenu();
    }
    
    //lose condition
    else {
        Menu m("Menu.txt", "ROOF_LOSE");
        m.printMenu();
        //lose game
        lift->setLiving(false);
    }
    
    setHasInteracted(true);
}