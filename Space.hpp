/******************************************************************************* 
** Program name: Space.hpp
** Author: Louis Nicastro
** Date: 3/12/2018
** Description: Header file for Space class. 
*******************************************************************************/ 

#ifndef SPACE_HPP
#define SPACE_HPP

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
#include "Item.hpp"
#include "Menu.hpp"

class Lift;

class Space {
    
    protected:
        Space* left;    //west
        Space* right;   //east
        Space* up;      //vertical up
        Space* down;    //vertical down
        Space* top;     //north
        Space* bottom;  //south
        
        string name;
        
        Menu* image;
        
        bool hasEntered = false;
        bool hasInteracted = false;
        
        //vector of people in it
        //Menu image
        std::vector<Item*> items;
        

    public:
        Space(string imageLocation, string imageSectionHead);
        virtual ~Space();
        virtual void interact(Lift* lift) = 0;
        void printSpace();
        void updateSpaceImage(Menu* newImage);
        
        string spacer = string(80,'-');
        
        //setters/getters for space pointers
        void setLeft(Space* left) {this->left = left;}
        void setRight(Space* right) {this->right = right;}
        void setTop(Space* top) {this->top = top;}
        void setBottom(Space* bottom) {this->bottom = bottom;}
        void setUp(Space* up) {this->up = up;}
        void setDown(Space* down) {this->down = down;}
        
        Space* getLeft() {return left;}
        Space* getRight() {return right;}
        Space* getTop() {return top;}
        Space* getBottom() {return bottom;}
        Space* getUp() {return up;}
        Space* getDown() {return down;}
        
        void setHasEntered(bool status) {hasEntered = status;}
        bool getEntered() {return hasEntered;}
        
        void setHasInteracted(bool status) {hasInteracted = status;}
        bool getHasInteracted() {return hasInteracted;}
        
        //for name
        string getName() {return name;}
        void setName(string name) {this->name = name;}
        
        void addItem(Item* item);
        std::vector<string> returnItems();
        void removeItem(Item* item);
        
        Item* returnItemByPosition(int position);
};

#endif  