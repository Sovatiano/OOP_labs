#include "Employee_Savostianov.h"
#include "BooleanFuncs.h"
#include <vector>
#include <sstream>

BOOST_CLASS_EXPORT(Manager)
BOOST_CLASS_EXPORT(Employee)


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


//template<class Archive>
shared_ptr<Employee> Employee::ReadFromFile(ifstream& fin) {
	boost::archive::text_iarchive ia(fin);
	shared_ptr<Employee> new_ptr;
	ia >> new_ptr;
	return new_ptr;
}


//template<class Archive>
void Employee::WriteToFile(ofstream& fout) const {
	shared_ptr<Employee> new_ptr{ make_shared<Employee>(*this) };
	boost::archive::text_oarchive oa(fout);
	oa << new_ptr;
}


Manager Manager::CreateManager() {
	string department;
	string employees_num;
	Employee new_emp = Employee::CreateEmployee();

	cout << "Введите название отдела, в котром работает менеджер: ";
	getline(cin, department);

	while (true) {
		cout << "Введите количество подчинённых менеджера: ";
		getline(cin, employees_num);
		if (isInteger(employees_num) && stoi(employees_num) > 0) {
			break;
		}
		else {
			cout << "Неверный ввод. Введите положительное целое число." << endl;
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
	cout << "Отдел: " << department << ", "
		<< "Количество подчинённых: " << employees_num << endl;
}

void Manager::WriteToFile(ofstream& fout) const {
	shared_ptr<Manager> new_ptr{ make_shared<Manager>(*this) };
	boost::archive::text_oarchive oa(fout);
	oa << new_ptr;
}

shared_ptr<Manager> Manager::ReadFromFile(ifstream& fin) {
	boost::archive::text_iarchive ia(fin);
	shared_ptr<Manager> new_ptr;
	ia >> new_ptr;
	return new_ptr;
}