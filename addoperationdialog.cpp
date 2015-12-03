#include "addoperationdialog.h"
#include "ui_addoperationdialog.h"
#include "QStyleFactory"

AddOperationDialog::AddOperationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOperationDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog);
    qApp->setStyle(QStyleFactory::create("fusion"));
}

AddOperationDialog::~AddOperationDialog()
{
    delete ui;
}

Result AddOperationDialog::getResult() const
{
    Result r;
    r.value = ui->spinMoney->value();
    r.category = ui->comboCategory->currentText();
    r.comment = ui->lineComment->text();
    r.time = QDateTime::currentDateTime();
    return r;
}

void AddOperationDialog::on_spinMoney_valueChanged(double d)
{
    ui->spinMoney->setPrefix(d > 0 ? "+" : "");
}
