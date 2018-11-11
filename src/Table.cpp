//
// Created by levletom on 11/9/18.
//

#include <unordered_map>
#include "Table.h"

Table::Table(int t_capacity):capacity(t_capacity),customersList(),orderList()  {
   open = false;
}


int Table::getCapacity() const {
    return capacity;
}

void Table::addCustomer(Customer *customer) {
    customersList.push_back(customer);
}

//removes customer with id=id, if not in table, does nothing.
//might need to add delete of customer.
void Table::removeCustomer(int id) {
    for(int i =0;i<customersList.size();i++){
        if(customersList[i]->getId()==id){
            customersList.erase(customersList.begin()+i);
        }
    }
}
//returns pointer to customer with id=id, if none in table returns nullptr.
Customer* Table::getCustomer(int id) {
    for(int i=0 ; i<customersList.size() ; i++){
        if(customersList[i]->getId()==id)
            return customersList[i];
    }
    return nullptr;
}

std::vector<Customer *>& Table::getCustomers() {
    return customersList;
}

std::vector<OrderPair> &Table::getOrders() {
    return  orderList;
}

void Table::order(const std::vector<Dish> &menu) {
    std::vector<OrderPair> thisOrder;
    for (int  i= 0; i < customersList.size(); i++) {
        std::vector<int> specifidCustomerOrder = customersList[i]->order(menu);
        for (int j = 0; j < specifidCustomerOrder.size(); ++j) {
            int id = specifidCustomerOrder[j];
            for(Dish d:menu){
                if(d.getId()==id){
                    OrderPair tPair(customersList[i]->getId(),d);
                    thisOrder.push_back(tPair);
                    orderList.push_back(tPair);
                }
            }
        }
    }
}

void Table::openTable() {
    open=true;
}
//delte customers
void Table::closeTable() {
    open = false;
}

int Table::getBill() {
    int ans =0;
    for(OrderPair op:orderList){
        ans = ans + op.second.getPrice();
    }
    return ans;
}

bool Table::isOpen() {
    return open;
}

int Table::getNumOfAvailbleSeats() {
    return getCapacity()-(customersList.size()-1);
}

Table::~Table() {
    clear();
}


Table::Table(const Table &other):capacity(other.getCapacity()),open(other.open),customersList(),orderList(other.orderList){
    for(int i=0;i<other.customersList.size();i++){
        customersList.push_back(other.customersList[i]->clone());
    }
}

Table::Table(Table &&other):capacity(other.getCapacity()),open(other.isOpen()),customersList(),orderList(other.orderList) {
    for(int i=0;i<other.customersList.size();i++){
        customersList.push_back(other.customersList[i]);
        other.customersList[i]=nullptr;
    }
}

Table &Table::operator=(const Table &other) {
    if (this == &other) {
        return *this;
    }
    for(int i=0;i<other.customersList.size();i++){
        customersList.push_back(other.customersList[i]->clone());
    }
    capacity=other.getCapacity();
    open=other.open;
    for(int i= 0;i<other.orderList.size();i++){
        orderList.push_back(OrderPair(other.orderList[i].first,Dish(other.orderList[i].second.getId(),other.orderList[i].second.getName(),other.orderList[i].second.getPrice(),other.orderList[i].second.getType())));
    }

}

Table &Table::operator=(Table &&other) {
    if (this != &other)
    {
        for(int i=0;i<other.customersList.size();i++){
            customersList.push_back(other.customersList[i]);
            other.customersList[i]=nullptr;
        }
        capacity=other.getCapacity();
        open=other.open;
        for(int i= 0;i<other.orderList.size();i++){
            orderList.push_back(OrderPair(other.orderList[i].first,Dish(other.orderList[i].second.getId(),other.orderList[i].second.getName(),other.orderList[i].second.getPrice(),other.orderList[i].second.getType())));
        }
    }

    return *this;
}

void Table::clear() {
    for(int i=0;i<customersList.size();i++){
        delete customersList[i];
        customersList.clear();
    }

}
