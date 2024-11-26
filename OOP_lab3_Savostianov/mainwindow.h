#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Department_Savostianov.h"
#include "employeetablemodel_savostianov.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void setDepartmentData(Department_Savostianov* data);

    void updateTable(std::vector<std::shared_ptr<Employee_Savostianov>>);

    void updateRowCount();

private slots:
    void on_addEmployeeButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Department_Savostianov* department = nullptr;
    EmployeeTableModel_Savostianov* employeeModel;
    void onAddEmployeeButtonClicked();
};
#endif // MAINWINDOW_H
