//
// Created by levletom on 11/9/18.
//

#include "Action.h"
#include "Table.h"
#include "Restaurant.h"
using namespace std;

BaseAction::BaseAction():status(PENDING) {

}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = COMPLETED;
}

void BaseAction::error(std::string errorMsg) {
    errorMsg=errorMsg;

}

std::string BaseAction::getErrorMsg() const {

    return errorMsg;
}

//*****************************************************************

OpenTable::OpenTable(int id, std::vector<Customer *> &customersList): tableId(id) , customers(customersList){
        error("Table does not exist or is already open");
}
// This method opens a new table for the list of customers, it needs to check 2 things:
//1.there exist a table with the given Id.
//2.the table is not open already
//3.this given table can hold the number of customers given.

void OpenTable::act(Restaurant &restaurant) {
 Table * tempTable = restaurant.getTable(tableId);
 if(tempTable != nullptr && !tempTable->isOpen() && tempTable->getCapacity() >= customers.size()-1)
 {
   tempTable->openTable();for(int i=0;i<customers.size();i++){tempTable->addCustomer(customers[i]);this->complete();}
 }
 else
     {
        getErrorMsg();
     }
}

std::string OpenTable::toString() const {
    return std::__cxx11::string();
}

//*****************************************************************

Order::Order(int id): tableId(id) {
    error("Table does not exist or is not open");
}

void Order::act(Restaurant &restaurant) {
    Table * tempTable(restaurant.getTable(tableId));
    if(tempTable != nullptr && tempTable->isOpen())
    {tempTable->order(restaurant.getMenu());}
    else
    {
       getErrorMsg();
    }

}

std::string Order::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTable(src),dstTable(dst), id(customerId) {
  error("Cannot move customer");
}

void MoveCustomer::act(Restaurant &restaurant) {
  Table * src = restaurant.getTable(srcTable);
  Table * dst = restaurant.getTable(dstTable);
  Customer * customer = src->getCustomer(id);
  if(src!=nullptr && src->isOpen() && dst!=nullptr && dst->isOpen() && customer!=nullptr && dst->getNumOfAvailbleSeats()>0)
  {
    src->removeCustomer(customer->getId());
    dst->addCustomer(customer);
    std::vector<OrderPair>  tempOrderlist;
    for(int i = 0;i<src->getOrders().size();i++){
        if(src->getOrders()[i].first==customer->getId())
        {
            dst->getOrders().push_back(src->getOrders()[i]);
        }
        else
        {
            tempOrderlist.push_back(src->getOrders()[i]);
        }

    }
      src->getOrders().clear();
      for(int i=0;i<tempOrderlist.size();i++){
          src->getOrders().push_back(tempOrderlist[i]);
      }
  }
  else
  {
      getErrorMsg();
  }
}

std::string MoveCustomer::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

Close::Close(int id):tableId(id) {

}

void Close::act(Restaurant &restaurant) {
  Table * toCloseTable(restaurant.getTable(tableId));
}

std::string Close::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

CloseAll::CloseAll() {

}

void CloseAll::act(Restaurant &restaurant) {

}

std::string CloseAll::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

PrintMenu::PrintMenu() {

}

void PrintMenu::act(Restaurant &restaurant) {

}

std::string PrintMenu::toString() const {
    return std::__cxx11::string();
}


//******************************************************************

PrintTableStatus::PrintTableStatus(int id): tableId(id){

}

void PrintTableStatus::act(Restaurant &restaurant) {

}

std::string PrintTableStatus::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

PrintActionsLog::PrintActionsLog() {

}

void PrintActionsLog::act(Restaurant &restaurant) {

}

std::string PrintActionsLog::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

BackupRestaurant::BackupRestaurant() {

}

void BackupRestaurant::act(Restaurant &restaurant) {

}

std::string BackupRestaurant::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

RestoreResturant::RestoreResturant() {

}

void RestoreResturant::act(Restaurant &restaurant) {

}

std::string RestoreResturant::toString() const {
    return std::__cxx11::string();
}
