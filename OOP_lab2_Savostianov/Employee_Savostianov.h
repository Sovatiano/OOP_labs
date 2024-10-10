#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Employee
{
private:
	int employeeID;
	string name;
	string surname;
	int salary;

public:
	Employee(int employeeID = 0, string name = "", string surname = "", int salary = 0)
		: employeeID(employeeID), name(name), surname(surname), salary(salary) {}

	~Employee() {}


	int getEmployeeID() const { return employeeID; }
	string getName() const { return name; }
	string getSurname() const { return surname; }
	double getSalary() const { return salary; }

	void setEmployeeID(int id) { employeeID = id; }
	void setName(const string& n) { name = n; }
	void setSurname(const string& s) { surname = s; }
	void setSalary(int sal) { salary = sal; }

	virtual Employee CreateEmployee();
	virtual void ShowInfo() const;

	Employee ReadFromFile(ifstream& fin);
	void WriteToFile(ofstream& fout) const;
};


class Manager : public Employee {
private:
	string department;
	int employees_num;

public:

	Manager(int employeeID = 0, string name = "", string surname = "", int salary = 0, string department = "", int employees_num = 0) :
		Employee(employeeID, name, surname, salary) {
		this->department = department;
		this->employees_num = employees_num;
	}

	Manager CreateManager();
	void ShowInfo() const;
	void setDepartment(string dep) { department = dep; }
	void setEmpnum(int emp_num) { employees_num = emp_num; }

	string getDepartment() const { return department; }
	double getEmpnum() const { return employees_num; }
};