#include "addemployeedialog.h"
#include "ui_addemployeedialog.h"
#include <QItemSelectionModel>
#include <QStandardItemModel>

addemployeedialog::addemployeedialog(Department_Savostianov* department, EmployeeTableModel_Savostianov* mainwin_model, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addemployeedialog)
    , employeeModel(new EmployeeTableModel_Savostianov(this))
{
    ui->setupUi(this);

    ui->empNumLabel->setVisible(false);
    ui->empNumBox->setVisible(false);
    ui->departmentLabel->setVisible(false);
    ui->departmentEdit->setVisible(false);

    dial_dep = department;
    mainwin_mod = mainwin_model;

    ui->tableView->setModel(employeeModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    employeeModel->fillTable(employeeModel, department->employees);
    ui->tableView->resizeColumnsToContents();
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &addemployeedialog::onRowSelected);

    // Показываем/прячем поле для числа подчинённых в зависимости от типа сотрудника
    connect(ui->isManager, &QCheckBox::toggled, this, [this](bool checked) {
        ui->empNumLabel->setVisible(checked);
        ui->empNumBox->setVisible(checked);
        ui->departmentLabel->setVisible(checked);
        ui->departmentEdit->setVisible(checked);
});

}
addemployeedialog::~addemployeedialog()
{
    delete ui;
}


int addemployeedialog::getId() const {
    return ui->idBox->value();
}

QString addemployeedialog::getName() const {
    return ui->nameEdit->text();
}

QString addemployeedialog::getSurname() const {
    return ui->surnameEdit->text();
}

int addemployeedialog::getSalary() const {
    return ui->salaryBox->value();
}

bool addemployeedialog::isManager() const {
    return ui->isManager->isChecked();
}

QString addemployeedialog::getDepartment() const {
    return ui->departmentEdit->text();
}
int addemployeedialog::getEmpNum() const {
    return ui->empNumBox->value();
}

void addemployeedialog::onRowSelected(const QModelIndex &current, const QModelIndex &previous) {
    Q_UNUSED(previous);

    // Получаем модель данных
    QAbstractTableModel *model = qobject_cast<QAbstractTableModel *>(ui->tableView->model());


    if (current.isValid()) {
        ui->idBox->setValue((model->data(model->index(current.row(), 0)).toInt()));
        ui->nameEdit->setText(model->data(model->index(current.row(), 1)).toString());
        ui->surnameEdit->setText(model->data(model->index(current.row(), 2)).toString());
        ui->salaryBox->setValue((model->data(model->index(current.row(), 3)).toInt()));
    } else {
        // Очищаем QLineEdit, если строка не выбрана
        ui->idBox->clear();
        ui->nameEdit->clear();
        ui->surnameEdit->clear();
        ui->salaryBox->clear();
    }

    if (typeid(*dial_dep->employees[current.row()].get()) == typeid(Manager_Savostianov)) {
        ui->isManager->setChecked(true);
        ui->departmentEdit->setText(model->data(model->index(current.row(), 4)).toString());
        ui->empNumBox->setValue((model->data(model->index(current.row(), 5)).toInt()));
    }
    else {
        ui->isManager->setChecked(false);
    }
}

void addemployeedialog::on_addButton_clicked()
{
    if (!ui->isManager->isChecked()) {
    int id = ui->idBox->value();
    QString name = ui->nameEdit->text();
    QString surname = ui->surnameEdit->text();
    int salary = ui->salaryBox->value();

    std::shared_ptr<Employee_Savostianov> new_ptr{ std::make_shared<Employee_Savostianov>(Employee_Savostianov(id, name.toStdString(), surname.toStdString(), salary))};
    dial_dep->employees.push_back(new_ptr);
    employeeModel->fillTable(employeeModel, dial_dep->employees);
    }
    else {
        int id = ui->idBox->value();
        QString name = ui->nameEdit->text();
        QString surname = ui->surnameEdit->text();
        int salary = ui->salaryBox->value();
        QString department = ui->departmentEdit->text();
        int empNum = ui->empNumBox->value();

        std::shared_ptr<Manager_Savostianov> new_ptr{ std::make_shared<Manager_Savostianov>(Manager_Savostianov(id, name.toStdString(), surname.toStdString(), salary, department.toStdString(), empNum))};
        dial_dep->employees.push_back(new_ptr);
        employeeModel->fillTable(employeeModel, dial_dep->employees);
        mainwin_mod->fillTable(employeeModel, dial_dep->employees);
    }

    int newRow = dial_dep->employees.size() - 1;
    QModelIndex newIndex = employeeModel->index(newRow, 0);
    ui->tableView->setCurrentIndex(newIndex);
    onRowSelected(newIndex, newIndex);
}


void addemployeedialog::on_editButton_clicked()
{
    QModelIndex currentIndex = ui->tableView->selectionModel()->currentIndex();
    if (currentIndex.isValid()) {
        // Получаем данные из QLineEdit
        int id = ui->idBox->value();
        QString name = ui->nameEdit->text();
        QString surname = ui->surnameEdit->text();
        int salary = ui->salaryBox->value();

        int ind = currentIndex.row();
        dial_dep->employees[ind]->setEmployeeID(id);
        dial_dep->employees[ind]->setName(name.toStdString());
        dial_dep->employees[ind]->setSurname(surname.toStdString());
        dial_dep->employees[ind]->setSalary(salary);
        if (typeid(*dial_dep->employees[ind].get()) == typeid(Manager_Savostianov)) {
            QString department = ui->departmentEdit->text();
            int empNum = ui->empNumBox->value();
            if (auto manager = std::dynamic_pointer_cast<Manager_Savostianov>(dial_dep->employees[ind])) {
                manager->setDepartment(department.toStdString());
                manager->setEmpnum(empNum);
            }
        }
        employeeModel->fillTable(employeeModel, dial_dep->employees);


        // Устанавливаем данные в модель
    } else {
        // Если строка не выбрана, выводим сообщение
        qWarning() << "No row selected!";
    }
}


void addemployeedialog::on_removeButton_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows(); // Только индексы строк


    // Сортируем индексы в обратном порядке, чтобы не нарушать последовательность при удалении
    std::sort(selectedRows.begin(), selectedRows.end(), [](const QModelIndex &a, const QModelIndex &b) {
        return a.row() > b.row();
    });
    ui->tableView->setModel(employeeModel);
    ui->tableView->resizeColumnsToContents();
    for (const QModelIndex &index : selectedRows) {
        int row = index.row();

        // Удаляем объект из department->employees
        if (row < dial_dep->employees.size()) {
            dial_dep->employees.erase(dial_dep->employees.begin() + row);
        }
    }
    employeeModel->fillTable(employeeModel, dial_dep->employees);
    if (!selectedRows.isEmpty()) {
        int lastRemovedRow = selectedRows.first().row();
        int newRow = std::min<int>(lastRemovedRow, dial_dep->employees.size() - 1);
        QModelIndex newIndex = employeeModel->index(newRow, 0);
        ui->tableView->setCurrentIndex(newIndex);
        onRowSelected(newIndex, newIndex);
    }
}

