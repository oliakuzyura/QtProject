#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "storage.h"
#include <QMainWindow>
#include <QListWidgetItem>
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
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();



    void on_actionLogin_triggered();

    void on_actionSign_up_triggered();


    void on_actionimport_triggered();

    void on_actionexport_triggered();

private:
    User * user_;
    Ui::MainWindow *ui;
    Storage * storage_;
    void is_Clicked();
    bool TestStation(Station st);
    bool TestIsClicked(Station st);
};

#endif // MAINWINDOW_H
