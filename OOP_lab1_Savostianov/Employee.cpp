#include "Employee.h"
#include "BooleanFuncs.h"
#include <vector>
#include <sstream>



Employee Employee::CreateEmployee() {
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


void Employee::ShowInfo() const {
	cout << "ID: " << employeeID << ", "
		<< "Имя: " << name << ", "
		<< "Фамилия: " << surname << ", "
		<< "Зарплата: " << salary << endl;
}


vector<string> split(const string& s, char delim) {
	vector<string> result;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}


Employee Employee::ReadFromFile(ifstream& fin) {
	Employee emp(-1, "", "", 0);
	if (fin.is_open()) {
		string cur_string;
		getline(fin, cur_string);
		vector<string> elements = split(cur_string, ' ');
		if (elements.size() == 4) {
			emp.setEmployeeID(stoi(elements[0]));
			emp.setName(elements[1]);
			emp.setSurname(elements[2]);
			emp.setSalary(stoi(elements[3]));
		}
	}

	return emp;
}


void Employee::WriteToFile(ofstream& fout) const {
	fout << employeeID << ' ' << name << ' ' << surname << ' ' << salary << endl;
}


