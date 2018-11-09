//
// Created by levletom on 11/9/18.
//

#include "Table.h"

Table::Table(int t_capacity):capacity(t_capacity) {

}

int Table::getCapacity() const {
    return capacity;
}

void Table::addCustomer(Customer *customer) {

}

void Table::removeCustomer(int id) {

}

Customer *Table::getCustomer(int id) {
    return nullptr;
}

std::vector<Customer *> &Table::getCustomers() {
    return customersList;
}

std::vector<OrderPair> &Table::getOrders() {
    return  orderList;
}

void Table::order(const std::vector<Dish> &menu) {

}

void Table::openTable() {

}

void Table::closeTable() {

}

int Table::getBill() {
    return 0;
}

bool Table::isOpen() {
    return open;
}
