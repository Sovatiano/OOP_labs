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
    // std::cout << "??????? ???????? ????? ??? ??????:";
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // std::cin.clear();
    // getline(std::cin, file_name);
    // while (file_name == "")
    // {
    //     std::cin.clear();
    //     std::cout << "??????? ?????????? ???: ";
    //     getline(std::cin, file_name);
    // }
    // std::ofstream fout(file_name, std::ios::out);
    // if (fout.is_open()) {
    //     for (const auto& employee : employees) {
    //         employee->WriteToFile(fout);
    //     }
    //     fout.close();
    // }
    // else {
    //     std::cout << "??????? ???? ?? ???????." << std::endl;
    // }
}


void Department_Savostianov::loadFromFile(std::string file_name) {

    std::ifstream ifs(file_name);
    boost::archive::text_iarchive ia(ifs);
    ia >> employees;

    // if (fin.is_open()) {
    //     clearEmployees();


    //     while (fin.peek() != EOF) {
    //         try {
    //             /*boost::archive::text_iarchive ia(fin);*/
    //             //shared_ptr<Manager> new_ptr = Manager().ReadFromFile(ia);
    //             std::streampos current_pos = fin.tellg();
    //             std::shared_ptr<Employee_Savostianov> new_ptr = Employee_Savostianov().ReadFromFile(fin);
    //             if (new_ptr->getName() == "") {
    //                 fin.seekg(current_pos);
    //                 if (!fin.good()) {
    //                     std::cout << "НАСРАЛИ!!" << std::endl;
    //                 }
    //                 std::shared_ptr<Manager_Savostianov> mng_ptr = Manager_Savostianov().ReadFromFile(fin); // код не идёт дальше этой строки и выходит из функции
    //                 employees.push_back(mng_ptr);
    //             }


    //             if (new_ptr->getName() != "") {
    //                 employees.push_back(new_ptr);
    //             }
    //         }
    //         catch (boost::archive::archive_exception& ex) {
    //             break;
    //         }
    //     }

    //     fin.close();
    // }
}


void Department_Savostianov::fillTest() {
    std::shared_ptr<Employee_Savostianov> new_ptr{ std::make_shared<Employee_Savostianov>(Employee_Savostianov(1, "aha", "ajjaj", 20000)) };
    employees.push_back(new_ptr);
}
