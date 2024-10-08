#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Employee_Savostianov.h"

using namespace std;

class Department {
private:
    vector<shared_ptr<Employee>> employees;

public:

    ~Department() {
        clearEmployees();
    }

    void addEmployee();

    bool removeEmployee();

    void clearEmployees();

    void saveToFile();

    void loadFromFile();

    void showEmployees() const;
};
