#include "Employee_Savostianov.h"
#include "BooleanFuncs.h"
#include <vector>
#include <sstream>
#include <iostream>

BOOST_CLASS_EXPORT(Manager_Savostianov)
BOOST_CLASS_EXPORT(Employee_Savostianov)


Employee_Savostianov Employee_Savostianov::CreateEmployee() {
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

    Employee_Savostianov new_employee(0, "", "", 0);
    new_employee.setEmployeeID(stoi(employeeID));
    new_employee.setName(name);
    new_employee.setSurname(surname);
    new_employee.setSalary(stoi(salary));

    return new_employee;
}


void Employee_Savostianov::ShowInfo() const {
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
std::shared_ptr<Employee_Savostianov> Employee_Savostianov::ReadFromFile(std::ifstream& fin) {
    boost::archive::text_iarchive ia(fin);
    std::shared_ptr<Employee_Savostianov> new_ptr;
    ia >> new_ptr;
    return new_ptr;
}


//template<class Archive>
void Employee_Savostianov::WriteToFile(std::ofstream& fout) const {
    std::shared_ptr<Employee_Savostianov> new_ptr{ std::make_shared<Employee_Savostianov>(*this) };
    boost::archive::text_oarchive oa(fout);
    oa << new_ptr;
}

void Employee_Savostianov::draw(QPainter& painter, int x, int y, std::vector<int> columnWidths, int cellHeight) const {
    QString idText = QString::number(employeeID);
    QString nameText = QString::fromStdString(name);
    QString surnameText = QString::fromStdString(surname);
    QString salaryText = QString::number(salary);

    painter.setPen(Qt::black);

    painter.drawRect(x, y, columnWidths[0] + 20, cellHeight);
    painter.drawText(QRect(x + 5, y, columnWidths[0], cellHeight), Qt::AlignCenter, idText);
    x += columnWidths[0] + 20;
    painter.drawRect(x, y, columnWidths[1] + 20, cellHeight);
    painter.drawText(QRect(x + 5, y, columnWidths[1], cellHeight), Qt::AlignLeft, nameText);
    x += columnWidths[1] + 20;
    painter.drawRect(x, y, columnWidths[2] + 20, cellHeight);
    painter.drawText(QRect(x + 5, y, columnWidths[2], cellHeight), Qt::AlignLeft, surnameText);
    x += columnWidths[2] + 20;
    painter.drawRect(x, y, columnWidths[3] + 20, cellHeight);
    painter.drawText(QRect(x + 5, y, columnWidths[3], cellHeight), Qt::AlignRight, salaryText);
    x += columnWidths[3] + 20;
    painter.drawRect(x, y, columnWidths[4] + 20, cellHeight);
    x += columnWidths[4] + 20;
    painter.drawRect(x, y, columnWidths[5] + 20, cellHeight);
}

QSize Employee_Savostianov::getTextBlockSize(QPainter& painter) const {
    QString nameText = QString::fromStdString(name);
    QString surnameText = QString::fromStdString(surname);
    QString salaryText = QString::number(salary);

    QRect nameRect = painter.boundingRect(QRect(0, 0, 0, 0), Qt::AlignLeft, nameText);
    QRect surnameRect = painter.boundingRect(QRect(0, 0, 0, 0), Qt::AlignLeft, surnameText);
    QRect salaryRect = painter.boundingRect(QRect(0, 0, 0, 0), Qt::AlignRight, salaryText);

    int width = nameRect.width() + surnameRect.width() + salaryRect.width();
    int height = std::max({ nameRect.height(), surnameRect.height(), salaryRect.height() });

    return QSize(width, height);
}



Manager_Savostianov Manager_Savostianov::CreateManager() {
    std::string department;
    std::string employees_num;
    Employee_Savostianov new_emp = Employee_Savostianov::CreateEmployee();

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

    Manager_Savostianov new_manager;
    new_manager.setEmployeeID(new_emp.getEmployeeID());
    new_manager.setName(new_emp.getName());
    new_manager.setSurname(new_emp.getSurname());
    new_manager.setSalary(new_emp.getSalary());
    new_manager.setDepartment(department);
    new_manager.setEmpnum(stoi(employees_num));

    return new_manager;
}

void Manager_Savostianov::ShowInfo() const {
    Employee_Savostianov::ShowInfo();
    std::cout << "Отдел: " << department << ", "
         << "Количество подчинённых: " << employees_num << std::endl;
}

void Manager_Savostianov::WriteToFile(std::ofstream& fout) const {
    std::shared_ptr<Manager_Savostianov> new_ptr{ std::make_shared<Manager_Savostianov>(*this) };
    boost::archive::text_oarchive oa(fout);
    oa << new_ptr;
}

std::shared_ptr<Manager_Savostianov> Manager_Savostianov::ReadFromFile(std::ifstream& fin) {
    boost::archive::text_iarchive ia(fin);
    std::shared_ptr<Manager_Savostianov> new_ptr;
    ia >> new_ptr;
    return new_ptr;
}


void Manager_Savostianov::draw(QPainter& painter, int x, int y, std::vector<int> columnWidths, int cellHeight) const {
    // Сначала рисуем базовый класс (ID, имя, фамилия, зарплата)
    Employee_Savostianov::draw(painter, x, y, columnWidths, cellHeight);

    QString departmentText = QString::fromStdString(department);
    QString employeesNumText = QString::number(employees_num);

    x = columnWidths[0] + columnWidths[1] + columnWidths[2] + columnWidths[3] + 80;
    painter.drawRect(x, y, columnWidths[4] + 20, cellHeight);
    painter.drawText(QRect(x + 5, y, columnWidths[4], cellHeight), Qt::AlignLeft, departmentText);
    x += columnWidths[4] + 20;
    painter.drawRect(x, y, columnWidths[5] + 20, cellHeight);
    painter.drawText(QRect(x + 5, y, columnWidths[5], cellHeight), Qt::AlignLeft, employeesNumText);
}

QSize Manager_Savostianov::getTextBlockSize(QPainter& painter) const {
    QSize baseSize = Employee_Savostianov::getTextBlockSize(painter);

    QString departmentText = QString::fromStdString(department);
    QString employeesNumText = QString::number(employees_num);

    QRect departmentRect = painter.boundingRect(QRect(0, 0, 0, 0), Qt::AlignLeft, departmentText);
    QRect employeesNumRect = painter.boundingRect(QRect(0, 0, 0, 0), Qt::AlignRight, employeesNumText);

    int width = std::max(baseSize.width(), departmentRect.width() + employeesNumRect.width());
    int height = baseSize.height() + std::max(departmentRect.height(), employeesNumRect.height());

    return QSize(width, height);
}
