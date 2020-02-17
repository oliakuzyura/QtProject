#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include "xmlstorage.h"
#include "sqlite_storage.h"
#include <QListWidget>
#include "add_editdialog.h"
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QMessageBox>
#include "login.h"
#include "edit_dialog.h"
#include "registration.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SqliteStorage * st = new SqliteStorage("../myproject/data/sql");
    storage_ = st;
    storage_->open();
    login log_diaog(storage_,this) ;
    log_diaog.exec();
    user_ = log_diaog.getUser();
    ui->label_19->setText(QString::fromStdString(user_->username));
    QListWidget * l = ui->listWidget;
    vector<Station> stations;
    stations = storage_->getAllUserStations(user_->id);
    for(Station stat: stations)
    {

        QVariant qVariant;
        qVariant.setValue(stat);

        QListWidgetItem *qStationListItem = new QListWidgetItem();
        qStationListItem->setText(QString::fromStdString(stat.name));
        qStationListItem->setData(Qt::UserRole, qVariant);

        l->addItem(qStationListItem);
    }
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete storage_;
    delete ui;

}
bool MainWindow::TestStation(Station st)
{
if(ui->label_9->text() == QString::fromStdString(st.name))
{
return true;
}
return false;
}
//void MainWindow::on_actionOpen_storage_triggered()
//{
//    ui->pushButton->setEnabled(true);
//    ui->listWidget->clear();
//    if(storage_ != nullptr)
//    {
//        delete storage_;
//    }

//    QString fileName = QFileDialog::getOpenFileName(
//                   this,              // parent
//                   "Dialog Caption",  // caption
//                   "",                // directory to start with
//                   "XML (*.xml);;All Files (*)");  // file name filter
//       qDebug() << fileName;
//    XmlStorage * st = new XmlStorage(fileName);
//    storage_ = st;
//    QListWidget * ql = ui->listWidget;
//    vector<Station> stations;
//    storage_->load();
//    stations = storage_->getAllStations();
//    for(Station stat: stations)
//    {

//        QVariant qVariant;
//        qVariant.setValue(stat);

//        QListWidgetItem *qStationListItem = new QListWidgetItem();
//        qStationListItem->setText(QString::fromStdString(stat.name));
//        qStationListItem->setData(Qt::UserRole, qVariant);

//        ui->listWidget->addItem(qStationListItem);
//    }
//is_Clicked();
//}

//void MainWindow::on_actionNew_storage_triggered()
//{
//    ui->pushButton->setEnabled(true);
//    if(storage_ != nullptr)
//    {
//        delete storage_;
//    }
//    QString fileName = QFileDialog::getSaveFileName(
//                   this,              // parent
//                   "Dialog Caption",  // caption
//                   "",                // directory to start with
//                   "XML (*.xml);;All Files (*)");  // file name filter
//       qDebug() << fileName;
//    XmlStorage * st = new XmlStorage(fileName);
//    storage_ = st;
//is_Clicked();
//}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    QVariant q = item->data(Qt::UserRole);
    Station st = q.value<Station>();

    ui->label_9->setText(QString::fromStdString(st.name));
    int a = TestStation(st);
    if(a)
    {

    }
    else
    {
        qDebug() << "TEST broke down";
    }
    ui->label_10->setText(QString::fromStdString(st.city));
    ui->label_11->setText(QString::fromStdString(st.country));
    ui->label_12->setText(QString::fromStdString(st.branch));
    ui->label_13->setText(QString::number(st.depth));
    ui->label_14->setText(QString::number(st.time));
    ui->label_15->setText(QString::number(st.id));
    vector<Branch> br = storage_->getAllStationBranches(st.id);
    ui->label_17->setText(QString::number(br.size()));

}

void MainWindow::on_pushButton_clicked()
{
    Add_editDialog d(this);
    d.setWindowTitle("Add");
    if(d.exec())
    {
        QListWidget * list = ui->listWidget;
        Station st = d.data();
        st.id = storage_->insertStation(st);
        QVariant qVariant;
        qVariant.setValue(st);

        QListWidgetItem *qStationListItem = new QListWidgetItem();
        qStationListItem->setText(QString::fromStdString(st.name));
        qStationListItem->setData(Qt::UserRole, qVariant);
        list->addItem(qStationListItem);
        //storage_->insertStation(st);
        QSqlQuery query;
        query.prepare("UPDATE stations SET user_id = :user_id WHERE id = :id");
        query.bindValue(":user_id",user_->id);
        query.bindValue(":id",st.id);
        if(!query.exec())
        {
            qDebug() << "addPerson error:"
                     << query.lastError();
        }
    }
    is_Clicked();
}

void MainWindow::on_pushButton_2_clicked()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();

    QListWidgetItem * selectedItem = list.at(0);
    QVariant vr = selectedItem->data(Qt::UserRole);

    Station st = vr.value<Station>();
    int a = st.id;
    int b = st.branches;
    edit_dialog editdialog(storage_,&st,this);
    QLineEdit * ln = editdialog.findChild<QLineEdit *>("lineEdit");
    QLineEdit * ln1 = editdialog.findChild<QLineEdit *>("lineEdit_2");
    QLineEdit * ln2 = editdialog.findChild<QLineEdit *>("lineEdit_3");
    QLineEdit * ln3 = editdialog.findChild<QLineEdit *>("lineEdit_4");
    QDoubleSpinBox * ln4 = editdialog.findChild< QDoubleSpinBox *>("doubleSpinBox");
    QDoubleSpinBox * ln5 = editdialog.findChild< QDoubleSpinBox *>("doubleSpinBox_2");
    ln->setText(QString::fromStdString(st.name));
    ln1->setText(QString::fromStdString(st.city));
    ln2->setText(QString::fromStdString(st.country));
    ln3->setText(QString::fromStdString(st.branch));
    ln4->setValue(st.depth);
    ln5->setValue(st.time);

    if(editdialog.exec())
    {
        st = editdialog.data();
        st.id = a;
        st.branches = b;
        storage_->updateStation(st);
        ui->listWidget->clear();
        vector<Station> stations;
        stations = storage_->getAllUserStations(user_->id);

        for(Station stat: stations)
        {
            QVariant qVariant;
            qVariant.setValue(stat);

            QListWidgetItem *qStationListItem = new QListWidgetItem();
            qStationListItem->setText(QString::fromStdString(stat.name));
            qStationListItem->setData(Qt::UserRole, qVariant);

            ui->listWidget->addItem(qStationListItem);
        }


    }
    is_Clicked();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(QMessageBox::question(this, "Remove","Are you sure?") == QMessageBox::No)
    {
        return;
    }

    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if (list.count() > 0) // selected
    {
        QListWidgetItem * selectedItem = list.at(0);
        QVariant vr = selectedItem->data(Qt::UserRole);
        Station st = vr.value<Station>();
        storage_->removeStation(st.id);
        // remove item from list
        int itemRow = ui->listWidget->row(selectedItem);
        ui->listWidget->takeItem(itemRow);
        delete selectedItem;

        // as it is on heap, but now detached from parent
    }
    else  // not selected
    {
        qDebug() << "No items selected";
    }
    is_Clicked();

}
bool MainWindow::TestIsClicked(Station st)
{
if(ui->label_9->text() == QString::fromStdString(st.name) && ui->label_10->text() == QString::fromStdString(st.city) && ui->label_11->text() == QString::fromStdString(st.country) && ui->label_12->text() == QString::fromStdString(st.branch))
{
return true;
}
return false;
}
void MainWindow::is_Clicked()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    if(list.count() > 0)
    {
        QListWidgetItem * selectedItem = list.at(0);
        QVariant vr = selectedItem->data(Qt::UserRole);
        Station st = vr.value<Station>();
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->label_9->setText(QString::fromStdString(st.name));
        ui->label_10->setText(QString::fromStdString(st.city));
        ui->label_11->setText(QString::fromStdString(st.country));
        ui->label_12->setText(QString::fromStdString(st.branch));
        ui->label_13->setText(QString::number(st.depth));
        ui->label_14->setText(QString::number(st.time));
        ui->label_15->setText(QString::number(st.id));
        int a = TestIsClicked(st);
        if(a){}
        else
        {
            qDebug() << "Test broke down";
        }



    }
    else
    {
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->label_9->clear();
        ui->label_10->clear();
        ui->label_11->clear();
        ui->label_12->clear();
        ui->label_13->clear();
        ui->label_14->clear();
        ui->label_15->clear();
        ui->label_17->clear();
    }
}

void MainWindow::on_actionLogin_triggered()
{
    login log(storage_,this);
    log.exec();
    QLineEdit * username = log.findChild<QLineEdit *>("lineEdit_2");
    QLineEdit * password = log.findChild<QLineEdit *>("lineEdit");
    QString q = username->text();
    QString q1 = password->text();
    string s = q.toStdString();
    string s1 = q1.toStdString();
    optional<User> u = storage_->getUserAuth(s,s1);
    if(u == nullopt)
    {

        password->clear();
    }
    else
    {
        QLineEdit * username = log.findChild<QLineEdit *>("lineEdit_2");
        QLineEdit * password = log.findChild<QLineEdit *>("lineEdit");
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
            delete user_;
            user_ = new User;
            *user_ = *u;
            log.close();
            ui->label_19->setText(QString::fromStdString(user_->username));
            ui->listWidget->clear();
            vector<Station> stations;
            stations = storage_->getAllUserStations(user_->id);
            for(Station stat: stations)
            {

                QVariant qVariant;
                qVariant.setValue(stat);

                QListWidgetItem *qStationListItem = new QListWidgetItem();
                qStationListItem->setText(QString::fromStdString(stat.name));
                qStationListItem->setData(Qt::UserRole, qVariant);

                ui->listWidget->addItem(qStationListItem);
            }
            is_Clicked();


        }

    }


}

void MainWindow::on_actionSign_up_triggered()
{
    registration r(this);
    r.exec();
    delete user_;
    user_ = r.getUser();
     ui->label_19->setText(QString::fromStdString(user_->username));
    ui->listWidget->clear();

}


void MainWindow::on_actionimport_triggered()
{
    ui->pushButton->setEnabled(true);
    ui->listWidget->clear();

    QString fileName = QFileDialog::getOpenFileName(
                this,              // parent
                "Dialog Caption",  // caption
                "",                // directory to start with
                "XML (*.xml);;All Files (*)");  // file name filter
    qDebug() << fileName;
    Storage * storage;
    if(!fileName.endsWith(".xml"))
    {
        QMessageBox::warning(this,"Error","File is not xml",QMessageBox::Apply);
    }
    else
    {
        XmlStorage * st = new XmlStorage(fileName);
        storage = st;

    }
    vector<Station> allst = storage_->getAllUserStations(user_->id);
    for(Station stat: allst)
    {
        storage_->removeStation(stat.id);
    }
    ui->listWidget->clear();
    QListWidget * ql = ui->listWidget;
    vector<Station> stations;
    storage->open();
    stations = storage->getAllStations();
    for(Station stat: stations)
    {
        stat.id = storage_->insertStation(stat);
        storage_->links(stat.id,user_->id);
        QVariant qVariant;
        qVariant.setValue(stat);

        QListWidgetItem *qStationListItem = new QListWidgetItem();
        qStationListItem->setText(QString::fromStdString(stat.name));
        qStationListItem->setData(Qt::UserRole, qVariant);

        ui->listWidget->addItem(qStationListItem);
    }
    delete storage;

    is_Clicked();
}

void MainWindow::on_actionexport_triggered()
{
    Storage * st1;
    ui->pushButton->setEnabled(true);
    QString fileName = QFileDialog::getSaveFileName(
                this,              // parent
                "Dialog Caption",  // caption
                "",                // directory to start with
                "XML (*.xml);;All Files (*)");  // file name filter
    qDebug() << fileName;
    if(!fileName.endsWith(".xml"))
    {
        QMessageBox::warning(this,"Error","File is not xml",QMessageBox::Apply);
    }
    else
    {
      XmlStorage * st = new XmlStorage(fileName);
      st1 = st;
    }
    vector<Station> stations = storage_->getAllUserStations(user_->id);
    for(Station stat:stations)
    {
        st1->insertStation(stat);
    }
    st1->close();
    is_Clicked();
}
