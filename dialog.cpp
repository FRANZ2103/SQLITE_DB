#include "mainwindow.h"
#include <QTimer>
#include "dialog.h"
#include "ui_dialog.h"
void Dialog::rowcount()
{

    QSqlQuery qry;
    qry.prepare("SELECT COUNT(*) FROM bookings"); // Counts Rows in SQLITE
    qry.exec();

    if (qry.next()) {
        int rowCount = qry.value(0).toInt();
        //Assume that the max bookable slots is already set in the db
        if (rowCount)

        qDebug() << "Number of rows in the table: " << rowCount;
    } else {
        qDebug() << "Failed to execute the query or fetch the result.";
    }
}

void Dialog::getDeets()
{
    //Get the plate number from the active table

    QSqlQuery qry;
    qry.prepare("SELECT * FROM active_slot_sucat2ayala");
    qry.exec();
    if (qry.next()) {
        QVariant value1 = qry.value(0);  // Get the value of the first column
        QVariant value2 = qry.value(1); //set_bookable_cap
        QVariant value3 = qry.value(2); //passenger_count
        QVariant value4 = qry.value(3); //passenger_cap
        QVariant value5 = qry.value(4); //departing_time
        QVariant value6 = qry.value(5);// current_driver //not needed
        QVariant value7 = qry.value(6); //current_booking_count

        // You can then use these values as needed, for example:
        QString stringValue1 = value1.toString();  // Convert to QString if it's a string
        int bookingsRemaining = value2.toInt() - value7.toInt();
        int currentPassengers = value3.toInt();
        QString departureTime = value5.toString();
        qDebug()<<stringValue1<<"it worked";
        qDebug()<<"Bookings remaining: "<<bookingsRemaining;
        qDebug()<<"Current Passengers: "<<currentPassengers<<"/"<<value4.toInt();
        qDebug()<<"Departing at approx: "<<departureTime;


        ui->slotsAvailable->setText("Bookable slots: \n"+QString::number(bookingsRemaining));
        ui->plateNumDisplay->setText("Plate Number: \n"+ stringValue1);
        ui->departing_time_label->setText("Departing Time: \n"+ departureTime);
        ui->passenger_count_label->setText("Current Passengers: \n"+ value3.toString()+"/"+value4.toString());

    } else {

        qDebug() << "No rows returned from the query.";
    }


}

void printHi() {
    qDebug() << "Hi";
}
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QTimer * timer = new QTimer(this);
    connect (    timer, SIGNAL (timeout()), this, SLOT(showtime()));
    timer->start();
    connOpen();
    getDeets();
    //get bookable deeets
    //get current passenger count, plate, maxcap, bookable slots
    rowcount();


}

Dialog::~Dialog()
{
    delete ui;

}



void Dialog::on_testButton_clicked()
{
}

void Dialog::showtime()
{
QTime time = QTime::currentTime();
QString time_text = time.toString("hh : mm : ss");
ui -> label_clock->setText(time_text);
getDeets();

}

