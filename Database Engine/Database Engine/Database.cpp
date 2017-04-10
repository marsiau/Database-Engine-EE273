//TODO mbie move all additional functions into new file?
#include <fstream>
#include <string>
//#include <list>
#include <vector>
#include <map>
#include "Table.hpp"
#include "Database.hpp"
using namespace std;

typedef map<string, Table*> TableMap;
typedef pair<string, Table*> TableMapPair;

//-------------------- Auxiliary functions --------------------
//Checks if filename has ".txt" and changes it dpending on chng
string chkType(string InStr, bool chng)//TESTED
{
  int InSize = InStr.size();
  string strEnd = {InStr[InSize-4], InStr[InSize-3], InStr[InSize-2], InStr[InSize-1]};
  if(strEnd == ".txt")
  {
    if(chng)
    {return InStr;}//Don't change
    else
    {return InStr.erase(InStr.size() - 4);}//Remove ".txt"
  }
  else
  {
    if(chng)
    {return InStr += ".txt";}//Add ".txt"
    else
    {return InStr;}//Don't change
  }
}
//Check if file exists
//From http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
inline bool exists_test (const std::string& name)
{
    ifstream f(name.c_str());
    return f.good();
}
//Deletes a file
void deleteFile(string FileName)
{
  //From http://www.cplusplus.com/reference/cstdio/remove/
  string FileName = chkType(FileName, 1);//Add the file type
  if( remove(FileName.c_str()) != 0 )
    perror( "Error deleting file" );
    else
    puts( "File successfully deleted" );
}
//-------------------- Auxiliary functions END --------------------

//Create an emty database
Database::Database(string Name)
{
  DBName = chkType(Name, 0);
}

//Database destructor
Database::~Database()
{
  //If database is not emty, save it
  if(!MapOfTables.emty())
  {
    //Iterate through map and destruct Table objects
    TableMap::iterator It = MapOfTables.begin();
    while(It != MapOfTables.end())
    {
      (It->second).~Table();
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
        TableNames.push_back(TableName);
        //new with non trivial constructor http://www.drdobbs.com/cpp/calling-constructors-with-placement-new/232901023
        Table* = pTable new (TableName);
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
  while(It != MapOfTables.end())//TODO is it really != or <=??/
  {
    //Destruct the Table object
    (It->second).~Table();
    //Delete the table file
    deleteFile(It->first);
    ++It;
  }
  //Delete the map contents
  MapOfTables.clear();
}

//Function to create a new table
void CREATE_TABLE(string NewTableName, vector<Cell> CollumnNames, vector<Cell> CollumnTypes)
{
  Table* = pTable new (string NewTableName, vector<Cell> CollumnNames, vector<Cell> CollumnTypes);
  if(!pTable){cout<<"ERROR allocating the Table";}
  MapOfTables.insert(make_pair(NewTableName), pTable);
}

//Function to delete a table
void Database::DROP_TABLE(string TableName)
{
  //Destruct the Table object
  MapOfTables.find(TableName)->second.~Table();
  //Remove data from the map container
  MapOfTables.erase(TableName);
  //Delete any remaining files
  deleteFile(TableName);
}
