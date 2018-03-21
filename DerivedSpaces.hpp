/******************************************************************************* 
** Program name: DerivedSpaces.hpp
** Author: Louis Nicastro
** Date: 3/12/2018
** Description: Header file for ALL 10 of the drived spaces.
*******************************************************************************/ 

#ifndef DERIVED_SPACES_HPP
#define DERIVED_SPACES_HPP

//from http://blog.sarah-maas.com/2018/03/13/colors/
#define SET_BOLD_RED        "\033[1;31m"
#define RESET_COLOR         "\033[0m"

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "Space.hpp"
#include "Item.hpp"
#include "Food.hpp"
#include "Menu.hpp"
#include "Lift.hpp"

class Slums : public Space {
    
    private:
        
        bool spokenToBoy = false;

    public:
        Slums(string imageLocation, string imageSectionHead);
        ~Slums();
        virtual void interact(Lift* lift);
        bool getSpokenToBoy() {return spokenToBoy;}
        void setSpokenToBoy(bool b) {spokenToBoy = b;}
};

class Market : public Space {
        
    private:
        
        

    public:
        Market(string imageLocation, string imageSectionHead);
        ~Market();
        virtual void interact(Lift* lift);
};

class GuardRoom : public Space {
        
    private:
        


    public:
        GuardRoom(string imageLocation, string imageSectionHead);
        ~GuardRoom();
        virtual void interact(Lift* lift);
};

class Hideout : public Space {
        
    private:
        


    public:
        Hideout(string imageLocation, string imageSectionHead);
        ~Hideout();
        virtual void interact(Lift* lift);
};

class Gates : public Space {
        
    private:

    public:
        Gates(string imageLocation, string imageSectionHead);
        ~Gates();
        virtual void interact(Lift* lift);
        int firstInteraction();
        int secondInteraction();
};

class Indicium : public Space {
        
    private:

    public:
        Indicium(string imageLocation, string imageSectionHead);
        ~Indicium();
        virtual void interact(Lift* lift);
};

class Room232 : public Space {
        
    private:
        


    public:
        Room232(string imageLocation, string imageSectionHead);
        ~Room232();
        virtual void interact(Lift* lift);
};

class Ampitheatre : public Space {
        
    private:
        
        bool spokenToMan = false;

    public:
        Ampitheatre(string imageLocation, string imageSectionHead);
        ~Ampitheatre();
        virtual void interact(Lift* lift);
        void setSpokenToMan(bool b) {spokenToMan = b;}
        bool getSpokenToMan() {return spokenToMan;}
};

class Orphanage : public Space {
        
    private:
        
        int availableMeals = 3;

    public:
        Orphanage(string imageLocation, string imageSectionHead);
        ~Orphanage();
        virtual void interact(Lift* lift);
        int getNumMeals() {return availableMeals;}
        void decNumMeals() {availableMeals--;}
        void eatMeal(Lift* lift);
        bool healStump(Lift* lift);
};

class Roof : public Space {
        
    private:
        
        
    public:
        Roof(string imageLocation, string imageSectionHead);
        ~Roof();
        virtual void interact(Lift* lift);
        
};

#endif  