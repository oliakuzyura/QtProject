#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "optional.h"
#include "station.h"
#include "branch.h"
#include "csv.h"
#include "user.h"

using std::string;
using std::vector;

class Storage
{
 public:
   //virtual int getNewStationId() = 0;
   virtual bool open() = 0;  // load main and extra entities here
   virtual bool close() = 0 ;  // save main and extra entities here
   // students
   virtual vector<Station> getAllStations(void) = 0;
   virtual optional<Station> getStationById(int station_id) = 0;
   virtual bool updateStation(const Station &station) = 0;
   virtual bool removeStation(int station_id) = 0;
   virtual int insertStation(const Station &station) = 0;
   virtual vector<Station> getAllUserStations(int user_id) = 0;

   // courses
   virtual vector<Branch> getAllBranches(void) = 0;
   virtual optional<Branch> getBranchById(int branch_id) = 0;
   virtual bool updateBranch(const Branch &branch) = 0;
   virtual bool removeBranch(int branch_id) = 0;
   virtual int insertBranch(const Branch &branch) = 0;
    virtual ~Storage() {}

    virtual optional<User> getUserAuth(string & username, string & password) = 0;
       // links
    virtual vector<Branch> getAllStationBranches(int station_id) = 0;
    virtual bool insertStationBranch(int station_id, int branch_id) = 0;
    virtual bool removeStationBranch(int station_id, int branch_id) = 0;
    virtual void links(int stat_id, int user_id) = 0;

};
