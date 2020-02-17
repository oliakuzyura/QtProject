#include "edit_dialog.h"
#include "ui_edit_dialog.h"
#include <storage.h>
#include <QListWidget>
#include <QDebug>
static bool isContained(vector<Branch> branches,Branch  branch)
{
for(Branch item: branches)
{
    if(item.id == branch.id)
    {
        return true;
    }
}
return false;
}
edit_dialog::edit_dialog(Storage *stor,Station *st, QWidget *parent) :
    stor_(stor),
    st_(st),
    QDialog(parent),
    ui(new Ui::edit_dialog)
{
    ui->setupUi(this);
    isClicked();
    QListWidget *add = ui->listWidget;
    QListWidget *other = ui->listWidget_2;
    vector<Branch> br = stor->getAllStationBranches(st->id);
    for(Branch stat: br)
       {

           QVariant qVariant;
           qVariant.setValue(stat);

           QListWidgetItem *qStationListItem = new QListWidgetItem();
           qStationListItem->setText(QString::fromStdString(stat.color));
           qStationListItem->setData(Qt::UserRole, qVariant);

           add->addItem(qStationListItem);
       }
     vector<Branch> all = stor->getAllBranches();
     for(Branch item: all )
     {
       if(!isContained(br,item))
       {
           QVariant qVariant;
           qVariant.setValue(item);
           QListWidgetItem *qStationListItem = new QListWidgetItem();
           qStationListItem->setText(QString::fromStdString(item.color));
           qStationListItem->setData(Qt::UserRole, qVariant);

           other->addItem(qStationListItem);
       }

     }

}

edit_dialog::~edit_dialog()
{
    delete ui;
}
Station edit_dialog::data()
{
    Station st;
    st.name = ui->lineEdit->text().toStdString();
    st.branch = ui->lineEdit_4->text().toStdString();
    st.city = ui->lineEdit_2->text().toStdString();
    st.country = ui->lineEdit_3->text().toStdString();
    st.depth = ui->doubleSpinBox->value();
    st.time = ui->doubleSpinBox_2->value();
    return st;
}

void edit_dialog::on_pushButton_clicked()
{

    QList<QListWidgetItem *> list = ui->listWidget_2->selectedItems();

    QListWidgetItem * selectedItem = list.at(0);
    QVariant vr = selectedItem->data(Qt::UserRole);

    Branch br = vr.value<Branch>();

    vr.setValue(br);
    QListWidgetItem *qStationListItem = new QListWidgetItem();
    qStationListItem->setText(QString::fromStdString(br.color));
    qStationListItem->setData(Qt::UserRole, vr);

    ui->listWidget->addItem(qStationListItem);
    stor_->insertStationBranch(st_->id,br.id);

   int itemRow = ui->listWidget_2->row(selectedItem);
   ui->listWidget_2->takeItem(itemRow);
   delete selectedItem;
   isClicked();
}

void edit_dialog::on_pushButton_2_clicked()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();

    QListWidgetItem * selectedItem = list.at(0);
    QVariant vr = selectedItem->data(Qt::UserRole);

    Branch br = vr.value<Branch>();
    vr.setValue(br);
    QListWidgetItem *qStationListItem = new QListWidgetItem();
    qStationListItem->setText(QString::fromStdString(br.color));
    qStationListItem->setData(Qt::UserRole, vr);

   ui->listWidget_2->addItem(qStationListItem);
   stor_->removeStationBranch(st_->id,br.id);
   int itemRow = ui->listWidget->row(selectedItem);
   ui->listWidget->takeItem(itemRow);
   delete selectedItem;
   isClicked();
}
void edit_dialog::isClicked()
{
if(ui->listWidget->selectedItems().size() > 0)
{
    ui->pushButton_2->setEnabled(true);
}
else
{
    ui->pushButton_2->setEnabled(false);
}
if(ui->listWidget_2->selectedItems().size() > 0)
{
    ui->pushButton->setEnabled(true);
}
else
{
    ui->pushButton->setEnabled(false);
}
}

void edit_dialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    isClicked();
}

void edit_dialog::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    isClicked();
}
