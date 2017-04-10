
#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include "Table.hpp"

using namespace std;

class Database
{
private:
  string DBName;
  //vector<string> TableNames;//TODO do we need this?
  //use maps, allows to search by key("TableName"), no need to iterate through vector to find the correct name
  //http://thispointer.com/stdmap-tutorial-part-1-usage-detail-with-examples/
  map<string, Table*> MapOfTables;

public:
  //Database constructor, creates and emty database
  Database(string Name);
  //Database destructor
  ~Database();
  //Function to open an existing database
  void OPEN();
  //Function to create a new table
  void CREATE_TABLE(string NewTableName, vector<Cell> CollumnNames, vector<Cell> CollumnTypes);
  //Function to delete a table
  void Database::DROP_TABLE(string TableName);
  void DROP_DATABASE();
};
#endif
