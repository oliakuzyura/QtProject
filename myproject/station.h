#pragma once
#include <string>
#include <QMetaType>
using std::string;  
struct Station
{
string name;
string city;
string country;
string branch;
float depth;
float time;
int id;
int branches;
};
Q_DECLARE_METATYPE(Station)
