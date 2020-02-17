#include "add_editdialog.h"
#include "ui_add_editdialog.h"
#include "station.h"

Add_editDialog::Add_editDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_editDialog)
{
    ui->setupUi(this);
}

Add_editDialog::~Add_editDialog()
{
    delete ui;
}
Station Add_editDialog::data()
{
Station st;
st.name = ui->lineEdit->text().toStdString();
st.city = ui->lineEdit_2->text().toStdString();
st.country = ui->lineEdit_3->text().toStdString();
st.branch = ui->lineEdit_4->text().toStdString();
st.depth = ui->doubleSpinBox->value();
st.time = ui->doubleSpinBox_2->value();
return st;
}
