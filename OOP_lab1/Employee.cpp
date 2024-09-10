#include "Employee.h"
#include "BooleanFuncs.h"



Employee CreateEmployee() {
	string employeeID;
	string name;
	string surname;
	string salary;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (true) {
		cout << "Введите ID сотрудника: ";
		getline(cin, employeeID);
		if (isInteger(employeeID) && stoi(employeeID) > 0) {
			break;
		}
		else {
			cout << "Неверный ввод. Введите положительное целое число." << endl;
		}
	}

	cout << "Введите имя сотрудника: ";
	getline(cin, name);

	cout << "Введите фамилию сотрудника: ";
	getline(cin, surname);

	while (true) {
		cout << "Введите зарплату сотрудника (целое число): ";
		getline(cin, salary);
		if (isInteger(salary) && stoi(salary) > 0) {
			break;
		}
		else {
			cout << "Неверный ввод. Введите положительное целое число." << endl;
		}
	}

	Employee new_employee(0, "", "", 0);
	new_employee.setEmployeeID(stoi(employeeID));
	new_employee.setName(name);
	new_employee.setSurname(surname);
	new_employee.setSalary(stoi(salary));

	return new_employee;
}