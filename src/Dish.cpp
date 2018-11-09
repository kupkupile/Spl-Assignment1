//
// Created by amitk on 11/9/18.
//
#include "Dish.h"

Dish::Dish(int d_id, std::string d_name, int d_price, DishType d_type):id(d_id),name(name),price(d_price),type(d_type) {

}

int Dish::getId() const {
    return id;
}

std::string Dish::getName() const {
    return name;
}

int Dish::getPrice() const {
    return price;
}

DishType Dish::getType() const {
    return type;
}

