#include "employeetablemodel_savostianov.h"

EmployeeTableModel_Savostianov::EmployeeTableModel_Savostianov(QObject* parent)
    : QAbstractTableModel(parent) {}

void EmployeeTableModel_Savostianov::setEmployees(const std::vector<std::shared_ptr<Employee_Savostianov>>& employees) {
    beginResetModel(); // Уведомление об обновлении модели
    this->employees = employees;
    endResetModel();
}

int EmployeeTableModel_Savostianov::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return employees.size(); // Количество строк равно количеству сотрудников
}

int EmployeeTableModel_Savostianov::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return 6;
}

QVariant EmployeeTableModel_Savostianov::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) return QVariant();

    const auto& employee = employees[index.row()];
    switch (index.column()) {
    case 0: return employee->getEmployeeID();
    case 1: return QString::fromStdString(employee->getName());
    case 2: return QString::fromStdString(employee->getSurname());
    case 3: return employee->getSalary();
    case 4: { // Подчинённые
        auto manager = dynamic_cast<Manager_Savostianov*>(employee.get());
        if (manager) {
            return QString::fromStdString(manager->getDepartment()); // Поле для менеджера
        } else {
            return "—"; // Пустое значение для обычного сотрудника
        }
    }
    case 5: { // Подчинённые
        auto manager = dynamic_cast<Manager_Savostianov*>(employee.get());
        if (manager) {
            return manager->getEmpnum(); // Поле для менеджера
        } else {
            return "—"; // Пустое значение для обычного сотрудника
        }
    }
    default: return QVariant();
    }
}

QVariant EmployeeTableModel_Savostianov::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "ID";
        case 1: return "Имя";
        case 2: return "Фамилия";
        case 3: return "Зарплата";
        case 4: return "Отдел";
        case 5: return "Количество Подчинённых";
        default: return QVariant();
        }
    }
    return QVariant();
}


bool EmployeeTableModel_Savostianov::removeRows(int row, int count, const QModelIndex &parent) {
    if (row < 0 || row >= employees.size() || count <= 0)
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        employees.erase(employees.begin() + row);  // dataList — контейнер с вашими данными
    }
    endRemoveRows();
    return true;
}
