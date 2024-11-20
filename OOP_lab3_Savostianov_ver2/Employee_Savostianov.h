#pragma once
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_woarchive.hpp>
#include <boost/archive/text_wiarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp >
#include <QString>
#include <QPainter>
#include <QSize>

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
    QString name;
    QString surname;
	int salary;

public:
    Employee(int employeeID = -1, const QString name = "", const QString surname = "", int salary = 0)
		: employeeID(employeeID), name(name), surname(surname), salary(salary) {}

	~Employee() {}

    void draw(QPainter& painter, int x, int y, int width, int height) const {
        QString data = QString("%1\t%2\t%3").arg(name).arg(surname).arg(salary);
        painter.drawText(x, y, width, height, Qt::AlignLeft, data);
    }

    // Подсчёт размеров текстового блока
    QSize calculateSize(const QFontMetrics& metrics) const {
        QString data = QString("%1\t%2\t%3").arg(name).arg(surname).arg(salary);
        return metrics.size(Qt::TextSingleLine, data);
    }


	int getEmployeeID() const { return employeeID; }
    QString getName() const { return name; }
    QString getSurname() const { return surname; }
	double getSalary() const { return salary; }

	void setEmployeeID(int id) { employeeID = id; }
    void setName(const QString& n) { name = n; }
    void setSurname(const QString& s) { surname = s; }
	void setSalary(int sal) { salary = sal; }

	virtual Employee CreateEmployee();
	virtual void ShowInfo() const;

	//template<class Archive>
    std::shared_ptr<Employee> ReadFromFile(std::ifstream& fin);

	//template<class Archive>
    virtual void WriteToFile(std::ofstream& fout) const;


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

    QString department;
	int employees_num;

public:

    Manager(int employeeID = -1, QString name = "", QString surname = "", int salary = 0, QString department = "", int employees_num = 0) :
		Employee(employeeID, name, surname, salary) {
		this->department = department;
		this->employees_num = employees_num;
	}

	Manager CreateManager();
	void ShowInfo() const;
    void setDepartment(QString dep) { department = dep; }
	void setEmpnum(int emp_num) { employees_num = emp_num; }

    QString getDepartment() const { return department; }
	double getEmpnum() const { return employees_num; }

    void WriteToFile(std::ofstream& fout) const;
    std::shared_ptr<Manager> ReadFromFile(std::ifstream& fin);
};
