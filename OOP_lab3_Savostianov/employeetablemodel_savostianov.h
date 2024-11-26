#ifndef EMPLOYEETABLEMODEL_SAVOSTIANOV_H
#define EMPLOYEETABLEMODEL_SAVOSTIANOV_H

#include <QAbstractTableModel>
#include <vector>
#include <memory>
#include "employee_savostianov.h"

class EmployeeTableModel_Savostianov : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit EmployeeTableModel_Savostianov(QObject* parent = nullptr);

    void setEmployees(const std::vector<std::shared_ptr<Employee_Savostianov>>& employees);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool removeRows(int row, int count, const QModelIndex &parent) override;

    void addEmployee(const std::shared_ptr<Employee_Savostianov> &employee) {
        int row = employees.size();
        beginInsertRows(QModelIndex(), row, row);  // Уведомляем о вставке строки
        employees.push_back(employee);             // Добавляем в вектор
        endInsertRows();                           // Завершаем вставку строки
    }

    void fillTable(EmployeeTableModel_Savostianov* model, const std::vector<std::shared_ptr<Employee_Savostianov>>& employeeList) {
        std::for_each(employeeList.begin(), employeeList.end(),
                      std::bind(&EmployeeTableModel_Savostianov::addEmployee, model, std::placeholders::_1));
    }



private:
    std::vector<std::shared_ptr<Employee_Savostianov>> employees; // Хранилище данных
};

#endif // EMPLOYEETABLEMODEL_SAVOSTIANOV_H
