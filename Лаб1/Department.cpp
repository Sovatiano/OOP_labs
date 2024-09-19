#include "Department.h"


void Department::addEmployee(const Employee& employee) {
    Employee* emp_pointer = new Employee(employee.getEmployeeID(), employee.getName(), employee.getSurname(), employee.getSalary());
    employees.push_back(emp_pointer);
}


bool Department::removeEmployee(int employeeID) {
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getEmployeeID() == employeeID) {
            delete* it;
            employees.erase(it);
            return true;
        }
    }
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
            employee->WriteToFile(fout);
        }
        fout.close();
    }
    else {
        cout << "ќткрыть файл не удалось." << endl;
    }
}


void Department::loadFromFile() {
    std::string file_name;
    std::ifstream fin;

    // —брос ввода и очистка
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();

    std::cout << "”кажите им€ файла с данными: ";
    std::getline(std::cin, file_name);

    fin.open(file_name);
    while (!fin.is_open()) {
        std::cin.clear();
        std::cout << "‘айл не найден, попробуйте ещЄ раз: ";
        std::getline(std::cin, file_name);
        fin.open(file_name);
    }

    if (fin.is_open()) {
        clearEmployees();

        Employee temp_emp = temp_emp.ReadFromFile(fin);
        while (temp_emp.getEmployeeID() != -1) {
            Employee* new_emp_pointer = new Employee(
                temp_emp.getEmployeeID(),
                temp_emp.getName(),
                temp_emp.getSurname(),
                temp_emp.getSalary()
            );

            employees.push_back(new_emp_pointer);
            temp_emp = temp_emp.ReadFromFile(fin);
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
            employee->ShowInfo();
        }
    }
}