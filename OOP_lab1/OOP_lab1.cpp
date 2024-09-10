#include <iostream>
#include "Department.h"
#include "Employee.h"
#include "BooleanFuncs.h"


void ShowMenu()
{
	cout << "1. Добавить сотрудника" << "\n"
		<< "2. Удалить сотрудника" << "\n"
		<< "3. Показать список сотрудников" << "\n"
		<< "4. Считать список из файла" << "\n"
		<< "5. Сохранить список в файл" << "\n"
		<< "6. Очистить список" << "\n"
		<< "0. Выход" << "\n";
}


int main()
{
	setlocale(LC_CTYPE, "Russian");
	Department department;

	while (1) {
		ShowMenu();
		int action;
		cout << "Введите номер опции (0-6): ";
		if (!(cin >> action) or action < 0 or action > 6) {
			cerr << "Неверный ввод. Попробуйте ещё раз." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		switch (action)
		{
		case 1:
		{
			Employee new_employee = CreateEmployee();
			department.addEmployee(new_employee);
			break;
		}

		case 2:
		{
			string employeeID;
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

			if (department.removeEmployee(stoi(employeeID))) {
				cout << "Сотрудник успешно удалён." << endl;
			}
			else {
				cout << "Не удалось найти сотрудника с заданным ID." << endl;
			}

			break;
		}

		case 3:
		{
			department.showEmployees();
			break;
		}

		case 4:
		{
			department.loadFromFile();
			break;
		}


		case 5:
		{
			department.saveToFile();
			break;
		}

		case 6: {
			department.clearEmployees();
			break;
		}

		case 0: {
			return 0;
		}

		}

	}
}