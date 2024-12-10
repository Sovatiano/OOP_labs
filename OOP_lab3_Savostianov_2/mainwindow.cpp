#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Department_Savostianov department;
    department.fillTest();
    TableWidget_Savostianov *table_widget = new TableWidget_Savostianov(&department);

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(table_widget);
    scrollArea->setWidgetResizable(true);


    setCentralWidget(scrollArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}
