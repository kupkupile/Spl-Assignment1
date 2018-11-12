#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Dish.h"

class Customer{
public:
	Customer(std::string c_name, int c_id);
	virtual std::vector<int> order(const std::vector<Dish> &menu)=0;
	virtual std::string toString() const = 0;
	std::string getName() const;
	int getId() const;
	virtual Customer* clone()=0;
	virtual ~Customer();
private:
	const std::string name;
	const int id;
};


class VegetarianCustomer : public Customer {
public:
	VegetarianCustomer(std::string name, int id);
	std::vector<int> order(const std::vector<Dish> &menu);
	std::string toString() const;

	Customer *clone() override;

    ~VegetarianCustomer() override;

private:
};


class CheapCustomer : public Customer {
public:
	CheapCustomer(std::string name, int id);
	std::vector<int> order(const std::vector<Dish> &menu);
	std::string toString() const;

	Customer *clone() override;

    ~CheapCustomer() override;

private:
	bool orderedAlready;
};


class SpicyCustomer : public Customer {
public:
	SpicyCustomer(std::string name, int id);
	std::vector<int> order(const std::vector<Dish> &menu);
	std::string toString() const;

	Customer *clone() override;

    ~SpicyCustomer() override;

private:
	bool orderedAlready;
};


class AlchoholicCustomer : public Customer {
public:
	AlchoholicCustomer(std::string name, int id);
	std::vector<int> order(const std::vector<Dish> &menu);
	std::string toString() const;
	bool Ordered(int dishId);

	Customer *clone() override;

    ~AlchoholicCustomer() override;

private:
	std::vector<int> ALCOrdered;
};


#endif