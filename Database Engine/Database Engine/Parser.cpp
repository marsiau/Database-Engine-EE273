#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Auxilary.hpp"
#include "Database.hpp"
#include "Table.hpp"
using namespace std;

typedef map<string, Database*> DBMap;

//-------------------- Internal functions --------------------
vector<string> StrToVec(string InStr)
{
  vector<string> OutVec;
  string Word = "";

  for(string::iterator SIt = InStr.begin(); SIt != InStr.end(); ++SIt)
  {
    //Get rid of unvanted characters
    if((*SIt) == ' ' || (*SIt) == '(' || (*SIt) == ')' || (*SIt) == ',' || (*SIt) == '\n')
    {
      if(Word != "")
      {
        OutVec.push_back(Word);
        //Cear the word
        Word = "";
      }
    }
    else
    {
      Word += (*SIt);
    }
  }
  OutVec.push_back(Word);//push_back the last word
  return OutVec;
}
//-------------------- Internal functions END --------------------

int main()
{
  //Variable declaration
  bool quit = false;
  string UsrIn = ""; //Usesr input string
  vector<string> UsrInV; //Vector of words from user input
  //Using maps allows easy change of active database
  DBMap MapOfDatabases;//Allows having multiple open databases at the same time
  DBMap::iterator ADB;// Active database

  while(!quit)
  {
    //Get user input
    if(getline(cin, UsrIn))
    {
      UsrInV.clear();//Clear user input vector
      UsrInV = StrToVec(UsrIn);//Convert user input to a vector
      UsrIn = "";
      //Do command
      if(UsrInV[0] == "QUIT")//TESTED
      {
        quit = true;
      }
      else if(UsrInV[0] == "DATABASE" && UsrInV[1] == "LIST")//TESTED
      {
        for(DBMap::iterator DBMIt = MapOfDatabases.begin(); DBMIt != MapOfDatabases.end(); ++DBMIt)//Database map iterator
        {
          cout<<endl<<DBMIt->first;
          if(DBMIt == ADB) {cout<<" <- Active database";}
          cout<<endl;
        }
      }
      else if(UsrInV[0] == "MAKE" && UsrInV[1] == "ACTIVE")//TESTED
      {
        if(UsrInV.size() < 3)
        {cout<<"ERROR\nDatabase name not specified\n";}
        else
        {
          ADB = MapOfDatabases.find(UsrInV[2]);
        }
      }
      else if(UsrInV[0] == "CREATE")//TESTED
      {
        if(UsrInV[1] == "DATABASE")
        {
          if(UsrInV.size() < 3)
          {cout<<"ERROR\nDatabase name not specified\n";}
          else if (!( MapOfDatabases.find(UsrInV[2]) == MapOfDatabases.end() ))//Check if not opened/created
          {cout<<"ERROR\nDatabase already open\n";}
          else if(exists_test(UsrInV[2]))//Check if the DB already exists
          {
            cout<<"ERROR\nDatabase "<<UsrInV[2] <<" already exists\n";
            cout<<"To open the database use: \"OPEN DATABASE " <<UsrInV[2] <<"\"" <<endl;
          }
          else
          {
            Database* pDatabase = new Database (UsrInV[2]);//Alocate new DB
            if(!pDatabase){cout<<"Error allocating new database";}
            else
            {
              MapOfDatabases.insert(make_pair(UsrInV[2], pDatabase));
              ADB = MapOfDatabases.find(UsrInV[2]);
            }
          }
        }
        else if(UsrInV[1] == "TABLE")
        {
          if(MapOfDatabases.empty())//Check if there is any databases
          {cout<<"ERROR\nNo database exists\n";} //TODO check this
          else if(UsrInV.size() <= 3)
          {cout<<"ERROR\nNot Enough input data supplied\n";}
          else
          {
            if((int(UsrInV.size()) - 3) % 2 != 0 )
            {cout<<"ERROR\nNot Enough input data supplied\n";}
            else
            {
              vector<string> CollumnNames, CollumnTypes;
              vector<string>::iterator TIt = UsrInV.begin() + 3;
              while(TIt != UsrInV.end())
              {
                CollumnNames.push_back(*TIt);
                ++TIt;
                CollumnTypes.push_back(*TIt);
                ++TIt;
              }
              (*(ADB->second)).CREATE_TABLE(UsrInV[2], {"i", "ii","iii"}, {"i", "ii", "iii"});
            }
          }
        }
      }
      else if(UsrInV[0] == "OPEN" && UsrInV[1] == "DATABASE")//TESTED
      {
        if(UsrInV.size() < 3)
        {cout<<"ERROR\nDatabase name not specified\n";}
        else if (!( MapOfDatabases.find(UsrInV[2]) == MapOfDatabases.end() ))//Check if not opened/created
        {cout<<"ERROR\nDatabase already open\n";}
        else if(!exists_test(UsrInV[2]))//Check if the DB already exists
        {
          cout<<"ERROR\nDatabase "<<UsrInV[2] <<" does not exist\n";
          cout<<"To create the database use: \"CREATE DATABASE " <<UsrInV[2] <<"\"" <<endl;
        }
        else
        {
          Database* pDatabase = new Database (UsrInV[2]);//Alocate new DB
          if(!pDatabase){cout<<"Error allocating new database";}
          else
          {
            MapOfDatabases.insert(make_pair(UsrInV[2], pDatabase));
            ADB = MapOfDatabases.find(UsrInV[2]);
            (*(ADB->second)).OPEN();
          }
        }
      }
      else if(UsrInV[0] == "SAVE")
      {
        for(DBMap::iterator DBMIt = MapOfDatabases.begin(); DBMIt != MapOfDatabases.end(); ++DBMIt)
        {
          (*(DBMIt->second)).SAVEALL();
        }
      }
      else if(UsrInV[0] == "DROP")
      {
        if(UsrInV[1] == "DATABASE")
        {
          if(UsrInV.size() < 3)
          {cout<<"ERROR\nName not specified\n";}
          else
          {(*(ADB->second)).DROP_DATABASE();}
        }
        else if(UsrInV[1] == "TABLE")
        {
          if(UsrInV.size() < 4)
          {cout<<"ERROR\ntable name not specified\n";}
          else
          {(*(ADB->second)).DROP_TABLE(UsrInV[3]);}
        }
        else {cout<<"ERROR\n";}
      }
      else if(UsrInV[0] == "DROP")

      else {cout<<"ERROR\nUnrecognised user input\nPlease try again\n";}
    }
    else {cout<<"IFSTREAM ERROR\n\n";}
  }
  //Destruct pointers
  if(!MapOfDatabases.empty())
  {
    //Iterate through map and destruct database objects
    DBMap::iterator It = MapOfDatabases.begin();
    while(It != MapOfDatabases.end())
    {
      //Destruct the database
      (*(It->second)).~Database();
      ++It;
    }
    //Clear the map contents
    MapOfDatabases.clear();
  }
  return 0;
}

#if 0
#endif
