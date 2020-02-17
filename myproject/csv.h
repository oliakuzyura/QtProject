#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

using CsvRow = vector<string>;   // type name alias
using CsvTable = vector<CsvRow>; // type name alias

namespace Csv
{
// parse csv, create & fill string table
CsvTable createTableFromString(const string &csv_str); 
// return a string filled with csv from string table
string createStringFromTable(const CsvTable &csv_table); 
}


