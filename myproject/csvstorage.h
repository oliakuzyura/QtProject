#ifndef CSVSTORAGE_H
#define CSVSTORAGE_H
#include <vector>
#include <string>
#include "optional.h"
#include "station.h"
#include "branch.h"
#include "csv.h"
#include "storage.h"
using namespace std;

class CsvStorage : public Storage
{
    const string dir_name_;

    vector<Station> stations_;
    vector<Branch> branchs_;

    static Station rowToStation(const CsvRow &row);
    static CsvRow stationToRow(const Station &st);
    static Branch rowToBranch(const CsvRow &row);
    static CsvRow branchToRow(const Branch &cs);

    int getNewStationId();
    int getNewBranchId();

  public:
    CsvStorage(const string & dir_name) : dir_name_(dir_name) { }

    bool load();  // load main and extra entities here
    bool save();  // save main and extra entities here
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
};

#endif // CSVSTORAGE_H
