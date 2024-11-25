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

private:
    std::vector<std::shared_ptr<Employee_Savostianov>> employees; // Хранилище данных
};

#endif // EMPLOYEETABLEMODEL_SAVOSTIANOV_H
