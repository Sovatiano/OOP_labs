#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onLoad);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSave);
    connect(ui->actionClear, &QAction::triggered, this, &MainWindow::onClear);
    connect(ui->actionPaint, &QAction::triggered, this, &MainWindow::onPaint);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onLoad() {
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить файл", "", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        department.loadFromFile(fileName);
    }
}

void MainWindow::onSave() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        department.saveToFile(fileName);
    }
}

void MainWindow::onClear() {
    department.removeAll();
    QMessageBox::information(this, "Очищено", "Все данные удалены.");
}

void MainWindow::onPaint() {
    QPainter painter(this);
    QFontMetrics metrics(painter.font());
    int y = 20;

    department.forEachEmployee([&](const Employee& employee) {
        employee.draw(painter, 10, y, this->width());
        y += metrics.height();
    });
}
