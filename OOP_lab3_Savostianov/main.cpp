#include "Department_Savostianov.h"
#include <Windows.h>
#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setlocale(LC_CTYPE, "Russian");
    Department_Savostianov department;

    QApplication app(argc, argv); // Создание объекта приложения.

    MainWindow mainWindow;        // Создание основного окна.
    mainWindow.setDepartmentData(&department);
    mainWindow.show();            // Отображение основного окна.

    return app.exec();

}
