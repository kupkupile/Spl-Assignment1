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
	const std::vector<std::string> getActionsLogStrings() const;
    std::vector<Dish>& getMenu();
    void close();
    void clear();

    // Destructor
    virtual ~Restaurant();

    // Copy Constructor
    Restaurant(const Restaurant &other);

    // Move Constructor
    Restaurant(Restaurant &&other);

    // Copy Assignment
    Restaurant& operator=(const Restaurant &other);

    // Move Assignment
    Restaurant& operator=(Restaurant &&other);

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

    BaseAction *creatCloseAllAction();

    BaseAction *createMenuAction();

    BaseAction *createStatusAction(std::vector<std::string> &tokens);

    BaseAction *createLogAction();

    BaseAction *createBackupAction();

    BaseAction *createRestoreAction();

	int getNextValidLineIndex(const std::vector<std::string> &lines, int readIndex) const;

	void createTables(std::string &tableConfigLine);

    void createMenu(std::vector<std::string> lines, int readIndex);

};

#endif