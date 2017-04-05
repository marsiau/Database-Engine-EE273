#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Tables.hpp"
#include "DatabaseV1.hpp"

//Check if file exists
//From http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
inline bool exists_test0 (const std::string& name)
{
    ifstream f(name.c_str());
    return f.good();
}


//Create an emty database
Database::Database(string Name);
{
  string DBName = Name;
  vector<string> TableNames;
  list<Table> Tables;
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
