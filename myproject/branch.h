#pragma once
#include <string>
#include <QMetaType>
using std::string;  
struct Branch
{
string color;
float depth;
int amount;
int id;
};
Q_DECLARE_METATYPE(Branch)
