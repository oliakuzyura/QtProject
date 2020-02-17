#include "registration.h"
#include "ui_registration.h"
#include <QLineEdit>
#include <QSqlQuery>
#include <QDebug>
#include <QCryptographicHash>
registration::registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registration)
{
    ui->setupUi(this);
}

registration::~registration()
{
    delete ui;
}
static QString hashPassword(QString const & pass) {
   QByteArray pass_ba = pass.toUtf8();
   QByteArray hash_ba = QCryptographicHash::hash(pass_ba, QCryptographicHash::Md5);
   QString pass_hash = QString(hash_ba.toHex());
   return pass_hash;
}
User * registration::getUser()
{
return user;
}
void registration::on_pushButton_clicked()
{
    QLineEdit * username = ui->lineEdit;
    QLineEdit * password = ui->lineEdit_2;
    QLineEdit * c_password = ui->lineEdit_3;
    QString usname =  username->text();
    QString psword =  password->text();
    QString cpsword =  c_password->text();
    if(usname.size() < 4)
    {
        ui->label_4->setText("Error: minimum 4 symbols in username");
        return;
    }
    else if(psword.size() < 4)
    {
        ui->label_4->setText("Error: minimum 4 symbols in password");
         return;
    }
    else if(psword != cpsword)
    {
         ui->label_4->setText("Error: passwords don't match");
          return;
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username=:username");
    query.bindValue(":username", usname);
    if(!query.exec())
    {
        qDebug() << "Error";
        return;
    }
    if(query.next())
    {
        ui->label_4->setText("User with this username already exists");
         return;
    }
    else
    {
    query.prepare("INSERT INTO users (username, password_hash) VALUES (:username, :password)");
    query.bindValue(":username",usname);
    query.bindValue(":password", hashPassword(psword));
    if(!query.exec())
    {
        qDebug() << "Error";
        return;
    }
    user = new User;
    user->username = usname.toStdString();
    user->password_hash = psword.toStdString();
    user->id = query.lastInsertId().toInt();
    this->close();
    }
}
