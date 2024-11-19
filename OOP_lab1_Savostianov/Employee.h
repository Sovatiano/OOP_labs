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
		Employee(int employeeID=0, string name="", string surname="", int salary=0)
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

		Employee CreateEmployee();
		void ShowInfo() const;

		Employee ReadFromFile(ifstream& fin);
		void WriteToFile(ofstream& fout) const;
};
