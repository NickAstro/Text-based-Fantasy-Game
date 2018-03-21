/******************************************************************************* 
** Program name: Item.hpp
** Author: Louis Nicastro
** Date: 3/13/2018
** Description: Header file for Item class. 
*******************************************************************************/ 

#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>


class Item {
    
    protected:
        string name;
        string type;
        

    public:
        Item();
        Item(string name);
        virtual ~Item();
        
        void setName(string name) {this->name = name;}
        string getName() {return name;}
        
        void setType(string type) {this->type = type;}
        string getType() {return type;}
        
        virtual int getPotential();
        
};

#endif  