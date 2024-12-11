#ifndef TABLEWIDGET_SAVOSTIANOV_H
#define TABLEWIDGET_SAVOSTIANOV_H

#include <QWidget>
#include <QString>
#include <QPainter>
#include "Department_Savostianov.h"
#include "Employee_Savostianov.h"

class TableWidget_Savostianov : public QWidget {
    Q_OBJECT

private:
    Department_Savostianov* department;
    int headerHeight = 30; // Высота заголовков таблицы
    int cellHeight = 25;   // Высота строки
    std::vector<int> columnWidths; // Ширина столбцов

    // Вычисление ширины столбцов
    void calculateColumnWidths();

public:
    TableWidget_Savostianov(Department_Savostianov* department, QWidget* parent = nullptr);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

};

#endif // TABLEWIDGET_SAVOSTIANOV_H
