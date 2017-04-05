
#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Tables.hpp"

using namespace std;

class Database
{
private:
  string DBName;
  vector<string> TableNames;
  list<Table> Tables;
public:
  Database();
  ~Database();
};
#endif
