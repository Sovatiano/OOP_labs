#include <QMainWindow>
#include <QFileDialog>
#include <QPainter>
#include "Department_Savostianov.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoad();
    void onSave();
    void onClear();
    void onPaint();

private:
    Ui::MainWindow *ui;
    Department department;
};
