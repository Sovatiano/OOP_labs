#include "Department_Savostianov.h"
#include "BooleanFuncs.h"


void Department::addEmployee(bool is_manager) {
    if (is_manager) {
        shared_ptr<Manager> new_ptr{ make_shared<Manager>(Manager().CreateManager()) };
        employees.push_back(new_ptr);
    }
    else {
        shared_ptr<Employee> new_ptr{ make_shared<Employee>(Employee().CreateEmployee()) };
        employees.push_back(new_ptr);
    }
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
            employees.erase(it);
            cout << "��������� ������� �����" << endl;
            return true;
        }
    }
    cout << "�� ������� ����� ���������� � ����� id" << endl;
    return false;
}


void Department::clearEmployees() {
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
    ofstream fout(file_name, ios::out);
    if (fout.is_open()) {
        boost::archive::text_oarchive oa(fout);
        oa << employees;
    }
    else {
        cout << "������� ���� �� �������." << endl;
    }
}


void Department::loadFromFile() {
    string file_name;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();

    std::cout << "������� ��� ����� � �������: ";
    std::getline(std::cin, file_name);

    ifstream fin(file_name);
    while (!fin.is_open()) {
        std::cin.clear();
        std::cout << "���� �� ������, ���������� ��� ���: ";
        std::getline(std::cin, file_name);
        ifstream fin(file_name);
    }

    if (fin.is_open()) {
        boost::archive::text_iarchive ia(fin);
        ia >> employees;

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