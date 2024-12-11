#ifndef EMPLOYEE_SAVOSTIANOV_H
#define EMPLOYEE_SAVOSTIANOV_H
#include <qpainter.h>
#pragma once
#include <string>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_woarchive.hpp>
#include <boost/archive/text_wiarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp >
#include <QString>
#include <QSize>


class Employee_Savostianov
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
    std::string name;
    std::string surname;
	int salary;



public:
    Employee_Savostianov(int employeeID = -1, std::string name = "", std::string surname = "", int salary = 0)
		: employeeID(employeeID), name(name), surname(surname), salary(salary) {}

    ~Employee_Savostianov() {}


	int getEmployeeID() const { return employeeID; }
    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }
	double getSalary() const { return salary; }

	void setEmployeeID(int id) { employeeID = id; }
    void setName(const std::string& n) { name = n; }
    void setSurname(const std::string& s) { surname = s; }
	void setSalary(int sal) { salary = sal; }
    virtual void draw(QPainter& painter, int x, int y, std::vector<int> columnWidths, int cellHeight) const;
    QSize getTextBlockSize(QPainter& painter) const;

    virtual Employee_Savostianov CreateEmployee();
	virtual void ShowInfo() const;

	//template<class Archive>
    std::shared_ptr<Employee_Savostianov> ReadFromFile(std::ifstream& fin);

	//template<class Archive>
    virtual void WriteToFile(std::ofstream& fout) const;


};


class Manager_Savostianov : public Employee_Savostianov {
	friend class boost::serialization::access;
private:
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
        ar& boost::serialization::base_object<Employee_Savostianov>(*this);
		ar& department;
		ar& employees_num;
	}

    std::string department;
	int employees_num;

public:

    Manager_Savostianov(int employeeID = -1, std::string name = "", std::string surname = "", int salary = 0, std::string department = "", int employees_num = 0) :
        Employee_Savostianov(employeeID, name, surname, salary) {
		this->department = department;
		this->employees_num = employees_num;
	}

    Manager_Savostianov CreateManager();
	void ShowInfo() const;
    void setDepartment(std::string dep) { department = dep; }
	void setEmpnum(int emp_num) { employees_num = emp_num; }

    std::string getDepartment() const { return department; }
	double getEmpnum() const { return employees_num; }

    void WriteToFile(std::ofstream& fout) const;
    std::shared_ptr<Manager_Savostianov> ReadFromFile(std::ifstream& fin);
    void draw(QPainter& painter, int x, int y, std::vector<int> columnWidths, int cellHeight) const;
    QSize getTextBlockSize(QPainter& painter) const;
};

#endif
