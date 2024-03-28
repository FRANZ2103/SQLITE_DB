#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    void rowcount();
    void getDeets();

    QSqlDatabase mydb;
    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen(){

        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/Users/Franz Sundiam/Documents/1 QT Projects/SQLiteTestDB/mySQLdatabase.db");

        if(!mydb.open()){

            qDebug()<< "Not connected!";
            return false;
        }
        else{
            qDebug()<< "Connected....!";
            return true;
        }
    }

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
