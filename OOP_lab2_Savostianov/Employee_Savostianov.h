#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_woarchive.hpp>
#include <boost/archive/text_wiarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp >

using namespace std;

class Employee
{
	friend class boost::serialization::access;
private:
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& employeeID;
		ar& name;
		ar& surname;
		ar& salary;
	}
	int employeeID;
	string name;
	string surname;
	int salary;

public:
	Employee(int employeeID = -1, string name = "", string surname = "", int salary = 0)
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

	//template<class Archive>
	shared_ptr<Employee> ReadFromFile(ifstream& fin);

	//template<class Archive>
	virtual void WriteToFile(ofstream& fout) const;
};


class Manager : public Employee {
	friend class boost::serialization::access;
private:
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Employee>(*this);
		ar& department;
		ar& employees_num;
	}

	string department;
	int employees_num;

public:

	Manager(int employeeID = -1, string name = "", string surname = "", int salary = 0, string department = "", int employees_num = 0) :
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

	void WriteToFile(ofstream& fout) const;
	shared_ptr<Manager> ReadFromFile(ifstream& fin);
};