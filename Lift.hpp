/******************************************************************************* 
** Program name: Lift.hpp
** Author: Louis Nicastro
** Date: 3/12/2018
** Description: Header file for Lift class. Lift is the main character
* in the game and will be able to roam around the map
*******************************************************************************/ 

#ifndef LIFT_HPP
#define LIFT_HPP

//from http://blog.sarah-maas.com/2018/03/13/colors/
#define SET_BOLD_RED        "\033[1;31m"
#define SET_RED             "\033[0;31m"
#define SET_BOLD_GREEN      "\033[1;32m"
#define SET_GREEN           "\033[0;32m"
#define SET_BOLD_YELLOW     "\033[1;33m"
#define SET_YELLOW          "\033[0;33m"
#define SET_BOLD_BLUE       "\033[1;34m"
#define SET_BLUE            "\033[0;34m"
#define SET_BOLD_MAGENTA    "\033[1;35m"
#define SET_MAGENTA         "\033[0;35m"
#define SET_BOLD_CYAN       "\033[1;36m"
#define SET_CYAN            "\033[0;36m"
#define RESET_COLOR         "\033[0m"

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
#include <ctime>    //for rand
#include <cstdlib>  //for rand

#include "Item.hpp"
#include "Menu.hpp"
#include "Space.hpp"

class Lift {
    
    private:
        Space* location;
        int stormlight = 0;
        std::vector<Item*> pack;
        unsigned const int packMaxSize = 4;
        int idealsEarned = 1; 
        std::vector<Menu*> ideals;
        
        //a bool to hold if Lift learned where the radiant is
        bool learnedAmpitheare = false;
        //bool to say if Lift learned about work being done in indicium
        bool learned232 = false;
        bool contactedAzir = false;
        
        //gameplay managers
        bool isAlive = true;
        bool winner = false;
        


    public:
        Lift();
        ~Lift();
        
        bool addItemToPack(Item* item);
        void removeFromPack(Item* item);
        std::vector<string> returnPack();
        Item* getItemByPosition(int position) {return pack[position];}
        
        int getIdeals() {return idealsEarned;}
        
        void setLoc(Space* location) {this->location = location;}
        Space* getLoc() {return location;}
        
        void setStorm(int storm) {stormlight += storm;}
        int getStorm() {return stormlight;}
        
        void makeMove(Space* destination);
        
        void speakIdeal();
        void gainIdeal() {idealsEarned++;}
        
        void setLearnAmpitheatre(bool b) {learnedAmpitheare = b;}
        bool getLearnAmp() {return learnedAmpitheare;}
        
        void setLearn232(bool b) {learned232 = b;}
        bool getLearn232() {return learned232;}
        
        void setLiving(bool b) {isAlive = b;}
        bool getIsAlive() {return isAlive;}
        
        void setWinner(bool b) {winner = b;}
        bool getWinner() {return winner;}
        
        void setContactAzir(bool b) {contactedAzir = b;}
        bool getAzir() {return contactedAzir;}
};

#endif  