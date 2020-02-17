#include "login.h"
#include "ui_login.h"
#include <QLineEdit>
#include <string>
#include "optional.h"
#include <QDebug>
login::login(Storage *storage,QWidget *parent) :
    storage_(storage),
    QDialog(parent),

    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QLineEdit * username = ui->lineEdit_2;
    QLineEdit * password = ui->lineEdit;
    QString q = username->text();
    QString q1 = password->text();
    string s = q.toStdString();
    string s1 = q1.toStdString();
    optional<User> u = storage_->getUserAuth(s,s1);
    if(u == nullopt)
    {
        ui->label->setText("wrong password or username");
        password->clear();
    }
    else
    {
        user_ = new User;
        *user_ = *u;
        this->close();
    }

}
User * login::getUser(){
return user_;
}
