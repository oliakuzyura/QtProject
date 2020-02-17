#include "csv.h" // generic list (array implementation)

CsvTable Csv::createTableFromString(const string &csv_str)
{
  
    string str;
    CsvRow row;
    CsvTable table;


    for (auto items = csv_str.begin(); items != csv_str.end(); items ++)
    {
        if (*items == '"')
        {
            str += *items;
            items++;
            while (*items != '"')
            {
                str += *items;
                items++;
            }
            str += *items;
            items++;
        }
        if (*items == ',')
        {
            row.push_back(str);
            str.resize(0);
        }
        else if (*items == '\n')
        {
            row.push_back(str);
            str.resize(0);
            table.push_back(row);
            row.resize(0);
        }
        else if (*items == '\0')
        {
            row.push_back(str);
            str.resize(0);
            table.push_back(row);
            row.resize(0);
            break;
        }
        else if (*items != '\r')
        {
           str += *items;
        }
    }
    return table;
} // parse csv & fill table

string Csv::createStringFromTable(const CsvTable &csv_table)
{
    string str;

    for (CsvRow items: csv_table)
    {
        
        for (string str1: items)
        {
            str += str1;
            if (str1 != items[items.size()-1])
            {
                str += ",";
            }
        }
        str += "\n";
    }
    return str;
} // malloc string array and fill it with csv
