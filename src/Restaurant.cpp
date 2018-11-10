//
// Created by amitk on 11/9/18.
//

#include <fstream>
#include "Restaurant.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;

Restaurant::Restaurant():open(),tables(),menu(),actionsLog() {
    open = false;
    customerindex =0 ;

}

Restaurant::Restaurant(const std::string &configFilePath):open(),tables(),menu(),actionsLog() {
    /*open=false;
    std::ifstream myFile(configFilePath);
    std::vector<std::string> lines;
    std::string line;
    if(myFile.is_open()){
        while(getline(myFile,line)){
            lines.push_back(line);
        }
    }
    */
    tables.push_back(new Table(4));
    tables.push_back(new Table(10));
    tables.push_back((new Table(10)));
    menu.push_back(Dish(1,"BEER",50,ALC));
    menu.push_back(Dish(2,"Salad",40,VEG));
    menu.push_back(Dish(3,"Water",10,BVG));
    menu.push_back(Dish(4,"Wine",60,ALC));
    menu.push_back(Dish(5,"Chili con carne",200,SPC));
    open=false;
    customerindex = 0;



}

void Restaurant::start() {

    open=true;
    std::cout<<"Restaurant is now open!"<<std::endl;
    std::string input;
    while(open){
      getline(cin,input);
      std::vector<std::string> tokens;
      string delims = " ,";
      std::size_t start = input.find_first_not_of(delims), end = 0;
      while((end = input.find_first_of(delims, start)) != std::string::npos)
      {
          tokens.push_back(input.substr(start, end - start));
          start = input.find_first_not_of(delims, end);
      }
      if(start != std::string::npos)
          tokens.push_back(input.substr(start));

      BaseAction* specificAction = makeMeAnAction(tokens);
      specificAction->act(*this);
      actionsLog.push_back(specificAction);


    }


}

int Restaurant::getNumOfTables() const {
    return 0;
}

Table *Restaurant::getTable(int ind) {
    if(ind<tables.size()){
        return tables[ind];
    }
    return nullptr;
}

const std::vector<BaseAction *> &Restaurant::getActionsLog() const {
    return actionsLog;
}

std::vector<Dish> &Restaurant::getMenu() {
    return menu;
}

OpenTable* Restaurant::createOpenTable(std::vector<std::string>& tokens) {
    int index = stoi(tokens[1]);
    vector<Customer*> customers;
    for (int i = 2; i < tokens.size(); ++i) {
        customers.push_back(creatCustomer(tokens[i],tokens[i+1]));
        i++;
    }
   OpenTable* ans = new OpenTable(index,customers);
    return ans;
}

Customer* Restaurant::creatCustomer(string name, string type) {
    if(type=="veg"){
        Customer* returnCust = new VegetarianCustomer(name,customerindex);
        customerindex++;
        return returnCust;
    }
    if(type=="chp"){
        Customer* returnCust = new CheapCustomer(name,customerindex);
        customerindex++;
        return returnCust;
    }
    if(type=="alc"){
        Customer* returnCust = new AlchoholicCustomer(name,customerindex);
        customerindex++;
        return returnCust;
    }
    if(type=="spc"){
        Customer* returnCust = new AlchoholicCustomer(name,customerindex);
        customerindex++;
        return returnCust;
    }

}

Order *Restaurant::createOrder(std::vector<std::string>& tokens) {
    int tableID = stoi(tokens[1]);
    Order* ans = new Order(tableID);
    return ans;
}

MoveCustomer *Restaurant::createMoveCustomer(std::vector<std::string>& tokens) {
    int originID = stoi(tokens[1]);
    int destID = stoi(tokens[2]);
    int custID = stoi(tokens[3]);
    MoveCustomer* ans = new MoveCustomer(originID,destID,custID);
    return ans;

}

Close *Restaurant::creatCloseAction(std::vector<std::string>& tokens) {
    int tableID = stoi(tokens[1]);
    Close* ans = new Close(tableID);
    return ans;
}

BaseAction *Restaurant::makeMeAnAction(std::vector<std::string> &tokens) {
    BaseAction* ans;
    if(tokens[0]=="open") {
        ans = createOpenTable(tokens);
    }
    else if(tokens[0]=="order"){
        ans = createOrder(tokens);
    }
    else if(tokens[0]=="move"){
        ans = createMoveCustomer(tokens);
     }
    else if(tokens[0]=="close"){
        ans = creatCloseAction(tokens);
    }
    else if(tokens[0]=="closeall"){
        ans = creatCloseAllAction(tokens);
    }
    else if(tokens[0]=="menu"){
        ans = createMenuAction(tokens);
    }
    else if(tokens[0]=="status"){
        ans = createStatusAction(tokens);
    }
    else if(tokens[0]=="log"){
        ans = createLogAction(tokens);
    }
    else if(tokens[0]=="backup"){
        ans = createBackupAction(tokens);
    }
    else if(tokens[0]=="restore"){
        ans = createRestoreAction(tokens);
    }
    else
        return nullptr;
    return ans;
}

BaseAction *Restaurant::creatCloseAllAction(std::vector<std::string> &tokens) {
    CloseAll* ans = new CloseAll();
    return ans;
}

BaseAction *Restaurant::createMenuAction(std::vector<std::string> &vector) {
    PrintMenu* ans = new PrintMenu();
    return ans;
}

BaseAction *Restaurant::createStatusAction(std::vector<std::string> &tokens) {
    PrintTableStatus* ans = new PrintTableStatus(stoi(tokens[1]));
    return ans;
}

BaseAction *Restaurant::createLogAction(std::vector<std::string> &tokens) {
    PrintActionsLog* ans = new PrintActionsLog();
    return ans;
}

BaseAction *Restaurant::createBackupAction(std::vector<std::string> &vector) {
    BackupRestaurant* ans  = new BackupRestaurant();
    return ans;
}

BaseAction *Restaurant::createRestoreAction(std::vector<std::string> &tokens) {
    RestoreResturant* ans = new RestoreResturant();
    return ans;
}

