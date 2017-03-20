#include "Tables.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>



using namespace std;

//Table constructor
Table::Table(TableName)
{
  string TableName = "TableName";
  fstream TableStream;
  TableStream.open(TableName.c_str(), ios::out | ios::app); //Opened for output operations at the end of file
  //ios::ate to delete previous info
  //TODO check whether such table does not exist? or defoult sql action
  if(!TableStream.is_open())
  {
      cout<<"Error creating a table file\n";
  }

}
//Table destructor
Table::~Table()
{
  TableStream.close();
}
//Function to write a series of values to the table
void Table::WRITE_TABLE(list< vector<string> > CollumnValues)
{
    //TableStream.seekp(0, ios::end);//go to the end of the file
    list< vector<string> >::iterator LIt; // LIt - List Iterator
    vector<string>::iterator VIt; // VIt - Vector Iterator
    for(LIt = CollumnValues.begin(); LIt != CollumnValues.end(); ++LIt)
    {
      for(VIt = LIt->begin(); VIt != LIt->end(); ++VIt)
      {
        TableStream << (*VIt) << ',';
      }
      TableStream << endl;
    }
}

//Function to create a new table
void Table::CREATE_TABLE(vector<string> CollumnNames, vector<string> CollumnTypes)
{
  //Construcing a list of table metadata
  list< vector <string> > CollumnValues;
  CollumnValues.push_back(CollumnNames);
  CollumnValues.push_back(CollumnTypes);
  WRITE_TABLE(CollumnValues);
}

//Function to create a new table and include values
void Table::CREATE_TABLE (string TableName, vector<string> CollumnNames, vector<string> CollumnTypes, list< vector<string> > CollumnValues)
{
    CREATE_TABLE (TableName, CollumnNames, CollumnTypes);
    WRITE_TABLE(CollumnValues);
}

//Function to delete a table
void Table::DROP_TABLE(string TableName)
{
  remove(TableName.c_str());
}

#if 1
list< vector<string> > Table::SELECT(vector<string> Collumns)
{

}
