#include "Department_Savostianov.h"
#include "BooleanFuncs.h"
#include <iostream>



void Department_Savostianov::addEmployee(bool is_manager) {
    if (is_manager) {
        std::shared_ptr<Manager_Savostianov> new_ptr{ std::make_shared<Manager_Savostianov>(Manager_Savostianov().CreateManager()) };
        employees.push_back(new_ptr);
    }
    else {
        std::shared_ptr<Employee_Savostianov> new_ptr{ std::make_shared<Employee_Savostianov>(Employee_Savostianov().CreateEmployee()) };
        employees.push_back(new_ptr);
    }
}




bool Department_Savostianov::removeEmployee() {
    std::string employeeID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true) {
        std::cout << "??????? ID ??????????: ";
        getline(std::cin, employeeID);
        if (isInteger(employeeID) && stoi(employeeID) > 0) {
            break;
        }
        else {
            std::cout << "???????? ????. ??????? ????????????? ????? ?????." << std::endl;
        }
    }

    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getEmployeeID() == stoi(employeeID)) {
            employees.erase(it);
            std::cout << "????????? ??????? ??????" << std::endl;
            return true;
        }
    }
    std::cout << "?? ??????? ????? ?????????? ? ????? id" << std::endl;
    return false;
}


void Department_Savostianov::clearEmployees() {
    employees.clear();
}


void Department_Savostianov::saveToFile(std::string file_name) {
    std::ofstream ofs(file_name);
    boost::archive::text_oarchive oa(ofs);
    oa << employees;
}


void Department_Savostianov::loadFromFile(std::string file_name) {
    std::ifstream ifs(file_name);
    boost::archive::text_iarchive ia(ifs);
    ia >> employees;
}


void Department_Savostianov::fillTest() {
    std::shared_ptr<Employee_Savostianov> new_ptr{ std::make_shared<Employee_Savostianov>(Employee_Savostianov(1, "Сергей", "Сергеев", 20000)) };
    employees.push_back(new_ptr);
    std::shared_ptr<Employee_Savostianov> new_ptr2{ std::make_shared<Employee_Savostianov>(Employee_Savostianov(2, "Антон", "Антонов", 30000)) };
    employees.push_back(new_ptr2);
    std::shared_ptr<Employee_Savostianov> new_ptr3{ std::make_shared<Employee_Savostianov>(Employee_Savostianov(3, "Пётр", "Петров", 40000)) };
    employees.push_back(new_ptr3);
    std::shared_ptr<Manager_Savostianov> new_ptr4{ std::make_shared<Manager_Savostianov>(Manager_Savostianov(4, "Иван", "Юрьевич", 50000, "Экономический", 3))};
    employees.push_back(new_ptr4);
}


std::vector<int> Department_Savostianov::getColumnWidths(QPainter& painter) {
    std::vector<int> columnWidths = {20, 100, 100, 70, 100, 200};
    for (auto elem: employees) {
        int id_length = painter.boundingRect(QRect(0, 0, 0, 0), Qt::AlignLeft, QString::number(elem->getEmployeeID())).width();
        if (id_length > columnWidths[0]) {
            columnWidths[0] = id_length + 20;
        }
        int name_length = painter.boundingRect(QRect(0, 0, 0, 0), Qt::AlignLeft, QString::fromStdString(elem->getName())).width();
        if (name_length > columnWidths[1]) {
            columnWidths[1] = name_length + 50;
        }
        int surname_length = painter.boundingRect(QRect(0, 0, 0, 0), Qt::AlignLeft, QString::fromStdString(elem->getSurname())).width();
        if (surname_length > columnWidths[2]) {
            columnWidths[2] = surname_length + 50;
        }
        int salary_length = painter.boundingRect(QRect(0, 0, 0, 0), Qt::AlignLeft, QString::number(elem->getSalary())).width();
        if (salary_length > columnWidths[3]) {
            columnWidths[3] = salary_length + 50;
        }

        if (Manager_Savostianov* manager = dynamic_cast<Manager_Savostianov*>(elem.get())) {
            // Вычисление ширины для поля department (отдел)
            int department_length = painter.boundingRect(QRect(0, 0, 0, 0), Qt::AlignLeft, QString::fromStdString(manager->getDepartment())).width();
            if (department_length > columnWidths[4]) {
                columnWidths[4] = department_length + 50;  // Плюс небольшой отступ
            }

            // Вычисление ширины для поля employees_num (количество сотрудников)
            int employees_num_length = painter.boundingRect(QRect(0, 0, 0, 0), Qt::AlignLeft, QString::number(manager->getEmpnum())).width();
            if (employees_num_length > columnWidths[5]) {
                columnWidths[5] = employees_num_length + 50;  // Плюс небольшой отступ
            }
        }
    }

    return columnWidths;
}
