#pragma once
#include <vector>
#include <string>
#include "optional.h"
#include "station.h"
#include "branch.h"
#include "storage.h"
#include <QtXml>
using namespace std;

class XmlStorage : public Storage
{
    QString dir_name_;

    vector<Station> stations_;
    vector<Branch> branchs_;
    int getNewBranchId();

  public:
    XmlStorage(QString & dir_name) : dir_name_(dir_name) { }
     int getNewStationId();
    bool open();  // load main and extra entities here
    bool close();  // save main and extra entities here
    // students
    vector<Station> getAllStations(void);
     optional<Station> getStationById(int station_id);
    bool updateStation(const Station &station);
    bool removeStation(int station_id);
    int insertStation(const Station &station);
    // courses
    vector<Branch> getAllBranches(void);
    optional<Branch> getBranchById(int branch_id);
    bool updateBranch(const Branch &branch);
    bool removeBranch(int branch_id);
    int insertBranch(const Branch &branch);
    optional<User> getUserAuth(string & username, string & password);
       // links
   vector<Branch> getAllStationBranches(int station_id);
     bool insertStationBranch(int station_id, int branch_id);
     bool removeStationBranch(int station_id, int branch_id);
        vector<Station> getAllUserStations(int user_id);
        void links(int stat_id, int user_id);
};


