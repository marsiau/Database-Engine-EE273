#include "Tables.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>

//using Cell = string;
typedef string Cell;
using namespace std;

//Auxiliary functions
vector<Cell> ReadRow(ifstream &InputStream)
{
  vector<Cell> Row;
  string TEMP;
  while(InputStream.peek() != '\n')
  {
    getline(InputStream, TEMP, ',');
    Row.push_back(TEMP);
  }
  InputStream.ignore(1);//To skip the \n
  return Row;
}
//End

//Table constructor. Creating a new table
Table::Table(string TableName, vector<Cell> CollumnNames, vector<Cell> CollumnTypes)
{
  Cell TableName = "TableName";
  vector<Cell> TBCollumnNames = CollumnNames;
  vector<Cell> TBCollumnTypes = CollumnTypes;
  list< vector<Cell> > TableData;
}


//Table constructor. Opening an existing table
Table::Table(string TableName)
{
  Cell TableName = "TableName";
  ifstream TableStream;
  //TODO check if table exists
  TableStream.open(TableName.c_str());
    if(!TableStream.is_open())
  {
      cout<<"Error creating a table file\n";
  }
  else
  {
    //Read and store Collumn Names, Collumn Types and Table Data
    vector<Cell> TBCollumnNames;
    vector<Cell> TBCollumnTypes;
    list< vector<Cell> > TableData;
    string TEMP;

    TBCollumnNames = ReadRow(TableStream);//Retrieve Collumn Names
    TBCollumnTypes = ReadRow(TableStream);//Retrieve Collumn Types
    //Retrieve Table Data
    while(!TableStream.eof())
    {
      TableData.push_back(ReadRow(TableStream));
    }
  }
}
//Table destructor
Table::~Table()
{
  TableStream.close();
}
//Function to write a series of values to the table file
void Table::WRITE_TABLE_TF()
{
    TableStream.seekp(0, ios::end);//go to the end of the file
    list< vector<Cell> >::iterator LIt; // LIt - List Iterator
    vector<Cell>::iterator VIt; // VIt - Vector Iterator
    for(LIt = CollumnValues.begin(); LIt != CollumnValues.end(); ++LIt)
    {
      for(VIt = LIt->begin(); VIt != LIt->end(); ++VIt)
      {
        TableStream << (*VIt) << ',';
      }
      TableStream << endl;
    }
}

//Function to delete a table
void Table::DROP_TABLE(string TableName)
{
  remove(TableName.c_str());
}

#if 0
list< vector<Cell> > Table::SELECT(vector<Cell> Collumns)
{

}
