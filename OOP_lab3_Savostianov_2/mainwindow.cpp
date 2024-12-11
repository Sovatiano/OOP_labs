#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Department_Savostianov* department = new Department_Savostianov;
    department->fillTest();

    QTabWidget *tabWidget = new QTabWidget(this);

    TableWidget_Savostianov* tableWidget = new TableWidget_Savostianov(department);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidget(tableWidget);
    scrollArea->setWidgetResizable(true);

    tabWidget->addTab(scrollArea, "Таблица");

    QWidget* buttonTab = new QWidget();
    QVBoxLayout* buttonLayout = new QVBoxLayout(buttonTab);

    QPushButton* save_button = new QPushButton("Сохранить данные", buttonTab);
    QPushButton* load_button = new QPushButton("Загрузить данные", buttonTab);

    buttonLayout->addWidget(save_button);
    buttonLayout->addWidget(load_button);

    connect(save_button, &QPushButton::clicked, this, &MainWindow::on_save_button_clicked);
    connect(load_button, &QPushButton::clicked, this, &MainWindow::on_load_button_clicked);

    // Добавляем вторую вкладку с кнопками
    tabWidget->addTab(buttonTab, "Сохранить/Загрузить");

    // Устанавливаем QTabWidget как центральный виджет
    setCentralWidget(tabWidget);

    // setCentralWidget(scrollArea);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_load_button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "",
                                                    tr("Text Files (*.txt);;All Files (*)"));

    department->loadFromFile(fileName.toStdString());
    updateTable(department->employees);
}


void MainWindow::on_save_button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "",
                                                    tr("Text Files (*.txt);;All Files (*)"));

    department->saveToFile(fileName.toStdString());
}

void MainWindow::updateTable(std::vector<std::shared_ptr<Employee_Savostianov>>) {
    tableWidget->update();
}
