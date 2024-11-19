#include "Department_Savostianov.h"
#include "BooleanFuncs.h"


void Department::addEmployee(bool is_manager) {
    if (is_manager) {
        std::shared_ptr<Manager> new_ptr{ std::make_shared<Manager>(Manager().CreateManager()) };
        employees.push_back(new_ptr);
    }
    else {
        std::shared_ptr<Employee> new_ptr{ std::make_shared<Employee>(Employee().CreateEmployee()) };
        employees.push_back(new_ptr);
    }
}


bool Department::removeEmployee() {
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


void Department::clearEmployees() {
    employees.clear();
}


void Department::saveToFile() {
    std::string file_name;
    std::cout << "??????? ???????? ????? ??? ??????:";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
    getline(std::cin, file_name);
    while (file_name == "")
    {
        std::cin.clear();
        std::cout << "??????? ?????????? ???: ";
        getline(std::cin, file_name);
    }
    std::ofstream fout(file_name, std::ios::out);
    if (fout.is_open()) {
        for (const auto& employee : employees) {
            employee->WriteToFile(fout);
        }
        fout.close();
    }
    else {
        std::cout << "??????? ???? ?? ???????." << std::endl;
    }
}


void Department::loadFromFile() {
    std::string file_name;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();

    std::cout << "??????? ??? ????? ? ???????: ";
    std::getline(std::cin, file_name);

    std::ifstream fin(file_name);
    while (!fin.is_open()) {
        std::cin.clear();
        std::cout << "???? ?? ??????, ?????????? ??? ???: ";
        std::getline(std::cin, file_name);
        std::ifstream fin(file_name);
    }

    if (fin.is_open()) {
        clearEmployees();


        while (fin.peek() != EOF) {
            try {
                /*boost::archive::text_iarchive ia(fin);*/
                //shared_ptr<Manager> new_ptr = Manager().ReadFromFile(ia);
                std::streampos current_pos = fin.tellg();
                std::shared_ptr<Employee> new_ptr = Employee().ReadFromFile(fin);
                if (new_ptr->getName() == "") {
                    fin.seekg(current_pos);
                    std::shared_ptr<Manager> mng_ptr = Manager().ReadFromFile(fin);
                    employees.push_back(mng_ptr);
                }


                if (new_ptr->getName() != "") {
                    employees.push_back(new_ptr);
                }
            }
            catch (boost::archive::archive_exception& ex) {
                break;
            }
        }

        fin.close();
    }
}


void Department::showEmployees() const {
    if (employees.size() == 0) {
        std::cout << "?????? ????." << std::endl;
    }

    else {
        for (const auto& employee : employees) {
            employee->ShowInfo();
        }
    }
}
