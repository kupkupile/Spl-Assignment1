//
// Created by levletom on 11/9/18.
//

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
