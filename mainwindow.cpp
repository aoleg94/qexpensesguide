#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addoperationdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("data");
        bool ok = db.open();
        Q_ASSERT(ok);
        QSqlQuery iq;
        ok = iq.exec("CREATE TABLE IF NOT EXISTS ops(id integer primary key autoincrement, "
                     "time integer, value real, comment text, category text);");
        Q_ASSERT(ok);
        ok = iq.exec("CREATE TABLE IF NOT EXISTS reg(id integer primary key autoincrement, "
                     "period integer, value real, comment text, category text);");
        Q_ASSERT(ok);
        ok = iq.exec("SELECT total(value/period) FROM reg;");
        Q_ASSERT(ok);
        Q_ASSERT(iq.size() <= 1);
        iq.next();
        dailyIncrement = iq.value(0).value<double>();
    }
    ui->setupUi(this);
    connect(ui->btnAdd, SIGNAL(clicked(bool)), this, SLOT(addOperation()));
    connect(ui->btnAddOp, SIGNAL(clicked(bool)), this, SLOT(addOperation()));
    connect(ui->btnAddRegular, SIGNAL(clicked(bool)), this, SLOT(addRegular()));

    QSqlQueryModel* sqm = new QSqlQueryModel(this);
    sqm->setQuery("SELECT value, datetime(time, 'unixepoch', 'localtime'), category, comment FROM ops;");
    ui->tblOps->setModel(sqm);

    /*sqm = new QSqlQueryModel(this);
    sqm->setQuery("SELECT value, time, category, comment FROM reg;");
    ui->tblRegular->setModel(sqm);*/
}

MainWindow::~MainWindow()
{
    QSqlDatabase::database().close();
    delete ui;
}

void MainWindow::updateModels()
{
    {
        QSqlQueryModel* sqm = qobject_cast<QSqlQueryModel*>(ui->tblOps->model());
        Q_ASSERT(sqm);
        QSqlQuery q = sqm->query();
        q.finish();
        bool ok = q.exec();
        Q_ASSERT(ok);
        sqm->setQuery(q);
    }
    /*{
        QSqlQueryModel* sqm = qobject_cast<QSqlQueryModel*>(ui->tblRegular->model());
        Q_ASSERT(sqm);
        QSqlQuery q = sqm->query();
        q.finish();
        bool ok = q.exec();
        Q_ASSERT(ok);
        sqm->setQuery(q);
    }*/
}

void MainWindow::addRow(const Result& r, bool regular)
{
    QSqlQuery q;
    q.prepare(QStringLiteral("INSERT INTO %1 VALUES(?,?,?,?);")
              .arg(regular ? "regular" : "ops"));
    q.addBindValue(r.time.toTime_t());
    q.addBindValue(r.value);
    q.addBindValue(r.comment);
    q.addBindValue(r.category);
    bool ok = q.exec();
    Q_ASSERT(ok);
}

void MainWindow::addRegular()
{
    /*AddOperationDialog aod(this);
    if(aod.exec() == QDialog::Accepted)
    {
        Result r = aod.getResult();
        addRow(r, true);
        updateModels();
    }*/
}

void MainWindow::addOperation()
{
    AddOperationDialog aod(this);
    if(aod.exec() == QDialog::Accepted)
    {
        Result r = aod.getResult();
        addRow(r, false);
        updateModels();
    }
}
