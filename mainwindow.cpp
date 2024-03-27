#include <QSqlQueryModel>
#include <QSqlQuery>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_delete_2_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    connOpen();

    QString id = ui->comboBox->currentText();
    QSqlQuery qry(mydb); // Do NOT allocate on the heap

    qry.prepare("DELETE FROM bookings where passengerid='"+id+"'");
    qry.exec();
    model->setQuery(std::move(qry));
    ui->tableView->setModel(model);
    connClose();

    qDebug()<<(model->rowCount());

}




void MainWindow::on_pushButton_2_clicked()
{
    QString passnum= ui->lineEdit->text();
    QString refnum = ui->lineEdit_2->text();

    connOpen();
    QSqlQuery qry;
    QString temp = "INSERT into bookings (passengerid,ReferenceNum) values ('"+passnum+"','"+refnum+"')";
    qry.prepare(temp);
    qry.exec();



    connClose();
}


void MainWindow::on_load_btn_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    connOpen();
    QSqlQuery qry(mydb); // Do NOT allocate on the heap
    qry.prepare("select * FROM bookings");
    qry.exec();
    model->setQuery(std::move(qry));
    ui->tableView->setModel(model);
    connClose();

    QSqlQueryModel *newmodel = new QSqlQueryModel();
    connOpen();


    QSqlQuery new_qry(mydb); // Do NOT allocate on the heap

    new_qry.prepare("select passengerid FROM bookings");
    new_qry.exec();
    newmodel->setQuery(std::move(new_qry));
    ui->comboBox->setModel(newmodel);
    connClose();



    // QSqlQuery qry = *new QSqlQuery (mydb);
    // qry.prepare("select * from tbl_bookings");

    //  qDebug()<<qry.exec()<<"debug";

    qDebug()<<(model->rowCount());
}


void MainWindow::on_putDBtoCombobox_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    connOpen();


    QSqlQuery qry(mydb); // Do NOT allocate on the heap

    qry.prepare("select passengerid FROM bookings");
    qry.exec();
    model->setQuery(std::move(qry));
    ui->comboBox->setModel(model);
    connClose();
    // QSqlQuery qry = *new QSqlQuery (mydb);
    // qry.prepare("select * from tbl_bookings");

    //  qDebug()<<qry.exec()<<"debug";

    qDebug()<<(model->rowCount());
    connClose();
}


void MainWindow::on_test_btn_clicked()
{
    connOpen();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM bookings LIMIT 1");
    qry.exec();

    if (qry.next()) {
        // Assuming 'bookings' table has columns named 'column1', 'column2', etc.
        // You would replace these with the actual column names from your table
        QVariant value1 = qry.value(0);  // Get the value of the first column
        QVariant value2 = qry.value(1);  // Get the value of the second column
        // Repeat for other columns as needed...

        // You can then use these values as needed, for example:
        QString stringValue1 = value1.toString();  // Convert to QString if it's a string
        int intValue2 = value2.toInt();            // Convert to int if it's an integer
        qDebug()<<stringValue1<<intValue2<<"it worked";
        // Now you can use stringValue1, intValue2, etc. in your code
    } else {
        // Handle the case where no rows were returned
        qDebug() << "No rows returned from the query.";
    }
    // connClose();


    // connOpen();

}


void MainWindow::on_count_rows_clicked()
{
    connOpen();
    QSqlQuery qry;
    qry.prepare("SELECT COUNT(*) FROM bookings"); // Counts Rows in SQLITE
    qry.exec();

    if (qry.next()) {
        int rowCount = qry.value(0).toInt();
        qDebug() << "Number of rows in the table: " << rowCount;
    } else {
        qDebug() << "Failed to execute the query or fetch the result.";
    }
    connClose();
}

