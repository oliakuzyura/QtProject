#ifndef EDIT_DIALOG_H
#define EDIT_DIALOG_H
#include "station.h"
#include "branch.h"
#include <QDialog>
#include <storage.h>
#include <QListWidget>
namespace Ui {
class edit_dialog;
}

class edit_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit edit_dialog(Storage *stor,Station *st, QWidget *parent = 0);
    ~edit_dialog();
    Station data();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

private:
    Ui::edit_dialog *ui;
    Station * st_;
    Storage * stor_;
    void isClicked();
};

#endif // EDIT_DIALOG_H
