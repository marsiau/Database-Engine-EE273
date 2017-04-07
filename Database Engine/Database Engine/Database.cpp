#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Tables.hpp"
#include "Database.hpp"
using namespace std;
//Auxiliary functions
//TODO mbie move all additional functions into new file?
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
//END

//Create an emty database
Database::Database(string Name)
{
  DBName = chkType(Name, 0);
}
//Database destructor
//Database::~Database();
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
      //Read all the table names in the database
      while(DBStream.peek() != '\n')
      {
        getline(DBStream, TableName, ',');
        TableNames.push_back(TableName);
        //Table TempTable(TableName);//Open the table
        //Tables.push_back(TempTable);
        Tables.push_back(Table TempTable(TableName));
      }
    }
  }
  else{cout<<"Database does not exist\n";}
}

#if 0
//Return required table
Table* Database::PickTable(string TableName)
{
  Table* ReqTable;//Required table
  bool found = false;
  list<string>::iterator LIt = Tables.begin();
  while(LIt != Tables.end() && !found)
  (
    if(TableName == (LIt*)->TableName)
    {
      ReqTable = &(LIt*);
      found = true;
    }
    ++LIt;
  )
  return
}
#endif
