//
// Created by amitk on 11/9/18.
//

#include "Customer.h"
#include "Dish.h"
//--------------------------------------------------Customer------------

Customer::Customer(std::string c_name, int c_id): name(c_name),id(c_id) {

}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

Customer::~Customer() {

}

//-----------------------------------------------------Veggie Customer-----------------------------
VegetarianCustomer::VegetarianCustomer(std::string name, int id) : Customer(name, id) {

}
//Veggie order strategy: order the smallest ID veggie dish in the menu , order the most expensive beverage(not alchohol)
//here int food stands for id for the veg dish , int bev stands for the id for the most expensive BVG.
// if there are 2 most expensive BVG then returns the one with smallest id
std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu) {
    int foodId = -1;
    int bev  = -1;
    int bevPrice;
    std::vector<int> dishesOrdered;
    for(int i = 0;i<menu.size();i++){
        if(menu[i].getType()==VEG & (foodId == -1 || menu[i].getId() < foodId))
               foodId = menu[i].getId();
        if(menu[i].getType()==BVG ) {
            if(bev==-1){bev=menu[i].getId();bevPrice = menu[i].getPrice();}
            else if(menu[i].getPrice()>bevPrice){bev=menu[i].getId();bevPrice=menu[i].getPrice();}
            else if(menu[i].getPrice()==bevPrice & menu[i].getId()<bev){bev = menu[i].getId();}
        }
    }
       if(foodId!= -1 & bev!=-1){
    dishesOrdered.push_back(foodId);
    dishesOrdered.push_back(bev);
}
return dishesOrdered;
}

Customer *VegetarianCustomer::clone() {
    return nullptr;
}

//yet to be implemented
std::string VegetarianCustomer::toString() const {
    return std::__cxx11::string();
}

VegetarianCustomer::~VegetarianCustomer() {

}

//----------------------------------------------------------------CheapCustomer-----------------------------------
CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {
orderedAlready=false;
}
//Cheap Customer order strategy : Order the Cheapest dish in the menu,oreders only once.
std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu) {
    int foodId = -1;
    int foodPrice;
    if(!orderedAlready) {
        for (int i = 0; i < menu.size(); i++) {
            if ((foodId == -1 || (menu[i].getPrice() < foodPrice)) ||
                (menu[i].getPrice() == foodPrice & foodId > menu[i].getId())) {
                foodId = menu[i].getId();
                foodPrice = menu[i].getPrice();
            }
        }
        orderedAlready=true;
        return std::vector<int>(1,foodId);
    }
    else
    {

        return std::vector<int>();
    }
}

Customer *CheapCustomer::clone() {
    return nullptr;
}

//yet to be implemented
std::string CheapCustomer::toString() const {
    return std::__cxx11::string();
}

CheapCustomer::~CheapCustomer() {

}

//-----------------------------------------------------------------Spicy Customer-------------------------------
// holds an additional field that states whether he oredered already or not
SpicyCustomer::SpicyCustomer(std::string name, int id) : Customer(name, id) {
orderedAlready=false;
}
//Spicy Customer Order strategy: if did not order yet : order the most expensive SPC dish
//otherwise : if did order already  then returns the cheapest BVG dish
std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu) {
    int foodId = -1;
    int foodPrice;
    //did not order yet
    if(!orderedAlready)
    {
        for (int i = 0; i < menu.size(); i++) {
            if ((menu[i].getType()==SPC && (foodId==-1 || (menu[i].getPrice() > foodPrice)) || (menu[i].getPrice() == foodPrice & foodId > menu[i].getId())))
            {  foodId = menu[i].getId(); foodPrice = menu[i].getPrice();}
        }
        if(foodId!=-1)
        {orderedAlready=true;return std::vector<int>(1,foodId);}

    }
    //ordered already
    else{
        for (int i = 0; i < menu.size(); i++) {
            if ((menu[i].getType()==BVG && (foodId==-1 || (menu[i].getPrice() < foodPrice)) || (menu[i].getPrice() == foodPrice & foodId > menu[i].getId())))
            {  foodId = menu[i].getId(); foodPrice = menu[i].getPrice();}
        }

        if(foodId!=-1)
        return std::vector<int>(1,foodId);
        else
            return std::vector<int>();
    }

}

Customer *SpicyCustomer::clone() {
    return nullptr;
}

std::string SpicyCustomer::toString() const {
    return std::__cxx11::string();
}

SpicyCustomer::~SpicyCustomer() {

}

//------------------------------------------------------------Alchoholic Customer-------------------------------
AlchoholicCustomer::AlchoholicCustomer(std::string name, int id) : Customer(name, id) {

}
//A method that will assist to ensure a dish wasnt ordered already
bool AlchoholicCustomer::Ordered(int dishId) {
    for(int i=0;i<ALCOrdered.size();i++)
    {
        if(ALCOrdered[i]==dishId)
            return true;
    }
}
//Alchoholic Customer order strategy: orders the cheapest alchoholic BVG in the menu that he hasnt ordered before
std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu) {
    int foodId = -1;
    int foodPrice;
    for (int i = 0; i < menu.size(); i++) {
        if ((menu[i].getType()==ALC && (!Ordered(menu[i].getId()) &&  (foodId==-1 || (menu[i].getPrice() < foodPrice || menu[i].getPrice() == foodPrice &  foodId < menu[i].getId())))))
        {  foodId = menu[i].getId(); foodPrice = menu[i].getPrice();}
    }
        if(foodId!=-1)
        {ALCOrdered.push_back(foodId);return std::vector<int>(1,foodId);}
         else
            {return std::vector<int>();}

}

Customer *AlchoholicCustomer::clone() {
    return nullptr;
}

std::string AlchoholicCustomer::toString() const {
    return std::__cxx11::string();
}

AlchoholicCustomer::~AlchoholicCustomer() {

}
