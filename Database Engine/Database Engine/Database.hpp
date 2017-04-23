#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <iostream>
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
  Database(string Name);//TESTED
  //Database destructor
  ~Database();
  //Function to open an existing database
  void OPEN();//TESTED
  //Funciton to delete database
  void DROP_DATABASE();
  //Function to create a new table
  void CREATE_TABLE(string NewTableName, vector<string> CollumnNames, vector<string> CollumnTypes);//TESTED
  //Function to delete a table
  void DROP_TABLE(string TableName);
  //Updates database and table files
  void SAVEALL();

  //Checks if such table exists
  bool CHECK_TABLE(string TBName);
  //Add new rows to the table
  void INSERT_INTO_TABLE(string TBName, vector<string> collumns, vector<Cell> values);
  //Add new rows to the table, w/o specifying the collumns
  void INSERT_INTO_TABLE(string TBName, vector<Cell> values);
  //Adds a list of new rows. NOT SAFE, no cheks performed whether the collumns match
  //Possible us is when merging two tables
  void INSERT_INTO_TABLE(string TBName, list<vector<Cell> >values);
  //Print table
  void PRINT_TABLE(string TBName);
  //Deletes all data stored in table
  void DELETE_TABLE(string TBName);
  //Deletes specific rows of table data
  void DELETE_TABLE(string TBName, vector<Cell> Collumns, vector< vector<char> > FilterCond, vector< vector<Cell> > FilterVal);

};
#endif
