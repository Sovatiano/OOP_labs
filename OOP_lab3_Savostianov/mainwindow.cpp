#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addemployeedialog.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , employeeModel(new EmployeeTableModel_Savostianov(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(employeeModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setDepartmentData(Department_Savostianov* newDepartment) {
    this->department = newDepartment;

    if (newDepartment) {
        employeeModel->setEmployees(newDepartment->employees); // Передаём данные модели
    }
}

void MainWindow::on_addEmployeeButton_clicked()
{
    addemployeedialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        int empID = dialog.getId();
        std::string name = dialog.getName().toStdString();
        std::string surname = dialog.getSurname().toStdString();
        int salary = dialog.getSalary();

        if (dialog.isManager()) {
            std::string dep_name = dialog.getDepartment().toStdString();
            int empNum = dialog.getEmpNum();
            department->employees.push_back(std::make_shared<Manager_Savostianov>(empID, name, surname, salary, dep_name, empNum));
        } else {
            department->employees.push_back(std::make_shared<Employee_Savostianov>(empID, name, surname, salary));
        }

        // Обновляем таблицу
        employeeModel->setEmployees(department->employees);
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "",
                                                    tr("Text Files (*.txt);;All Files (*)"));

    department->loadFromFile(fileName.toStdString());
    employeeModel->setEmployees(department->employees);
}


void MainWindow::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "",
                                                    tr("Text Files (*.txt);;All Files (*)"));

    department->saveToFile(fileName.toStdString());
}


void MainWindow::on_pushButton_5_clicked()
{
    department->clearEmployees();
    employeeModel->setEmployees(department->employees);
}


void MainWindow::on_pushButton_2_clicked()
{
    QModelIndex currentIndex = ui->tableView->currentIndex();

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Выберите строку для удаления.");
        return;
    }

    employeeModel->removeRows(currentIndex.row(), 1, QModelIndex());
}

