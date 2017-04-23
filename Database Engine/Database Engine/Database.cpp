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
Database::Database(string Name)//TESTED
{
  DBName = chkType(Name, 0);
}

//Database destructor
Database::~Database()
{
  string FileName = chkType(DBName, 1); //Add the file type
  ofstream DBStream;
  DBStream.open(FileName, ios::trunc);
  if(!DBStream.is_open())
  {
    cout<<"Error opening a database file\n";
  }
  else
  {
    //If database is not emty, save it
    if(!MapOfTables.empty())
    {
      //Iterate through map and destruct Table objects
      TableMap::iterator It = MapOfTables.begin();
      while(It != MapOfTables.end())
      {
        //Save the table name inside database file
        DBStream << (It->first) <<',';
        //Destruct the Table
        (*(It->second)).~Table();
        ++It;
      }
      //Clear the map contents
      MapOfTables.clear();
    }
    //If it is emty then there is nothing to be cleared
  }
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
  MapOfTables.clear();
}

//Function to create a new table
void Database::CREATE_TABLE(string NewTableName, vector<string> CollumnNames, vector<string> CollumnTypes)
{
  Table* pTable = new Table (NewTableName, CollumnNames, CollumnTypes);
  if(!pTable){cout<<"ERROR allocating new Table\n";}
  else
  {
    MapOfTables.insert( {NewTableName, pTable} );
  }
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

void Database::SAVEALL()
{
  string FileName = chkType(DBName, 1); //Add the file type
  ofstream DBStream;
  DBStream.open(FileName, ios::trunc);
  if(!DBStream.is_open())
  {
    cout<<"Error opening a database file\n";
  }
  else
  {
    //If database is not emty, save it
    if(MapOfTables.size() > 0)
    {
      //Iterate through map
      TableMap::iterator It = MapOfTables.begin();
      while(It != MapOfTables.end())
      {
        //Save the table name inside database file
        DBStream << (It->first) <<',';
        //Destruct the Table
        (*(It->second)).WRITE_TABLE_TF();
        ++It;
      }
    }
  }
}

//Add new rows to the table
void Database::INSERT_INTO_TABLE(string TBName, vector<string> collumns, vector<Cell> values)
{
  (*MapOfTables.find(TBName)->second).INSERT(vector<string> collumns, vector<Cell> values);
}
//Add new rows to the table, w/o specifying the collumns
void Database::INSERT_INTO_TABLE(string TBName, vector<Cell> values)
{
  (*MapOfTables.find(TBName)->second).INSERT(vector<Cell> values);
}
//Adds a list of new rows. TODO NOT SAFE, no cheks performed wether the collumns match
void Database::INSERT_INTO_TABLE(string TBName, list<vector<Cell> >values)
{
  (*MapOfTables.find(TBName)->second).INSERT(list<vector<Cell> >values);
}

void Database::PRINT_TABLE(string TBName)
{
  (*MapOfTables.find(TBName)->second).PRINT();
}
