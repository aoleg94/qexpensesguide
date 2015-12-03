#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include "addoperationdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addRegular();
    void addOperation();
    void updateModels();
private:
    Ui::MainWindow *ui;
    void addRow(const Result &r, bool regular);
    double dailyIncrement;
};

#endif // MAINWINDOW_H
