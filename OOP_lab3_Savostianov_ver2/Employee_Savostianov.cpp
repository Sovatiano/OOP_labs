#include "Employee_Savostianov.h"
#include "BooleanFuncs.h"
#include <vector>
#include <sstream>

BOOST_CLASS_EXPORT(Manager)
BOOST_CLASS_EXPORT(Employee)


Employee Employee::CreateEmployee() {
    std::string employeeID;
    std::string name;
    std::string surname;
    std::string salary;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "Введите ID сотрудника: ";
        getline(std::cin, employeeID);
        if (isInteger(employeeID) && stoi(employeeID) > 0) {
            break;
        }
        else {
            std::cout << "Неверный ввод. Введите положительное целое число." << std::endl;
        }
    }

    std::cout << "Введите имя сотрудника: ";
    getline(std::cin, name);

    std::cout << "Введите фамилию сотрудника: ";
    getline(std::cin, surname);

    while (true) {
        std::cout << "Введите зарплату сотрудника (целое число): ";
        getline(std::cin, salary);
        if (isInteger(salary) && stoi(salary) > 0) {
            break;
        }
        else {
            std::cout << "Неверный ввод. Введите положительное целое число." << std::endl;
        }
    }

    Employee new_employee(0, "", "", 0);
    new_employee.setEmployeeID(stoi(employeeID));
    new_employee.setName(name);
    new_employee.setSurname(surname);
    new_employee.setSalary(stoi(salary));

    return new_employee;
}


void Employee::ShowInfo() const {
    std::cout << "ID: " << employeeID << ", "
         << "Имя: " << name << ", "
         << "Фамилия: " << surname << ", "
         << "Зарплата: " << salary << std::endl;
}


std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}


//template<class Archive>
std::shared_ptr<Employee> Employee::ReadFromFile(std::ifstream& fin) {
    boost::archive::text_iarchive ia(fin);
    std::shared_ptr<Employee> new_ptr;
    ia >> new_ptr;
    return new_ptr;
}


//template<class Archive>
void Employee::WriteToFile(std::ofstream& fout) const {
    std::shared_ptr<Employee> new_ptr{ std::make_shared<Employee>(*this) };
    boost::archive::text_oarchive oa(fout);
    oa << new_ptr;
}


Manager Manager::CreateManager() {
    std::string department;
    std::string employees_num;
    Employee new_emp = Employee::CreateEmployee();

    std::cout << "Введите название отдела, в котром работает менеджер: ";
    getline(std::cin, department);

    while (true) {
        std::cout << "Введите количество подчинённых менеджера: ";
        getline(std::cin, employees_num);
        if (isInteger(employees_num) && stoi(employees_num) > 0) {
            break;
        }
        else {
            std::cout << "Неверный ввод. Введите положительное целое число." << std::endl;
        }
    }

    Manager new_manager;
    new_manager.setEmployeeID(new_emp.getEmployeeID());
    new_manager.setName(new_emp.getName());
    new_manager.setSurname(new_emp.getSurname());
    new_manager.setSalary(new_emp.getSalary());
    new_manager.setDepartment(department);
    new_manager.setEmpnum(stoi(employees_num));

    return new_manager;
}

void Manager::ShowInfo() const {
    Employee::ShowInfo();
    std::cout << "Отдел: " << department << ", "
         << "Количество подчинённых: " << employees_num << std::endl;
}

void Manager::WriteToFile(std::ofstream& fout) const {
    std::shared_ptr<Manager> new_ptr{ std::make_shared<Manager>(*this) };
    boost::archive::text_oarchive oa(fout);
    oa << new_ptr;
}

std::shared_ptr<Manager> Manager::ReadFromFile(std::ifstream& fin) {
    boost::archive::text_iarchive ia(fin);
    std::shared_ptr<Manager> new_ptr;
    ia >> new_ptr;
    return new_ptr;
}
