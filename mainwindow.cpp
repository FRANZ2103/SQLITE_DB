#include <QSqlQueryModel>
#include <QSqlQuery>
#include "mainwindow.h"
#include "ui_mainwindow.h"

int MainWindow::getCurrentPassengerValue(int &passengerNumber)
{
    // passengerNumber = 999;
    // connOpen();
    connOpen();
    QSqlQuery qry;
    //Get number first then insert
    QString query = "SELECT passenger_count FROM active_slot_sucat2ayala";

    qry.prepare(query);
    qry.exec();

    if(qry.next()){
        QVariant NumberVariant = qry.value(0);

        passengerNumber = NumberVariant.toInt();
             qDebug()<<"Passenger Number is "<< passengerNumber;
        // ui->currentNumber_label->setText(QString::number(passengerNumber));
        }
    else{
        qDebug()<<"Something wrong with increment";
    }

    connClose();
    return passengerNumber;
}

int MainWindow::getValueFromDB(int &valueToUpdate)
{
    valueToUpdate = 999;
    return valueToUpdate;
}

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
    on_load_btn_clicked();
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



    // connClose();
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

    qDebug()<<(model->rowCount())<<" alternative row count";
}


void MainWindow::on_test_btn_clicked()
{
    connOpen();

    QSqlQuery qry;
    qry.prepare("SELECT * FROM bookings WHERE passengerid = :search_value");

    // Replace 'your_table_name' with the actual name of your table
    // Replace 'column_name' with the actual column name you want to search
    // ':search_value' is a placeholder for the value you are searching for

    int searchValue = 42;  // Example value to search for
    qry.bindValue(":search_value", searchValue);

    if (qry.exec()) {
        if (qry.next()) {
            // Value found, you can retrieve the values of other columns if needed

            QString passnum= ui->lineEdit->text() + "1";
            QString refnum = ui->lineEdit_2->text();


            QString temp = "INSERT into bookings (passengerid,ReferenceNum) values ('"+passnum+"','"+refnum+"')";
            qry.prepare(temp);
            qry.exec();

            int intValue = qry.value(0).toInt(); // Assuming the first column is an integer
            QString stringValue = qry.value(1).toString(); // Assuming the second column is a string

            qDebug() << "Value found - Int Value:" << intValue << ", String Value:" << stringValue;
        } else {
            qDebug() << "Value not found in the table.";
        }
    } else {
        qDebug() << "Query failed:" << qry.lastError().text();
    }


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
    // connClose();
}


void MainWindow::on_select_from_Limit_to_variables_clicked()
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

}


void MainWindow::on_getValAtLimitNum_clicked()
{
    connOpen();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM bookings LIMIT 2");
    qry.exec();
    for(int i = 0; i< 2; i++){
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
    }
}



void MainWindow::on_incrementThenInsert_clicked()
{
    //Get number first then insert

    // QString query = "SELECT passenger_count FROM active_slot_sucat2ayala";
  int newwr;
  int passengerNumber = getCurrentPassengerValue(newwr);
  qDebug()<<" returned "<<passengerNumber;/*

    qry.prepare(query);
    qry.exec();

    if(qry.next()){
        QVariant NumberVariant = qry.value(0);

        passengerNumber = NumberVariant.toInt();
        // qDebug()<<"Passenger Number is "<< passengerNumber;
        ui->currentNumber_label->setText(QString::number(passengerNumber));
        }
    else{
        qDebug()<<"Something wrong with increment";
    }*/


    //We now update
  int newPassengerCount = passengerNumber +1;
  connOpen();
  QSqlQuery qry;
    qry.prepare("UPDATE active_slot_sucat2ayala SET passenger_count = :new_passenger_count WHERE current_plate = :plate_value");
    QString plateValueToUpdate = "XYZ-123";  // Example current_plate value to update
    qry.bindValue(":new_passenger_count", newPassengerCount);
    qry.bindValue(":plate_value", plateValueToUpdate);

    if(qry.exec()){

        qDebug()<<"Passenger Number is updated "<< newPassengerCount;
        // ui->currentNumber_label->setText();
    }
    else{
        qDebug()<<"Something wrong with increment";
    }

}

void MainWindow::on_decrementThenInsert_clicked()
{
    int tempValue;
    int passengerNumber =  getCurrentPassengerValue(tempValue);
    int testt =  getCurrentPassengerValue(tempValue);
    qDebug()<<"Try "<<testt;
}

