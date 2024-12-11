#include "tablewidget_savostianov.h"

TableWidget_Savostianov::TableWidget_Savostianov(Department_Savostianov* department, QWidget* parent)
    : QWidget(parent), department(department) {
}


void TableWidget_Savostianov::paintEvent(QPaintEvent* event) {
    if (!department) return;

    QPainter painter(this);
    int y = 0;
    int x = 0;
    int cellHeight = 40;

    std::vector<int> columnWidths = department->getColumnWidths(painter);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);

    painter.drawRect(x, y, columnWidths[0] + 20, cellHeight);
    painter.drawText(QRect(x, y, columnWidths[0], cellHeight), Qt::AlignCenter, "ID");
    x += columnWidths[0] + 20;
    painter.drawRect(x, y, columnWidths[1] + 20, cellHeight);
    painter.drawText(QRect(x, y, columnWidths[1], cellHeight), Qt::AlignCenter, "Имя");
    x += columnWidths[1] + 20;
    painter.drawRect(x, y, columnWidths[2 + 20], cellHeight);
    painter.drawText(QRect(x, y, columnWidths[2], cellHeight), Qt::AlignCenter, "Фамилия");
    x += columnWidths[2] + 20;
    painter.drawRect(x, y, columnWidths[3] + 20, cellHeight);
    painter.drawText(QRect(x, y, columnWidths[3], cellHeight), Qt::AlignCenter, "Зарплата");
    x += columnWidths[3] + 20;
    painter.drawRect(x, y, columnWidths[4] + 20, cellHeight);
    painter.drawText(QRect(x, y, columnWidths[4], cellHeight), Qt::AlignCenter, "Отдел");
    x += columnWidths[4] + 20;
    painter.drawRect(x, y, columnWidths[5] + 20, cellHeight);
    painter.drawText(QRect(x, y, columnWidths[5], cellHeight), Qt::AlignCenter, "Число подчинённых");

    y += cellHeight;
    x = 0;

    std::for_each(department->employees.begin(), department->employees.end(), [&painter, &y, &x, &columnWidths, &cellHeight](const std::shared_ptr<Employee_Savostianov>& item) {
        item->draw(painter, x, y, columnWidths, cellHeight);
        y += 40;
    });

    int table_width = std::accumulate(columnWidths.begin(), columnWidths.end(), 0) + 120;
    painter.drawLine(table_width - 1, 0, table_width - 1, (department->employees.size() + 1) * cellHeight);
    QSize sizeHint = QSize(columnWidths[0] + columnWidths[1] + columnWidths[2] + columnWidths[3] + columnWidths[4] + columnWidths[5] + 120, y);
    setFixedSize(sizeHint);
}

QSize TableWidget_Savostianov::sizeHint() const {
    if (!department) return QSize(0, 0);

    QPainter painter;
    int totalHeight = 0;
    int maxWidth = 0;
    int cellHeight = 40;

    // Получаем максимальный размер для каждого столбца
    std::vector<int> columnWidths = department->getColumnWidths(painter);


    maxWidth = columnWidths[0] + columnWidths[1] + columnWidths[2] + columnWidths[3] + columnWidths[4] + columnWidths[5];
    totalHeight = department->employees.size() * cellHeight + 40; // Включая заголовок

    return QSize(maxWidth, totalHeight);
}


void TableWidget_Savostianov::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    update(); // Перерисовать таблицу
}
