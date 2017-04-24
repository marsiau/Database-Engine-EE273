#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "Auxilary.hpp"
#include "Database.hpp"
#include "Table.hpp"

using namespace std;

typedef map<string, Database*> DBMap;
typedef string Cell;

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
      //Parse command
      if(UsrInV[0] == "QUIT")
      {
        quit = true;
      }
      else if(UsrInV[0] == "DATABASE" && UsrInV[1] == "LIST")
      {
        for(DBMap::iterator DBMIt = MapOfDatabases.begin(); DBMIt != MapOfDatabases.end(); ++DBMIt)//Database map iterator
        {
          cout<<endl<<DBMIt->first;
          if(DBMIt == ADB) {cout<<" <- Active database";}
          cout<<endl;
        }
      }
      else if(UsrInV[0] == "MAKE" && UsrInV[1] == "ACTIVE")
      {
        if(UsrInV.size() < 3)
        {cout<<"ERROR\nDatabase name not specified\n";}
        else
        {
          ADB = MapOfDatabases.find(UsrInV[2]);
        }
      }
      else if(UsrInV[0] == "CREATE")
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
          {cout<<"ERROR\nDatabase does not exist\n";}
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
              (*(ADB->second)).CREATE_TABLE(UsrInV[2], CollumnNames, CollumnTypes);
            }
          }
        }
      }
      else if(UsrInV[0] == "OPEN" && UsrInV[1] == "DATABASE")
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
      else if(UsrInV[0] == "LIST" && UsrInV[1] == "TABLES")
      {
        (*(ADB->second)).LIST_TABLES();
      }
      else if(UsrInV[0] == "DROP")
      {
        if(UsrInV[1] == "DATABASE")
        {
          {(*(ADB->second)).DROP_DATABASE();}
          MapOfDatabases.erase(ADB);
        }
        else if(UsrInV[1] == "TABLE")
        {
          if(UsrInV.size() < 3)
          {cout<<"ERROR\ntable name not specified\n";}
          else
          {(*(ADB->second)).DROP_TABLE(UsrInV[2]);}
        }
        else {cout<<"ERROR\n";}
      }
      else if(UsrInV[0] == "INSERT" && UsrInV[1] == "INTO")
      {
        //http://stackoverflow.com/questions/571394/how-to-find-if-an-item-is-present-in-a-stdvector
        if ( !(find(UsrInV.begin(), UsrInV.end(), "VALUES") != UsrInV.end() ))
        {cout<<"ERROR\nWrong syntax\n";}
        else if(UsrInV[3] == "VALUES")//Check if collumns were specified
        {//If not, create a vector of values and insert into table
          vector<Cell> values;
          for(vector<string>::iterator UsrInVIt = (UsrInV.begin()) + 4; UsrInVIt != UsrInV.end(); ++UsrInVIt)
          {
            values.push_back(*UsrInVIt);
          }
          (*(ADB->second)).INSERT_INTO_TABLE(UsrInV[2], values);
        }
        else
        {//If specified, create a vector of collumns and a vector of values and insert into table
          vector<Cell> collumns;
          vector<Cell> values;
          vector<string>::iterator UsrInVIt;
          for(UsrInVIt = UsrInV.begin() + 3; (*UsrInVIt) != "VALUES"; ++UsrInVIt)//Create vector of collumns
          {
            collumns.push_back(*UsrInVIt);
          }
          ++UsrInVIt;//Ignore "VALUES"
          cout<<"pisk\n"<<*UsrInVIt<<endl;
          while(UsrInVIt != UsrInV.end())//Create vector of values
          {
            values.push_back(*UsrInVIt);
            ++UsrInVIt;
            cout<<"pisk\n"<<endl;
          }
          (*(ADB->second)).INSERT_INTO_TABLE(UsrInV[2], collumns, values);
        }
      }
      else if(UsrInV[0] == "PRINT" && UsrInV[1] == "TABLE")
      {
        if(UsrInV.size() < 3)
        {cout<<"ERROR\nTable Name not supplied\n";}
        else if(!((*(ADB->second)).CHECK_TABLE(UsrInV[2])))
        {cout<<"ERROR\nTable does not exist\n";}
        else
        {
          (*(ADB->second)).PRINT_TABLE(UsrInV[2]);
        }
      }
      else if(UsrInV[0] == "DELETE" && UsrInV[1] == "FROM")
      {
        if(UsrInV.size() == 3)
        {
          (*(ADB->second)).DELETE_TABLE(UsrInV[2]);//Deletes all rows in the table
        }
        else
        {
          if(!((UsrInV.size() - 4) > 0 && (UsrInV.size() - 4) % 3 == 0))
          {cout<<"ERROR\nNot enough data provided\n";}
          else
          {
            vector<string> Collumns;
            vector< vector<char> > FilterCond;
            vector<char> FilterCondVec;
            vector< vector<Cell> > FilterVal;
            vector<Cell> FilterValVec;
            vector<string>::iterator UsrInVIt = UsrInV.begin() + 4;
            string CollumnName = "";
            while(UsrInVIt != UsrInV.end())
            {
              if((*UsrInVIt) == CollumnName)
              {
                ++UsrInVIt;//Skip Collumn Name
                FilterCondVec.push_back(char((*UsrInVIt)[0]));//Store comparison operator
                ++UsrInVIt;
                FilterValVec.push_back(*UsrInVIt);//Store comparison value
              }
              else
              {
                //Flush previous vectors
                if(!FilterCondVec.empty())
                {
                  FilterCond.push_back(FilterCondVec);
                  FilterCondVec.clear();
                }
                if(!FilterValVec.empty())
                {
                  FilterVal.push_back(FilterValVec);
                  FilterValVec.clear();
                }
                CollumnName = (*UsrInVIt);
                Collumns.push_back(CollumnName);//Store collumn name
                ++UsrInVIt;
                FilterCondVec.push_back(char((*UsrInVIt)[0]));//Store comparison operator
                ++UsrInVIt;
                FilterValVec.push_back(*UsrInVIt);//Store comparison value
              }
              ++UsrInVIt;
            }
            //Flush last words
            FilterCond.push_back(FilterCondVec);
            FilterVal.push_back(FilterValVec);
            //Delete them
            (*(ADB->second)).DELETE_TABLE(UsrInV[2], Collumns, FilterCond, FilterVal);
          }
        }
      }
      else if(UsrInV[0] == "UPDATE" && UsrInV[2] == "SET")
      {
        if ( !(find(UsrInV.begin(), UsrInV.end(), "SET") != UsrInV.end() ) && !(find(UsrInV.begin(), UsrInV.end(), "WHERE") != UsrInV.end() ))
        {cout<<"ERROR\nWrong syntax\n";}
        else
        {
          vector<string> UPCollumns;
          vector<Cell>  UPVal;
          vector<string> Collumns;
          vector< vector<char> > FilterCond;
          vector<char> FilterCondVec;
          vector< vector<Cell> > FilterVal;
          vector<Cell> FilterValVec;
          string CollumnName = "";
          vector<string>::iterator UsrInVIt = UsrInV.begin() + 3;
          while((*UsrInVIt) != "WHERE")//Read new values for UPCollumns
          {
            if((*(UsrInVIt + 1)) == "=" )//Some aditional testing
            {
              UPCollumns.push_back(*UsrInVIt);
              UsrInVIt += 2;
              UPVal.push_back(*UsrInVIt);
            }
            else
            {cout<<"ERROR\nWrong syntax\n";break;}
            ++UsrInVIt;
          }
          ++UsrInVIt;//Skip WHERE
          while(UsrInVIt != UsrInV.end())//Read the conditions
          {
            if((*UsrInVIt) == CollumnName)
            {
              ++UsrInVIt;//Skip Collumn Name
              FilterCondVec.push_back(char((*UsrInVIt)[0]));//Store comparison operator
              ++UsrInVIt;
              FilterValVec.push_back(*UsrInVIt);//Store comparison value
            }
            else
            {
              //Flush previous vectors
              if(!FilterCondVec.empty())
              {
                FilterCond.push_back(FilterCondVec);
                FilterCondVec.clear();
              }
              if(!FilterValVec.empty())
              {
                FilterVal.push_back(FilterValVec);
                FilterValVec.clear();
              }
              CollumnName = (*UsrInVIt);
              Collumns.push_back(CollumnName);//Store collumn name
              ++UsrInVIt;
              FilterCondVec.push_back(char((*UsrInVIt)[0]));//Store comparison operator
              ++UsrInVIt;
              FilterValVec.push_back(*UsrInVIt);//Store comparison value
            }
            ++UsrInVIt;
          }
          //Flush last words
          FilterCond.push_back(FilterCondVec);
          FilterVal.push_back(FilterValVec);
          (*(ADB->second)).UPDATE_TABLE(UsrInV[1], UPCollumns, UPVal, Collumns, FilterCond, FilterVal);
        }
      }
      else {cout<<"ERROR\nUnrecognised user input\nPlease try again\n";}
    }
    else {cout<<"IFSTREAM ERROR\n\n";}
  }
  //Close and free up memory
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
    MapOfDatabases.clear();//Just in case
  }
  return 0;
}
