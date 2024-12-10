#ifndef DEPARTMENT_SAVOSTIANOV_H
#define DEPARTMENT_SAVOSTIANOV_H
#pragma once
#include <vector>
#include <boost/serialization/vector.hpp>
#include "Employee_Savostianov.h"
#include <QTableWidget>
#include <QPainter>
#include <QHeaderView>
#include <memory>
#include <vector>


class Department_Savostianov {
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & employees;
    }

public:

    ~Department_Savostianov() {
        clearEmployees();
    }

    std::vector<std::shared_ptr<Employee_Savostianov>> employees;

    void addEmployee(bool is_manager);

    bool removeEmployee();

    void clearEmployees();

    void saveToFile(std::string file_name);

    void loadFromFile(std::string file_name);

    void showEmployees(QTableWidget* table);

    void extracted(std::shared_ptr<Employee_Savostianov> &new_ptr);
    void fillTest();
};


#endif
