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
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        for (const auto& employee : employees)
            ar& employee;
    }

public:

    ~Department() {
        clearEmployees();
    }

    void addEmployee(bool is_manager);

    bool removeEmployee();

    void clearEmployees();

    void saveToFile();

    void loadFromFile();

    void showEmployees() const;
};
