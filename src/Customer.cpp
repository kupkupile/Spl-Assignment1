//
// Created by amitk on 11/9/18.
//

#include "Customer.h"

//--------------------------------------------------Customer------------

Customer::Customer(std::string c_name, int c_id): name(c_name),id(c_id) {

}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

//-----------------------------------------------------Veggie Customer-----------------------------
VegetarianCustomer::VegetarianCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu) {
    return std::vector<int>();
}

std::string VegetarianCustomer::toString() const {
    return std::__cxx11::string();
}


//----------------------------------------------------------------CheapCustomer-----------------------------------
CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu) {
    return std::vector<int>();
}

std::string CheapCustomer::toString() const {
    return std::__cxx11::string();
}

//-----------------------------------------------------------------Spicy Customer-------------------------------
SpicyCustomer::SpicyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu) {
    return std::vector<int>();
}

std::string SpicyCustomer::toString() const {
    return std::__cxx11::string();
}
//------------------------------------------------------------Alchoholic Customer-------------------------------
AlchoholicCustomer::AlchoholicCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu) {
    return std::vector<int>();
}

std::string AlchoholicCustomer::toString() const {
    return std::__cxx11::string();
}
