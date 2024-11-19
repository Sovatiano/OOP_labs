﻿#include <iostream>
#include "Department_Savostianov.h"
#include <Windows.h>


void ShowMenu()
{
    std::cout << "1. Добавить сотрудника" << "\n"
		<< "2. Добавить менеджера" << "\n"
		<< "3. Удалить сотрудника" << "\n"
		<< "4. Показать список сотрудников" << "\n"
		<< "5. Считать список из файла" << "\n"
		<< "6. Сохранить список в файл" << "\n"
		<< "7. Очистить список" << "\n"
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
        std::wcout << "Введите номер опции (0-7): ";
        if (!(std::cin >> action) or action < 0 or action > 7) {
            std::cerr << "Неверный ввод. Попробуйте ещё раз." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		switch (action)
		{
		case 1:
		{
			department.addEmployee(false);
			break;
		}

		case 2:
		{
			department.addEmployee(true);
			break;
		}

		case 3:
		{
			department.removeEmployee();
			break;
		}

		case 4:
		{
			department.showEmployees();
			break;
		}

		case 5:
		{
			department.loadFromFile();
			break;
		}


		case 6:
		{
			department.saveToFile();
			break;
		}

		case 7: {
			department.clearEmployees();
			break;
		}

		case 0: {
			return 0;
		}

		}

	}
}