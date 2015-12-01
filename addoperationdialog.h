#ifndef ADDOPERATIONDIALOG_H
#define ADDOPERATIONDIALOG_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class AddOperationDialog;
}

struct Result
{
    double value;
    QDateTime time;
    QString category, comment;
};

class AddOperationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOperationDialog(QWidget *parent = 0);
    ~AddOperationDialog();
    Result getResult() const;
private slots:
    void on_spinMoney_valueChanged(double d);
private:
    Ui::AddOperationDialog *ui;
};

#endif // ADDOPERATIONDIALOG_H
