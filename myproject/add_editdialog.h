#ifndef ADD_EDITDIALOG_H
#define ADD_EDITDIALOG_H
#include "station.h"
#include <QDialog>

namespace Ui {
class Add_editDialog;
}

class Add_editDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_editDialog(QWidget *parent = 0);
    Station data();
    ~Add_editDialog();

private:
    Ui::Add_editDialog *ui;
};

#endif // ADD_EDITDIALOG_H
