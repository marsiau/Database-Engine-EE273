//TODO mbie move all additional functions into new file?
#include <fstream>
#include <string>
//#include <list>
#include <vector>
#include <map>
#include "Table.hpp"
#include "Database.hpp"
#include "Auxilary.hpp"
using namespace std;

typedef map<string, Table*> TableMap;
typedef pair<string, Table*> TableMapPair;

//-------------------- Internal functions --------------------

//-------------------- Internal functions END --------------------

//Create an emty database
Database::Database(string Name)
{
  DBName = chkType(Name, 0);
}

//Database destructor
Database::~Database()
{
  //If database is not emty, save it
  if(MapOfTables.size() > 0) //if(!MapOfTables.emty()) didn't work?!
  {
    //Iterate through map and destruct Table objects
    TableMap::iterator It = MapOfTables.begin();
    while(It != MapOfTables.end())
    {
      (*(It->second)).~Table();
      ++It;
    }
    //Clear the map contents
    MapOfTables.clear();
  }
  //If it is emty then there is nothing to be cleared
}

//Open an existing Database
void Database::OPEN()
{
  if(exists_test(DBName))
  {
    ifstream DBStream;
    DBStream.open(chkType(DBName, 1));
    if(!DBStream.is_open())
    {
      string TableName;
      while(DBStream.peek() != '\n')
      {
        //Read all the table names in the database
        getline(DBStream, TableName, ',');
        //new with non trivial constructor http://www.drdobbs.com/cpp/calling-constructors-with-placement-new/232901023
        Table* pTable = new Table (TableName);
        if(!pTable){cout<<"ERROR allocating the Table";}
        MapOfTables.insert(make_pair(TableName, pTable));
      }
    }
  }
  else{cout<<"Database does not exist\n";}
}

//Delete database
void Database::DROP_DATABASE()
{
  TableMap::iterator It = MapOfTables.begin();
  while(It != MapOfTables.end())
  {
    //Destruct the Table object
    (*(It->second)).~Table();
    //Delete the table file
    deleteFile(It->first);
    ++It;
  }
  //Delete the map contents
  //MapOfTables.clear();
}

//Function to create a new table
void Database::CREATE_TABLE(string NewTableName, vector<Cell> CollumnNames, vector<Cell> CollumnTypes)
{
  Table* pTable = new Table (NewTableName, CollumnNames, CollumnTypes);
  if(!pTable){cout<<"ERROR allocating the Table";}
  MapOfTables.insert(make_pair(NewTableName, pTable));
}

//Function to delete a table
void Database::DROP_TABLE(string TableName)
{
  //Destruct the Table object
  (*MapOfTables.find(TableName)->second).~Table();
  //Remove data from the map container
  MapOfTables.erase(TableName);
  //Delete any remaining files
  deleteFile(TableName);
}
