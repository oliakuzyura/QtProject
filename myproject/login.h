#ifndef LOGIN_H
#define LOGIN_H
#include "storage.h"
#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    User * getUser();
    explicit login(Storage * storage,QWidget *parent = 0);
    ~login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::login *ui;
    Storage * storage_;
    User * user_;
};

#endif // LOGIN_H
