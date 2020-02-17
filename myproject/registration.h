#ifndef REGISTRATION_H
#define REGISTRATION_H
#include "user.h"
#include <QDialog>

namespace Ui {
class registration;
}

class registration : public QDialog
{
    Q_OBJECT

public:
    explicit registration(QWidget *parent = 0);
    ~registration();
    User * getUser();

private slots:
    void on_pushButton_clicked();

private:
    Ui::registration *ui;
    User * user;

};

#endif // REGISTRATION_H
