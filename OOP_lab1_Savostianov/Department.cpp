#include "Department.h"
#include "BooleanFuncs.h"


void Department::addEmployee() {
    Employee* emp_pointer = new Employee;
    *emp_pointer = Employee().CreateEmployee();
    employees.push_back(emp_pointer);
}


bool Department::removeEmployee() {
    string employeeID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << "������� ID ����������: ";
        getline(cin, employeeID);
        if (isInteger(employeeID) && stoi(employeeID) > 0) {
            break;
        }
        else {
            cout << "�������� ����. ������� ������������� ����� �����." << endl;
        }
    }

    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getEmployeeID() == stoi(employeeID)) {
            delete* it;
            employees.erase(it);
            cout << "��������� ������� �����" << endl;
            return true;
        }
    }
    cout << "�� ������� ����� ���������� � ����� id" << endl;
    return false;
}


void Department::clearEmployees() {
    for (auto& employee : employees) {
        delete employee;
    }
    employees.clear();
}


void Department::saveToFile() {
    string file_name;
    cout << "������� �������� ����� ��� ������:";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
    getline(cin, file_name);
    while (file_name == "")
    {
        cin.clear();
        cout << "������� ���������� ���: ";
        getline(cin, file_name);
    }
    ofstream fout;
    fout.open(file_name, ios::out);

    if (fout.is_open()) {
        for (const auto& employee : employees) {
            employee->WriteToFile(fout);
        }
        fout.close();
    }
    else {
        cout << "������� ���� �� �������." << endl;
    }
}


void Department::loadFromFile() {
    std::string file_name;
    std::ifstream fin;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();

    std::cout << "������� ��� ����� � �������: ";
    std::getline(std::cin, file_name);

    fin.open(file_name);
    while (!fin.is_open()) {
        std::cin.clear();
        std::cout << "���� �� ������, ���������� ��� ���: ";
        std::getline(std::cin, file_name);
        fin.open(file_name);
    }

    if (fin.is_open()) {

        while (!fin.eof()) {
            Employee* new_emp_pointer = new Employee;
            *new_emp_pointer = Employee().ReadFromFile(fin);

            if (new_emp_pointer->getEmployeeID() != -1) {
                employees.push_back(new_emp_pointer);
            }
            else {
                delete new_emp_pointer;
                break;
            }
        }

        fin.close();
    }
}


void Department::showEmployees() const {
    if (employees.size() == 0) {
        cout << "������ ����." << endl;
    }

    else {
        for (const auto& employee : employees) {
            employee->ShowInfo();
        }
    }
}