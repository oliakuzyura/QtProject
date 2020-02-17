#include "sqlite_storage.h"
#include <QtSql>
#include <QCryptographicHash>
#include<QDebug>
#include <QString>
SqliteStorage::SqliteStorage(const string & dir_name) : dir_name_(dir_name)
{
  db_ = QSqlDatabase::addDatabase("QSQLITE");
}
bool SqliteStorage::open() {
    QString path = QString::fromStdString(this->dir_name_) + "/data.sqlite";
    db_.setDatabaseName(path);
    bool connected = db_.open();
    if (!connected) { return false;  }
    return true;
}


bool SqliteStorage::close() {
    db_.close();
    return true;
}
Station getStationFromQuery(const QSqlQuery & query)
{
    string name = query.value("Metrostation").toString().toStdString();
    string color = query.value("Colorofstation").toString().toStdString();
    string city = query.value("City").toString().toStdString();
    string country = query.value("Country").toString().toStdString();
    float depth = query.value("Depth").toFloat();
    float time = query.value("Time").toFloat();
    int id = query.value("id").toInt();
    int branches = query.value("branches").toInt();
    Station s;
    s.name = name;
    s.branch = color;
    s.city = city;
    s.country = country;
    s.depth = depth;
    s.time = time;
    s.id = id;
    s.branches = branches;
    return s;
}
Branch getBranchFromQuery(const QSqlQuery & query)
{
    string color = query.value("color").toString().toStdString();
    float depth = query.value("depth").toFloat();
    float amount = query.value("amount").toFloat();
    int id = query.value("id").toInt();
    Branch s;
    s.color = color;
    s.depth = depth;
    s.amount = amount;
    s.id = id;
    return s;
}
vector<Station> SqliteStorage::getAllStations(void) {

    vector<Station> stations;
    QSqlQuery query("SELECT * FROM stations");
    while (query.next())
    {
       Station s = getStationFromQuery(query);
       stations.push_back(s);
    }

    return stations;
}

optional<Station> SqliteStorage::getStationById(int station_id) {

    QSqlQuery query;
    query.prepare("SELECT * FROM stations WHERE id = :id");
    query.bindValue(":id", station_id);
    if (!query.exec()) {  // do exec if query is prepared SELECT query
       qDebug() << "get station error:" << query.lastError();
        return nullopt;
    }
    if (query.next()) {
       Station s = getStationFromQuery(query);
        return s;
    } else {
       return nullopt;
    }

}

bool SqliteStorage::updateStation(const Station &station) {

    QSqlQuery query;
    query.prepare("UPDATE stations SET Metrostation = :Metrostation, Colorofstation = :Colorofstation, City = :City, Country = :Country, Depth = :Depth, Time = :Time, Branches = :Branches WHERE id = :id");
    query.bindValue(":Metrostation", QString::fromStdString(station.name));
    query.bindValue(":Colorofstation",  QString::fromStdString(station.branch));
    query.bindValue(":City",  QString::fromStdString(station.city));
    query.bindValue(":Country",  QString::fromStdString(station.country));
    query.bindValue(":Depth", station.depth);
    query.bindValue(":Time", station.time);
    query.bindValue(":id", station.id);
    query.bindValue(":Branches",station.branches);
    if (!query.exec()){
        qDebug() << "updatePerson error:" << query.lastError();
        return false;
    }
  return true;
}

bool SqliteStorage::removeStation(int station_id){

    QSqlQuery query;
    query.prepare("DELETE FROM stations WHERE id = :id");
    query.bindValue(":id", station_id);
    if (!query.exec()){

        qDebug() << "deletePerson error:" << query.lastError();
        return false;
    }
 return true;
}

int SqliteStorage::insertStation(const Station &station) {


    QSqlQuery query;
    query.prepare("INSERT INTO stations (Metrostation, Colorofstation, City, Country, Depth, Time, Branches) VALUES (:Metrostation, :Colorofstation, :City, :Country, :Depth, :Time, :Branches)");
    query.bindValue(":Metrostation", QString::fromStdString(station.name));
    query.bindValue(":Colorofstation",  QString::fromStdString(station.branch));
    query.bindValue(":City",  QString::fromStdString(station.city));
    query.bindValue(":Country",  QString::fromStdString(station.country));
    query.bindValue(":Depth", station.depth);
    query.bindValue(":Time", station.time);
    query.bindValue(":Branches",station.branches);
    if (!query.exec()){
        qDebug() << "addPerson error:"
                 << query.lastError();
        return 0;
    }
    QVariant var = query.lastInsertId();

  return var.toInt();

}

// branches

vector<Branch> SqliteStorage::getAllBranches(void) {
    vector<Branch> branches;
    QSqlQuery query("SELECT * FROM branches");
    while (query.next())
    {
       Branch s = getBranchFromQuery(query);
       branches.push_back(s);
    }

    return branches;
}

optional<Branch> SqliteStorage::getBranchById(int branch_id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM branches WHERE id = :id");
    query.bindValue(":id", branch_id);
    if (!query.exec()) {  // do exec if query is prepared SELECT query
       qDebug() << "get branch error:" << query.lastError();
        return nullopt;
    }
    if (query.next()) {
       Branch s = getBranchFromQuery(query);
        return s;
    } else {
       return nullopt;
    }
}

bool SqliteStorage::updateBranch(const Branch &branch) {
    QSqlQuery query;
    query.prepare("UPDATE stations SET  color = :color, depth = :depth, amount = :amount WHERE id = :id");
    query.bindValue(":color", QString::fromStdString(branch.color));
    query.bindValue(":depth", branch.depth);
    query.bindValue(":amount", branch.amount);
    query.bindValue(":id", branch.id);
    if (!query.exec()){
        qDebug() << "updateBranch error:" << query.lastError();
        return false;
    }
  return true;
}

bool SqliteStorage::removeBranch(int branch_id) {
    QSqlQuery query;
    query.prepare("DELETE FROM branches WHERE id = :id");
    query.bindValue(":id", branch_id);
    if (!query.exec()){

        qDebug() << "deleteBranch error:" << query.lastError();
        return false;
    }
 return true;
}

int SqliteStorage::insertBranch(const Branch &branch) {

    QSqlQuery query;
    query.prepare("INSERT INTO branches (color, depth, amount) VALUES (:color, :depth, :amount)");
    query.bindValue(":color", QString::fromStdString(branch.color));
    query.bindValue(":depth", branch.depth);
    query.bindValue(":amount", branch.amount);
    if (!query.exec()){
        qDebug() << "addBranch error:"
                 << query.lastError();
        return 0;
    }
    QVariant var = query.lastInsertId();

  return var.toInt();
}
vector<Station> SqliteStorage::getAllUserStations(int user_id)
{
 vector<Station> st;
 QSqlQuery query;
 query.prepare("SELECT * FROM stations WHERE user_id = :user_id");
 query.bindValue(":user_id", user_id);
 if(!query.exec())
 {
     qDebug() << "addBranch error:"
              << query.lastError();
     return st;
 }
 while(query.next())
 {
     Station s;
     s.name = query.value("Metrostation").toString().toStdString();
     s.branch = query.value("Colorofstation").toString().toStdString();
     s.city = query.value("City").toString().toStdString();
     s.country = query.value("Country").toString().toStdString();
     s.depth = query.value("Depth").toFloat();
     s.time = query.value("Time").toFloat();
     s.id =  query.value("id").toInt();
     s.branches = query.value("branches").toInt();
     st.push_back(s);

 }
return st;
}
static QString hashPassword(QString const & pass) {
   QByteArray pass_ba = pass.toUtf8();
   QByteArray hash_ba = QCryptographicHash::hash(pass_ba, QCryptographicHash::Md5);
   QString pass_hash = QString(hash_ba.toHex());
   return pass_hash;
}
optional<User> SqliteStorage::getUserAuth(string & username, string & password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password_hash = :password_hash");
    query.bindValue(":username", QString::fromStdString(username));
    query.bindValue(":password_hash", hashPassword(QString::fromStdString(password)));
    if(!query.exec())
    {
        qDebug() << "addBranch error:"
                 << query.lastError();
        return nullopt;
    }
    if(query.next())
    {
        User u;
        u.username = query.value("username").toString().toStdString();
        u.password_hash = query.value("password_hash").toString().toStdString();
     //   qDebug() <<QString::fromStdString(u.password_hash);
        u.id = query.value("id").toInt();
        return u;
    }
    return nullopt;
}
  // links
vector<Branch> SqliteStorage::getAllStationBranches(int station_id)
{
    vector<Branch> b;
    QSqlQuery query;
    query.prepare("SELECT branch_id FROM links WHERE station_id = :station_id");
    query.bindValue(":station_id",station_id);
    if(!query.exec())
    {
        qDebug() << "addBranch error:"
                 << query.lastError();
        return b;
    }
    while(query.next())
    {
        Branch b1;
        QSqlQuery query1;
        query1.prepare("SELECT * FROM branches WHERE id = :id1");
        query1.bindValue(":id1",query.value("branch_id").toInt());
        if(!query1.exec())
        {
            qDebug() << "addBranch error:"
                     << query.lastError();
            return b;
        }
        if(query1.next())
        {
        b1.color = query1.value("color").toString().toStdString();
        b1.amount = query1.value("amount").toInt();
        b1.depth =  query1.value("depth").toFloat();
        b1.id = query1.value("id").toInt();
        b.push_back(b1);
        }
    }
    return b;
}

bool SqliteStorage::insertStationBranch(int station_id, int branch_id)
{
    QSqlQuery query;
    query.prepare("INSERT INTO links (station_id, branch_id) VALUES (:station_id, :branch_id)");
    query.bindValue(":station_id", station_id);
    query.bindValue(":branch_id", branch_id);
    if(!query.exec())
    {
        qDebug() << "addBranch error:"
                 << query.lastError();
        return false;
    }
    return true;
}
bool SqliteStorage::removeStationBranch(int station_id, int branch_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM links WHERE station_id = :station_id AND branch_id = :branch_id");
    query.bindValue(":station_id", station_id);
    query.bindValue(":branch_id", branch_id);
    if(!query.exec())
    {
        qDebug() << "addBranch error:"
                 << query.lastError();
        return false;
    }
    return true;
}
void SqliteStorage::links(int stat_id, int user_id)
{
   QSqlQuery query;
   query.prepare("UPDATE stations SET user_id = :user_id WHERE id = :id");
   query.bindValue(":user_id",user_id);
   query.bindValue(":id",stat_id);
   if(!query.exec())
   {
       qDebug() << "addBranch error:"
                << query.lastError();
       return;
   }
}
