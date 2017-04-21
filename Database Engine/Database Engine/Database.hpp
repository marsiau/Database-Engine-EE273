
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
  //Funciton to delete database
  void DROP_DATABASE();
  //Function to create a new table
  void CREATE_TABLE(string NewTableName, vector<string> CollumnNames, vector<string> CollumnTypes);
  //Function to delete a table
  void DROP_TABLE(string TableName);
};
#endif
