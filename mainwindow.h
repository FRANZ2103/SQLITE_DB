#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_delete_2_clicked();

    void on_pushButton_2_clicked();

    void on_load_btn_clicked();

    void on_putDBtoCombobox_clicked();

    void on_test_btn_clicked();

    void on_count_rows_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
