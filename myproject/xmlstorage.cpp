#include "xmlstorage.h"
#include <iostream>
#include <QtXml>
#include <QFile>
#include <QTextStream>
using namespace std;
int XmlStorage::getNewStationId()
{
    int max = 0;
    for (Station &st : stations_)
    {
        if (st.id > max)
        {
            max = st.id;
        }
    }
    max = max + 1;
    return max;
}
int XmlStorage::getNewBranchId()
{
    int max = 0;
    for (Branch &br : branchs_)
    {
        if (br.id > max)
        {
            max = br.id;
        }
    }
    max = max + 1;
    return max;
}
Station domElementToStation(QDomElement & element)
{
    Station c;
    c.name = element.attribute("Metro_station").toStdString();
    c.branch = element.attribute("Color_of_station").toStdString();
    c.city = element.attribute("City").toStdString();
    c.country = element.attribute("Country").toStdString();
    c.time = element.attribute("Time").toFloat();
    c.depth = element.attribute("Depth").toFloat();
    c.id = element.attribute("id").toInt();
    return c;
}
Branch domElementToBranch(QDomElement & element)
{
    Branch c;
    c.color = element.attribute("color").toStdString();
    c.depth = element.attribute("depth").toFloat();
    c.amount = element.attribute("amount").toFloat();
    c.id = element.attribute("id").toInt();
    return c;
}
bool XmlStorage::open()
{
    QString str =  dir_name_;
    QFile file(str);
    if (!file.open(QFile::ReadOnly))
    {

        return false;
    }
    QTextStream ts(&file);

    QString xml_text = ts.readAll();
    qDebug() << xml_text;
    file.close();

    QDomDocument doc;

    QString errMeg;
    int errLine;
    int errCol;
    if (!doc.setContent(xml_text, &errMeg, &errLine, &errCol))
    {

        return false;
    }
    QDomElement root_el = doc.documentElement();
    QDomNodeList children = root_el.childNodes();
    for(int i = 0; i < children.size(); i++)
    {
      QDomNode node = children.at(i);
      QDomElement element = node.toElement();
      Station c = domElementToStation(element);
      stations_.push_back(c);
    }
//      string str1 =  dir_name_ + "/branch.xml";
//      QString q1 = QString::fromStdString(str1);
//      QFile file1(q1);
//      if (!file1.open(QFile::ReadOnly))
//      {

//          return false;
//      }
//      QTextStream ts1(&file1);

//      QString xml_text1 = ts1.readAll();
//      qDebug() << xml_text1;
//      file1.close();

//      QDomDocument doc1;

//      QString errMeg1;
//      int errLine1;
//      int errCol1;
//      if (!doc1.setContent(xml_text1, &errMeg1, &errLine1, &errCol1))
//      {

//          return false;
//      }
//      QDomElement root_el1 = doc1.documentElement();
//      QDomNodeList children1 = root_el1.childNodes();
//      for(int i = 0; i < children1.size(); i++)
//      {
//        QDomNode node1 = children1.at(i);
//        QDomElement element1 = node1.toElement();
//        Branch c1 = domElementToBranch(element1);
//        branchs_.push_back(c1);

//       }
    return true;
}
QDomElement stationToDomElement(QDomDocument & doc, Station & c)
{
    QDomElement station_el = doc.createElement("stations");
     station_el.setAttribute("Metro_station", c.name.c_str());
     station_el.setAttribute("Color_of_station", c.branch.c_str());
     station_el.setAttribute("City", c.city.c_str());
     station_el.setAttribute("Country", c.country.c_str());
     station_el.setAttribute("Depth",c.depth);
     station_el.setAttribute("Time", c.time);
     station_el.setAttribute("id",c.id);
     return station_el;
}
QDomElement branchToDomElement(QDomDocument & doc, Branch & c)
{
    QDomElement branch_el = doc.createElement("branches");
    branch_el.setAttribute("color", c.color.c_str());
    branch_el.setAttribute("depth", c.depth);
    branch_el.setAttribute("amount", c.amount);
    branch_el.setAttribute("id", c.id);

     return branch_el;
}
bool XmlStorage::close()
{
    QDomDocument doc;

   QDomElement root =  doc.createElement("stations");

   for(Station & c : this->stations_)
   {
       QDomElement station_el = stationToDomElement(doc,c);
        root.appendChild(station_el);
   }
   doc.appendChild(root);
   QString xml_text = doc.toString(4);

   QString str =  dir_name_;

   QFile file(str);
   bool isOpened = file.open(QFile::WriteOnly);
   if (!isOpened)
   {

       return false;
   }
   QTextStream ts(&file);
   ts << xml_text;

   file.close();

//   QDomDocument doc1;

//  QDomElement root1 =  doc1.createElement("branches");

//  for(Branch & c1 : this->branchs_)
//  {
//      QDomElement branch_el = branchToDomElement(doc1,c1);
//       root1.appendChild(branch_el);
//  }
//  doc1.appendChild(root1);
//  QString xml_text1 = doc1.toString(4);

//  string str1 =  dir_name_ + "/branch.xml";
//  QString q1 = QString::fromStdString(str1);
//  QFile file1(q1);
//  bool isOpened1 = file1.open(QFile::WriteOnly);
//  if (!isOpened1)
//  {

//      return false;
//  }
//  QTextStream ts1(&file1);
//  ts1 << xml_text1;

//  file1.close();
   return true;
} // save main and extra entities here
// students
vector<Station> XmlStorage::getAllStations(void)
{
    return stations_;
}
optional<Station> XmlStorage::getStationById(int station_id)
{
    for (Station station : stations_)
    {
        if (station.id == station_id)
        {
            return station;
        }
    }
    return nullopt;
}
bool XmlStorage::updateStation(const Station &station)
{
    for (Station & station1 : stations_)
    {
        if(station1.id == station.id)
        {
            station1.name = station.name;
            station1.branch = station.branch;
            station1.city = station.city;
            station1.country = station.country;
            station1.depth = station.depth;
            station1.time = station.time;
            return true;
        }
    }
   return false;
}
bool XmlStorage::removeStation(int station_id)
{
    for(auto i = stations_.begin(); i < stations_.end();i++)
    {
      if (station_id == i->id)
      {
         stations_.erase(i);
         return true;
      }
    }
    return false;
}
int XmlStorage::insertStation(const Station &station)
{
    Station station1 = station;
    station1.id = getNewStationId();
    stations_.push_back(station1);
    return station1.id;
}
// courses
vector<Branch> XmlStorage::getAllBranches(void)
{
return branchs_;
}
optional<Branch> XmlStorage::getBranchById(int branch_id)
{
    for (Branch branch : branchs_)
    {
        if (branch.id == branch_id)
        {
            return branch;
        }
    }
    return nullopt;
}
bool XmlStorage::updateBranch(const Branch &branch)
{
    for (Branch branch1 : branchs_)
    {
        if(branch1.id == branch.id)
        {
            branch1.color = branch.color;
            branch1.depth = branch.depth;
            branch1.amount = branch.amount;
            branch1.id = branch.id;
            return true;
        }
    }
   return false;

}
bool XmlStorage::removeBranch(int branch_id)
{
   for(auto i = branchs_.begin(); i < branchs_.end();i++)
    {
      if (branch_id == i->id)
      {
         branchs_.erase(i);
         return true;
      }
    }
    return false;
}
int XmlStorage::insertBranch(const Branch &branch)
{

    Branch branch1 = branch;
    branch1.id = getNewStationId();
    branchs_.push_back(branch1);
    return branch1.id;
}
optional<User> XmlStorage::getUserAuth(string & username, string & password)
{
    return nullopt;
}
   // links
vector<Branch> XmlStorage::getAllStationBranches(int station_id)
{
     vector<Branch> br;
    return br;
}
 bool XmlStorage::insertStationBranch(int station_id, int branch_id)
 {
     return true;
 }
 bool XmlStorage::removeStationBranch(int station_id, int branch_id)
 {
     return true;
 }
vector<Station> XmlStorage::getAllUserStations(int user_id)
{
     vector<Station> br;
    return br;
}
 void XmlStorage::links(int stat_id, int user_id)
 {
     return;
 }
