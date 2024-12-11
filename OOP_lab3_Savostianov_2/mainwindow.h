#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Department_Savostianov.h"
#include "Employee_Savostianov.h"
#include "tablewidget_savostianov.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QApplication>
#include <QTabWidget>
#include <QPushButton>
#include <QFileDialog>

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
    void updateTable(std::vector<std::shared_ptr<Employee_Savostianov>>);
    void setDepartmentData(Department_Savostianov* newDepartment);

private:
    Ui::MainWindow *ui;
    Department_Savostianov* department = nullptr;
    TableWidget_Savostianov* tableWidget = new TableWidget_Savostianov(department);
    void on_save_button_clicked();
    void on_load_button_clicked();
};
#endif // MAINWINDOW_H
