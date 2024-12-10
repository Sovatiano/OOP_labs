#include "tablewidget_savostianov.h"

void TableWidget_Savostianov::updateWidgetSize() {
    if (department) {
        int totalHeight = headerHeight + department->employees.size() * cellHeight;
        setFixedSize(2 * cellWidth, totalHeight);
    }
}


void TableWidget_Savostianov::paintEvent(QPaintEvent *event) {
    if (!department) return;

    QPainter painter(this);
    const auto &items = department->employees;

    // Отрисовка заголовков
    painter.setBrush(Qt::lightGray);
    painter.drawRect(0, 0, width(), headerHeight);
    painter.drawText(10, 20, "Name");
    painter.drawText(cellWidth + 10, 20, "Value");

    // Отрисовка содержимого
    int y = headerHeight;
    for (size_t i = 0; i < items.size(); ++i) {
        std::shared_ptr<Employee_Savostianov> item = items[i];

        // Чередование цвета строк
        if (i % 2 == 0)
            painter.setBrush(Qt::white);
        else
            painter.setBrush(Qt::lightGray);

        // Рисуем строку
        painter.drawRect(0, y, width(), cellHeight);
        painter.drawText(10, y + 20, QString::fromStdString(item->getName()));
        painter.drawText(cellWidth + 10, y + 20, QString::number(item->getSalary()));

        y += cellHeight;
    }
}


QSize TableWidget_Savostianov::sizeHint() const {
    // Размер виджета зависит от количества элементов
    return QSize(2 * cellWidth, headerHeight + department->employees.size() * cellHeight);
}
