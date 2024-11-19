#include <iostream>
#include "Department.h"
#include "Employee.h"
#include "BooleanFuncs.h"
#define NOMINMAX
#include <Windows.h>


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
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

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
			department.addEmployee();
			break;
		}

		case 2:
		{
			department.removeEmployee();
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