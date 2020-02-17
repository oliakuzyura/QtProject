#ifndef SQLITE_STORAGE_H
#define SQLITE_STORAGE_H
#include "storage.h"
#include <QtSql>
#include <QSqlDatabase>

class SqliteStorage : public Storage
{
    const string dir_name_;
    QSqlDatabase db_;
public:
    SqliteStorage(const string & dir_name);

     bool open() ;  // load main and extra entities here
     bool close() ;  // save main and extra entities here
    // students
     vector<Station> getAllStations(void) ;
    optional<Station> getStationById(int station_id) ;
    bool updateStation(const Station &station) ;
    bool removeStation(int station_id);
     int insertStation(const Station &station) ;
    // courses
     vector<Branch> getAllBranches(void) ;
     optional<Branch> getBranchById(int branch_id) ;
     bool updateBranch(const Branch &branch) ;
     bool removeBranch(int branch_id) ;
     int insertBranch(const Branch &branch) ;
      vector<Station> getAllUserStations(int user_id) ;
      optional<User> getUserAuth(string & username, string & password) ;
        // links
      vector<Branch> getAllStationBranches(int station_id) ;
      bool insertStationBranch(int station_id, int branch_id) ;
      bool removeStationBranch(int station_id, int branch_id) ;
       void links(int stat_id, int user_id);
};

#endif // SQLITE_STORAGE_H
