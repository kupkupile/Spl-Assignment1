#ifndef RESTAURANT_H_
#define RESTAURANT_H_

#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include "Action.h"


class Restaurant{		
public:
	Restaurant();
    Restaurant(const std::string &configFilePath);
    void start();
    int getNumOfTables() const;
    Table* getTable(int ind);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
	std::vector<std::string> getActionsLogStrings();
    std::vector<Dish>& getMenu();
    void close();

private:
    bool open;
    std::vector<Table*> tables;
    std::vector<Dish> menu;
    std::vector<BaseAction*> actionsLog;
    std::vector<std::string> actionsLogStrings;
    //**********

    int customerindex;
    OpenTable* createOpenTable(std::vector<std::string>& vector);

    Customer* creatCustomer(std::string name, std::string type);

    Order *createOrder(std::vector<std::string>& tokens);

    MoveCustomer *createMoveCustomer(std::vector<std::string>& tokens);

    Close *creatCloseAction(std::vector<std::string>& tokens);

    BaseAction *makeMeAnAction(std::vector<std::string>& tokens);

    BaseAction *creatCloseAllAction(std::vector<std::string> &tokens);

    BaseAction *createMenuAction(std::vector<std::string> &vector);

    BaseAction *createStatusAction(std::vector<std::string> &tokens);

    BaseAction *createLogAction(std::vector<std::string> &tokens);

    BaseAction *createBackupAction(std::vector<std::string> &vector);

    BaseAction *createRestoreAction(std::vector<std::string> &tokens);
};

#endif