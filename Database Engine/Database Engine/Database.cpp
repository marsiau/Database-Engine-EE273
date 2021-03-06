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
    {cout<<"ERROR\nCan not open database file\n";}
    else
    {
      string TableName;
      //Read all the table names in the database
      while(getline(DBStream, TableName, ','))
      {
        //New with non trivial constructor http://www.drdobbs.com/cpp/calling-constructors-with-placement-new/232901023
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
  //Delete the database file
  deleteFile(DBName);
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
        //Save tables
        (*(It->second)).WRITE_TABLE_TF();
        ++It;
      }
    }
  }
}
//Lists all tables
void Database::LIST_TABLES()
{
  TableMap::iterator It = MapOfTables.begin();
  while(It != MapOfTables.end())
  {
    //Print tables
    cout << (It->first) <<endl;
    ++It;
  }
}
//Checks if such table exists
bool Database::CHECK_TABLE(string TBName)
{
  if(MapOfTables.find(TBName) == MapOfTables.end())
  {return false;}//not found
  else
  {return true;}//found
}

//Add new rows to the table
void Database::INSERT_INTO_TABLE(string TBName, vector<string> collumns, vector<Cell> values)
{
  (*MapOfTables.find(TBName)->second).INSERT(collumns, values);
}

//Add new rows to the table, w/o specifying the collumns
void Database::INSERT_INTO_TABLE(string TBName, vector<Cell> values)
{
  (*MapOfTables.find(TBName)->second).INSERT(values);
}

//Adds a list of new rows. NOT SAFE, no cheks performed whether the collumns match
//Possible us is when merging two tables
void Database::INSERT_INTO_TABLE(string TBName, list<vector<Cell> >values)
{
  (*MapOfTables.find(TBName)->second).INSERT(values);
}

//Print one of the tables
void Database::PRINT_TABLE(string TBName)
{
  (*(MapOfTables.find(TBName))->second).PRINT();
}

//Prints rows of a table that meet WHERE conditions
void Database::PRINT_TABLE(string TBName, vector<Cell> Collumns, vector< vector<string> > FilterCond, vector< vector<Cell> > FilterVal)
{
  (*(MapOfTables.find(TBName))->second).PRINT(Collumns, FilterCond, FilterVal);
}

//Deletes all data stored in table
void Database::DELETE_TABLE(string TBName)
{
  (*(MapOfTables.find(TBName))->second).DELETE();
}
//Deletes specific rows of table data
void Database::DELETE_TABLE(string TBName, vector<string> Collumns, vector< vector<string> > FilterCond, vector< vector<Cell> > FilterVal)
{
  (*MapOfTables.find(TBName)->second).DELETE(Collumns, FilterCond, FilterVal);
}

//Changes/updates specific collumns
void Database::UPDATE_TABLE(string TBName, vector<string> UpCollumns, vector<Cell> UpVal, vector<Cell> Collumns, vector< vector<string> > FilterCond, vector< vector<Cell> > FilterVal)
{
  (*MapOfTables.find(TBName)->second).UPDATE(UpCollumns, UpVal, Collumns, FilterCond, FilterVal);
}
