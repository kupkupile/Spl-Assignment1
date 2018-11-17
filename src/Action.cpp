//
// Created by levletom on 11/9/18.
//

#include "Action.h"
#include "Table.h"
#include "Restaurant.h"
extern Restaurant *backup;

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
    this->errorMsg="Error: "+errorMsg;
    status=ERROR;
    cout<<this->errorMsg<<endl;

}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

void BaseAction::setStatus(ActionStatus status) {
    this->status=status;

}

void BaseAction::setErrorMsg(string msg) {
    errorMsg=msg;
}

std::string BaseAction::getPublicErrorMsg() const {
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
    Table* tempTable = nullptr;
    if(tableId>=0)
        tempTable = restaurant.getTable(tableId);
 if(tempTable != nullptr && !tempTable->isOpen() && tempTable->getCapacity() >= (int)customers.size()-1)
 {
   tempTable->openTable();
   for(int i=0;i<(int)customers.size();i++){
       tempTable->addCustomer(customers[i]);

   }
     this->complete();
   customers.clear();
 }
 else
     {
         for(int i =0;i<(int)customers.size();i++){
             delete customers[i];
             customers[i] = nullptr;
         }
         error("Table does not exist or is already open");
     }
}

BaseAction *OpenTable::clone() {
    vector<Customer*> tCustomers;
    for(int i=0;i<(int)customers.size();i++){
        tCustomers.push_back(customers[i]);
    }
    BaseAction* result = new OpenTable(tableId,tCustomers);
    result->setStatus(getStatus());
    result->setErrorMsg(getErrorMsg());
    return result;
}

std::string OpenTable::toString() const {
    return std::__cxx11::string();
}

//*****************************************************************

Order::Order(int id): tableId(id) {

}

void Order::act(Restaurant &restaurant) {
    Table* tempTable = nullptr;
    if(tableId>=0)
        tempTable=restaurant.getTable(tableId);
    if(tempTable != nullptr && tempTable->isOpen())
    {tempTable->order(restaurant.getMenu());
      complete();}
    else
    {
        error("Table does not exist or is not open");
    }

}

BaseAction *Order::clone() {
    BaseAction* result = new Order(tableId);
    result->setStatus(getStatus());
    result->setErrorMsg(getErrorMsg());
    return result;
}

std::string Order::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTable(src),dstTable(dst), id(customerId) {

}

void MoveCustomer::act(Restaurant &restaurant) {
    Table* src = nullptr;
    Table* dst = nullptr;
    Customer* customer = nullptr;
    if(srcTable>=0)
        src = restaurant.getTable(srcTable);
    if(dstTable>=0)
        dst = restaurant.getTable(dstTable);
    if(id>=0 && src!= nullptr)
        customer = src->getCustomer(id);
  if(src!=nullptr && src->isOpen() && dst!=nullptr && dst->isOpen() && customer!=nullptr && dst->getNumOfAvailbleSeats()>0)
  {
    src->removeCustomer(customer->getId());
    dst->addCustomer(customer);
    std::vector<OrderPair>  tempOrderlist;
    for(int i = 0;i<(int)src->getOrders().size();i++){
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
      for(int i=0;i<(int)tempOrderlist.size();i++){
          src->getOrders().push_back(tempOrderlist[i]);
      }

    for(int i = 0;i<(int)tempOrderlist.size();i++){
        if(tempOrderlist[i].first==customer->getId())
        {
            dst->getOrders().push_back(tempOrderlist[i]);
           // src.removeCustomersOrders(customerId);
        }
    }
    if(src->getCustomers().empty())
        src->closeTable();
    complete();
  }
  else
  {
      error("Cannot move customer");
  }
}

BaseAction *MoveCustomer::clone() {
    BaseAction* result = new MoveCustomer(srcTable,dstTable,id);
    result->setStatus(getStatus());
    result->setErrorMsg(getErrorMsg());
    return result;
}

std::string MoveCustomer::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

Close::Close(int id):tableId(id) {

}

void Close::act(Restaurant &restaurant) {
    Table* table = nullptr;
    if(tableId>=0)
        table = restaurant.getTable(tableId);
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

BaseAction *Close::clone() {
    BaseAction* result = new Close(tableId);
    result->setStatus(getStatus());
    result->setErrorMsg(getErrorMsg());
    return result;
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

BaseAction *CloseAll::clone() {
    BaseAction* result = new CloseAll();
    result->setStatus(getStatus());
    result->setErrorMsg(getErrorMsg());
    return result;
}

std::string CloseAll::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

PrintMenu::PrintMenu() {

}

void PrintMenu::act(Restaurant &restaurant) {
   for(int i=0;i<(int)restaurant.getMenu().size();i++){
       cout<< restaurant.getMenu()[i].getName() << " ";
       if(restaurant.getMenu()[i].getType()==0)
       {
           cout<<"VEG";
       }
       if(restaurant.getMenu()[i].getType()==1)
       {
           cout<<"SPC";
       }if(restaurant.getMenu()[i].getType()==2)
       {
           cout<<"BVG";
       }if(restaurant.getMenu()[i].getType()==3)
       {
           cout<<"ALC";
       }
       std::cout<< " " << restaurant.getMenu()[i].getPrice()<<"NIS" << endl;
   }
   complete();
}

BaseAction *PrintMenu::clone() {
    BaseAction* result = new PrintMenu();
    result->setStatus(getStatus());
    result->setErrorMsg(getErrorMsg());
    return result;
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
        cout << "Table " << tableId << " status:" << " open" << endl;
        cout << "Customers:" << endl;
        for(int i=0;i<(int)toPrint->getCustomers().size();i++){
            cout<< toPrint->getCustomers()[i]->getId()<< " " << toPrint->getCustomers()[i]->getName()<<endl;
        }
        cout<< "Orders:" << endl;
        for(int j=0;j<(int)toPrint->getOrders().size();j++){
            cout<< toPrint->getOrders()[j].second.getName()<< " " << toPrint->getOrders()[j].second.getPrice()<< "NIS " << toPrint->getOrders()[j].first<<endl;
        }
        cout<<"Current Bill: "<< toPrint->getBill()<< "NIS"<<endl;
    }
    else{
        cout << "Table " << tableId << " status: " << "closed" << endl;
    }
    complete();
}

BaseAction *PrintTableStatus::clone() {
    BaseAction* result = new PrintTableStatus(tableId);
    result->setStatus(getStatus());
    result->setErrorMsg(getErrorMsg());
    return result;
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
    for(int i= 0; i<(int)actionsLog.size();i++){
        string msg;
        if(actionsLog[i]->getStatus()==COMPLETED)
            msg= "Completed";
        else if(actionsLog[i]->getStatus()==ERROR)
            msg =  actionsLog[i]->getPublicErrorMsg();
        else
            msg = "PENDING";
        cout<<actionLogStrings[i]<< " "<< msg<<endl;
    }
    complete();
}

BaseAction *PrintActionsLog::clone() {
    BaseAction* result = new PrintActionsLog();
    result->setStatus(getStatus());
    result->setErrorMsg(getErrorMsg());
    return result;
}

std::string PrintActionsLog::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

BackupRestaurant::BackupRestaurant() {

}

void BackupRestaurant::act(Restaurant &restaurant) {
    if(backup== nullptr)
        backup = new Restaurant(restaurant);
    else{
        delete backup;
        backup = new Restaurant(restaurant);
    }
    complete();
}

BaseAction *BackupRestaurant::clone() {
    BaseAction* result = new BackupRestaurant();
    result->setStatus(getStatus());
    result->setErrorMsg(getErrorMsg());
    return result;
}

std::string BackupRestaurant::toString() const {
    return std::__cxx11::string();
}

//******************************************************************

RestoreResturant::RestoreResturant() {

}

void RestoreResturant::act(Restaurant &restaurant) {
    if(backup!= nullptr) {
        restaurant = *backup;
        complete();
    }
    else
        error("No backup available");
}

BaseAction *RestoreResturant::clone() {
    BaseAction* result = new RestoreResturant();
    result->setStatus(getStatus());
    result->setErrorMsg(getErrorMsg());
    return result;
}

std::string RestoreResturant::toString() const {
    return std::__cxx11::string();
}

BaseAction::~BaseAction() {

}

OpenTable::~OpenTable() {

}

Order::~Order() {

}

MoveCustomer::~MoveCustomer() {

}

Close::~Close() {

}

CloseAll::~CloseAll() {

}

PrintMenu::~PrintMenu() {

}

PrintTableStatus::~PrintTableStatus() {

}

PrintActionsLog::~PrintActionsLog() {

}

BackupRestaurant::~BackupRestaurant() {

}

RestoreResturant::~RestoreResturant() {

}
