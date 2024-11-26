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
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
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


void MainWindow::updateTable(std::vector<std::shared_ptr<Employee_Savostianov>>) {
    employeeModel->fillTable(employeeModel, department->employees);
    ui->tableView->setModel(employeeModel);
    ui->tableView->resizeColumnsToContents();
    updateRowCount();
}

void MainWindow::updateRowCount() {
    int rowCount = employeeModel->rowCount();
    ui->rowCountLabel->setText(QString("Количество строк: %1").arg(rowCount));
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

        updateTable(department->employees);
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "",
                                                    tr("Text Files (*.txt);;All Files (*)"));

    department->loadFromFile(fileName.toStdString());
    updateTable(department->employees);
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
    updateTable(department->employees);
}


void MainWindow::on_pushButton_2_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows(); // Только индексы строк

    if (selectedRows.empty()) {
        QMessageBox::warning(this, "Ошибка", "Выберите строки для удаления.");
        return;
    }

    // Сортируем индексы в обратном порядке, чтобы не нарушать последовательность при удалении
    std::sort(selectedRows.begin(), selectedRows.end(), [](const QModelIndex &a, const QModelIndex &b) {
        return a.row() > b.row();
    });

    // Удаляем строки из модели
    for (const QModelIndex &index : selectedRows) {
        employeeModel->removeRows(index.row(), 1, QModelIndex());
    }
    ui->tableView->setModel(employeeModel);
    ui->tableView->resizeColumnsToContents();
    updateRowCount();
}

