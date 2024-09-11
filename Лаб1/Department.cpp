#include "Department.h"


void Department::addEmployee(const Employee& employee) {
    employees.push_back(employee);
}


bool Department::removeEmployee(int employeeID) {
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if (it->getEmployeeID() == employeeID) {
            employees.erase(it);
            return true;
        }
    }
    return false;
}


void Department::clearEmployees() {
    employees.clear();
}


void Department::saveToFile() {
    string file_name;
    cout << "¬ведите название файла дл€ записи:";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
    getline(cin, file_name);
    while (file_name == "")
    {
        cin.clear();
        cout << "¬ведите корректное им€: ";
        getline(cin, file_name);
    }
    ofstream fout;
    fout.open(file_name, ios::out);

    if (fout.is_open()) {
        for (const auto& employee : employees) {
            employee.WriteToFile(fout);
        }
        fout.close();
    }
    else {
        cout << "ќткрыть файл не удалось." << endl;
    }
}


void Department::loadFromFile() {
    string file_name;
    ifstream fin;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
    cout << "”кажите им€ файла с данными: ";
    getline(cin, file_name);
    fin.open(file_name, ios::in);
    while (!fin.is_open())
    {
        cin.clear();
        cout << "‘айл не найден, попробуйте ещЄ раз: ";
        getline(cin, file_name);
        fin.open(file_name, ios::in);
    }
    if (fin.is_open()) {
        employees.clear();
        string read_string;
        Employee new_emp = new_emp.ReadFromFile(fin);
        while (new_emp.getEmployeeID() != -1) {
            employees.push_back(new_emp);
            new_emp = new_emp.ReadFromFile(fin);
        }
        fin.close();
    }
}


void Department::showEmployees() const {
    if (employees.size() == 0) {
        cout << "—писок пуст." << endl;
    }

    else {
        for (const auto& employee : employees) {
            employee.ShowInfo();
        }
    }
}