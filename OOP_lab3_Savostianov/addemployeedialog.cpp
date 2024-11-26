#include "addemployeedialog.h"
#include "ui_addemployeedialog.h"

addemployeedialog::addemployeedialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addemployeedialog)
{
    ui->setupUi(this);

    ui->empNumLabel->setVisible(false);
    ui->empNumBox->setVisible(false);
    ui->departmentLabel->setVisible(false);
    ui->departmentEdit->setVisible(false);

    connect(ui->buttonBox_2, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox_2, &QDialogButtonBox::rejected, this, &QDialog::reject);

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
