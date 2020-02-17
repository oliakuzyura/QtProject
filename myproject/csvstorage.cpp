#include "csvstorage.h"
#include <iostream>
using namespace std;
Station CsvStorage::rowToStation(const CsvRow &row)
{
    Station station;
    station.name = row[0];
    station.city = row[1];
    station.country = row[2];
    station.branch = row[3];
    station.depth = stof(row[4]);
    station.time = stof(row[5]);
    station.id = stoi(row[6]);
    return station;
}
CsvRow CsvStorage::stationToRow(const Station &st)
{
    CsvRow row;
    string str;
    str = st.name;
    row.push_back(str);
    str = st.city;
    row.push_back(str);
    str = st.country;
    row.push_back(str);
    str = st.branch;
    row.push_back(str);
    str = to_string(st.depth);
    row.push_back(str);
    str = to_string(st.time);
    row.push_back(str);
    str = to_string(st.id);
    row.push_back(str);
    return row;
}
Branch CsvStorage::rowToBranch(const CsvRow &row)
{
    Branch branch;
    branch.color = row[0];
    branch.depth = stof(row[1]);
    branch.amount = stof(row[2]);
    branch.id = stoi(row[3]);
    return branch;
}
CsvRow CsvStorage::branchToRow(const Branch &cs)
{
    CsvRow row;
    string str;
    str = cs.color;
    row.push_back(str);
    str = to_string(cs.depth);
    row.push_back(str);
    str = to_string(cs.amount);
    row.push_back(str);
    str = to_string(cs.id);
    row.push_back(str);
    return row;
}

int CsvStorage::getNewStationId()
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
int CsvStorage::getNewBranchId()
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

bool CsvStorage::load()
{
    string str = dir_name_ + "/station.csv";
    ifstream fp;
    fp.open(str, ios::in);
    if (!fp.good())
    {
        return false;
    }
    string str1;
    string str2;
    while (getline(fp, str1))
    {
        str2 += str1 + "\n";
    }
    CsvTable table = Csv::createTableFromString(str2);
    for (auto i = table.begin() + 1; i < table.end(); i++)
    {
        Station station = rowToStation(*i);
        stations_.push_back(station);
    }
    fp.close();
    // branch
    string st = dir_name_ + "/branch.csv";
    ifstream fp1;
    fp1.open(st, ios::in);
    if (!fp1.good())
    {
        return false;
    }
    string st1;
    string st2;
    while (getline(fp1, st1))
    {
        st2 += st1 + "\n";
    }
    CsvTable table1 = Csv::createTableFromString(st2);
    for (auto i = table1.begin() + 1; i < table1.end(); i++)
    {
        Branch branch = rowToBranch(*i);
        branchs_.push_back(branch);
    }
    fp1.close();
    return true;
} // load main and extra entities here
bool CsvStorage::save()
{
    string str = dir_name_ + "/station.csv";
    ofstream fp;
    CsvTable table;
    for (Station st : stations_)
    {
        CsvRow row = stationToRow(st);
        table.push_back(row);
    }
    fp.open(str, ios::out);
    fp << "name,city,country,branch,depth,time,id\n"
       << Csv::createStringFromTable(table);

    fp.close();
    //branch
    string st1 = dir_name_ + "/branch.csv";
    ofstream fp1;
    CsvTable table1;
    for (Branch br : branchs_)
    {
        CsvRow row = branchToRow(br);
        table1.push_back(row);
    }
    fp1.open(st1, ios::out);
    fp1 << "name,city,country,branch,depth,time,id\n"
       << Csv::createStringFromTable(table1);

    fp1.close();
    return true;
} // save main and extra entities here
// students
vector<Station> CsvStorage::getAllStations(void)
{
    return stations_;
}
optional<Station> CsvStorage::getStationById(int station_id)
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
bool CsvStorage::updateStation(const Station &station)
{
    for (Station station1 : stations_)
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
bool CsvStorage::removeStation(int station_id)
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
int CsvStorage::insertStation(const Station &station)
{
    Station station1 = station;
    station1.id = getNewStationId();
    stations_.push_back(station1);
    return station1.id;
}
// courses
vector<Branch> CsvStorage::getAllBranches(void)
{
return branchs_;
}
optional<Branch> CsvStorage::getBranchById(int branch_id)
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
bool CsvStorage::updateBranch(const Branch &branch)
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
bool CsvStorage::removeBranch(int branch_id)
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
int CsvStorage::insertBranch(const Branch &branch)
{

    Branch branch1 = branch;
    branch1.id = getNewStationId();
    branchs_.push_back(branch1);
    return branch1.id;
}
