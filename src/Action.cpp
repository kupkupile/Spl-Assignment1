//
// Created by levletom on 11/9/18.
//

#include "Action.h"
#include "Table.h"
#include "Restaurant.h"
using namespace std;

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
    status=ERROR;
    cout<<errorMsg<<endl;

}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

//*****************************************************************

OpenTable::OpenTable(int id, std::vector<Customer *> &customersList): tableId(id) , customers(customersList){

}
// This method opens a new table for the list of customers, it needs to check 2 things:
//1.there exist a table with the given Id.
//2.the table is not open already
//3.this given table can hold the number of customers given.

void OpenTable::act(Restaurant &restaurant) {
 Table * tempTable = restaurant.getTable(tableId);
 if(tempTable != nullptr && !tempTable->isOpen() && tempTable->getCapacity() >= customers.size()-1)
 {
   tempTable->openTable();
   for(int i=0;i<customers.size();i++){
       tempTable->addCustomer(customers[i]);
       this->complete();
   }
 }
 else
     {
         error("Table does not exist or is already open");
     }
}

std::string OpenTable::toString() const {
    return std::__cxx11::string();
}

//*****************************************************************

Order::Order(int id): tableId(id) {

}

void Order::act(Restaurant &restaurant) {
    Table * tempTable(restaurant.getTable(tableId));
    if(tempTable != nullptr && tempTable->isOpen())
    {tempTable->order(restaurant.getMenu());}
    else
    {
        error("Table does not exist or is not open");
    }

}

std::string Order::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTable(src),dstTable(dst), id(customerId) {

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

    for(int i = 0;i<tempOrderlist.size();i++){
        if(tempOrderlist[i].first==customer->getId())
        {
            dst->getOrders().push_back(tempOrderlist[i]);
           // src.removeCustomersOrders(customerId);
        }
    }
  }
  else
  {
      error("Cannot move customer");
  }
}

std::string MoveCustomer::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

Close::Close(int id):tableId(id) {

}

void Close::act(Restaurant &restaurant) {
  Table * table = restaurant.getTable(tableId);
  if(table==nullptr||!table->isOpen()) {
      error("Table does not exist or is not open");
  }
  else{
      int bill = table->getBill();
      table->closeTable();
      cout<<"Table "<<tableId<<" was closed. Bill "<<bill<<"NIS"<<endl;
      complete();
  }

}

std::string Close::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

CloseAll::CloseAll() {

}

void CloseAll::act(Restaurant &restaurant) {
    int numOfTables = restaurant.getNumOfTables();
    for(int i = 0;i<numOfTables;i++){
        Table * table = restaurant.getTable(i);
        if(table!=nullptr&&table->isOpen()) {
            int bill = table->getBill();
            table->closeTable();
            cout<<"Table "<<i<<" was closed. Bill "<<bill<<"NIS"<<endl;
        }

    }
    complete();
    restaurant.close();
}

std::string CloseAll::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

PrintMenu::PrintMenu() {

}

void PrintMenu::act(Restaurant &restaurant) {
   for(int i=0;i<restaurant.getMenu().size();i++){
       cout<< restaurant.getMenu()[i].getName() << " " << restaurant.getMenu()[i].getType() << " " << restaurant.getMenu()[i].getId() << endl;
   }
}

std::string PrintMenu::toString() const {
    return std::__cxx11::string();
}


//******************************************************************

PrintTableStatus::PrintTableStatus(int id): tableId(id){

}

void PrintTableStatus::act(Restaurant &restaurant) {
    Table *toPrint = restaurant.getTable(tableId);
    if(toPrint->isOpen())
    {
        cout << "Table " << tableId << "status: " << "open" << endl;
        cout << "Customers:" << endl;
        for(int i=0;i<toPrint->getCustomers().size();i++){
            cout<< toPrint->getCustomers()[i]->getId()<< " " << toPrint->getCustomers()[i]->getName()<<endl;
        }
        for(int j=0;j<toPrint->getOrders().size();j++){
            cout<< toPrint->getOrders()[j].second.getName()<< " " << toPrint->getOrders()[j].second.getPrice()<< " " << toPrint->getOrders()[j].first<<endl;
        }
    }
    else{
        cout << "Table " << tableId << "status: " << "closed" << endl;
    }

}

std::string PrintTableStatus::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

PrintActionsLog::PrintActionsLog() {

}

void PrintActionsLog::act(Restaurant &restaurant) {
    vector<string> actionLogStrings = restaurant.getActionsLogStrings();
    vector<BaseAction*> actionsLog = restaurant.getActionsLog();
    for(int i= 0; i<actionLogStrings.size()-1;i++){
        string msg;
        if(actionsLog[i]->getStatus()==COMPLETED)
            msg= "Completed";
        else if(actionsLog[i]->getStatus()==ERROR)
            msg = "Error: "+getErrorMsg();
        else
            msg = "PENDING";
        cout<<actionLogStrings[i]<< " "<< msg<<endl;
    }
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
