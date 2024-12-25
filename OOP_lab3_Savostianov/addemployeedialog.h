#ifndef ADDEMPLOYEEDIALOG_H
#define ADDEMPLOYEEDIALOG_H

#include <QDialog>
#include "employeetablemodel_savostianov.h"
#include "Department_Savostianov.h"
#include "mainwindow.h"

namespace Ui {
class addemployeedialog;
}

class addemployeedialog : public QDialog
{
    Q_OBJECT

public:
    explicit addemployeedialog(Department_Savostianov* department, EmployeeTableModel_Savostianov* mainwin_model, QWidget *parent = nullptr);
    ~addemployeedialog();

    int getId() const;
    QString getName() const;
    QString getSurname() const;
    int getSalary() const;
    bool isManager() const;
    QString getDepartment() const;
    int getEmpNum() const;
    void onRowSelected(const QModelIndex &current, const QModelIndex &previous);
    Department_Savostianov* dial_dep = nullptr;
    EmployeeTableModel_Savostianov* mainwin_mod = nullptr;

private slots:
    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_removeButton_clicked();

private:
    Ui::addemployeedialog *ui;
    EmployeeTableModel_Savostianov* employeeModel;
};

#endif // ADDEMPLOYEEDIALOG_H
