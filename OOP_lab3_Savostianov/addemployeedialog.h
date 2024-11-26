#ifndef ADDEMPLOYEEDIALOG_H
#define ADDEMPLOYEEDIALOG_H

#include <QDialog>

namespace Ui {
class addemployeedialog;
}

class addemployeedialog : public QDialog
{
    Q_OBJECT

public:
    explicit addemployeedialog(QWidget *parent = nullptr);
    ~addemployeedialog();

    int getId() const;
    QString getName() const;
    QString getSurname() const;
    int getSalary() const;
    bool isManager() const;
    QString getDepartment() const;
    int getEmpNum() const;

private:
    Ui::addemployeedialog *ui;
};

#endif // ADDEMPLOYEEDIALOG_H
