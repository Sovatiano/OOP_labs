#ifndef TABLEWIDGET_SAVOSTIANOV_H
#define TABLEWIDGET_SAVOSTIANOV_H

#include <QWidget>
#include <QString>
#include <QPainter>
#include "Department_Savostianov.h"
#include "Employee_Savostianov.h"

class TableWidget_Savostianov : public QWidget
{
private:
    Department_Savostianov *department;
    int cellWidth;
    int cellHeight;
    int headerHeight;

public:
    explicit TableWidget_Savostianov(Department_Savostianov *c, QWidget *parent = nullptr)
        : QWidget(parent), department(c), cellWidth(100), cellHeight(30), headerHeight(40) {
        // Устанавливаем фиксированный размер на основе количества элементов
        updateWidgetSize();
    }

    void updateWidgetSize();
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // TABLEWIDGET_SAVOSTIANOV_H
