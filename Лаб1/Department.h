#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Employee.h"

using namespace std;

class Department {
private:
    vector<Employee> employees;

public:
    void addEmployee(const Employee& employee);

    bool removeEmployee(int employeeID);

    void clearEmployees();

    void saveToFile();

    void loadFromFile();

    void showEmployees() const;
};
