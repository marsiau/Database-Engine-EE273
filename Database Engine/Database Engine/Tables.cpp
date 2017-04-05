//TODO remove all cout statements? log file?
#include "Tables.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <iomanip>
#include <cstdio>

using namespace std;
typedef string Cell; //supposedly same thing as: using Cell = string;

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
//Generate a string of characters of size "size"
string genString(int size, char character)
{
  string temp(size, character);
  return temp;
}
//End

//Table constructor. Creating a new table
Table::Table(string NewTableName, vector<Cell> CollumnNames, vector<Cell> CollumnTypes)
{
  //TODO check if contains .txt
  TableName = NewTableName;
  TBCollumnNames = CollumnNames;
  TBCollumnTypes = CollumnTypes;
  TableData;
}

//Table constructor. Opening an existing table
Table::Table(string OpTableName)
{
  TableName = OpTableName;
  ifstream TableStream;
  //TODO check if table exists
  string FileName = TableName + ".txt"; //Add the file type
  TableStream.open(FileName);
    if(!TableStream.is_open())
  {
      cout<<"Error creating a table file\n";
  }
  else
  {
    //Read and store Collumn Names, Collumn Types and Table Data
    TBCollumnNames;
    TBCollumnTypes;
    TableData;
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
  //Save table in a file
  WRITE_TABLE_TF();
}

//Function to delete a table
void Table::DROP_TABLE()
{
  //From http://www.cplusplus.com/reference/cstdio/remove/
  string FileName = TableName + ".txt"; //Add the file type
  if( remove(FileName.c_str()) != 0 )
    perror( "Error deleting file" );
  else
    puts( "File successfully deleted" );
}

//Function to write a series of values to the table file
void Table::WRITE_TABLE_TF()
{
  //ios::trunc - 	If the file is opened for output operations and it already existed,
  //its previous content is deleted and replaced by the new one.
  string FileName = TableName + ".txt"; //Add the file type
  ofstream TableStream;
  TableStream.open(FileName, ios::trunc);
  if(!TableStream.is_open())
  {
      cout<<"Error opening a table file\n";
  }
  else
  {
    //Pushing table collumn types and names to the data list
    //TODO THIS IS BAD, really bad
    list< vector<Cell> > TableData = this->TableData;
    TableData.push_front(TBCollumnTypes);
    TableData.push_front(TBCollumnNames);
    //Writing the TableData and collumn types&names to file
    list< vector<Cell> >::iterator LIt; // LIt - List Iterator
    vector<Cell>::iterator VIt; // VIt - Vector Iterator
    for(LIt = TableData.begin(); LIt != TableData.end(); ++LIt)
    {
      for(VIt = LIt->begin(); VIt != LIt->end(); ++VIt)
      {
        TableStream << (*VIt) << ',';
      }
      TableStream << endl;
    }
    TableStream.close();
  }
}
//TODO TEST

list< vector<Cell> > Table::SELECT(vector<Cell> Collumns)
{
  vector<int> CollNum;
  list< vector<Cell> > Selection;
  //TODO this could be reused
  vector<Cell>:: iterator VItC; // VIt - Vector Iterator for Collumns
  vector<Cell>:: iterator VItN; // VIt - Vector Iterator for Names
  for(VItC = Collumns.begin(); VItC < Collumns.end(); ++VItC)
  {
    bool found = false;
    int i = 0;
    for(VItN = TBCollumnNames.begin(); !found && VItN != TBCollumnNames.end(); ++VItN)
    {
      if((*VItC) == (*VItN))
      {
        CollNum.push_back(i);
        found  = true;
      }
      else
      {
        i++;
      }
    }
  }

  list< vector<Cell> >:: iterator LItD; // LIt - List Iterator for TableData
  for(LItD = TableData.begin(); LItD != TableData.end(); ++LItD)
  {
    //Create a temp vector to store selected row data
    vector<Cell> temp;
    for(int i = 0; i < CollNum.size(); i++)
    {
      temp.push_back((*LItD)[i]);
    }
    //Push temp to Selection
    Selection.push_back(temp);
  }
  return Selection;
}
//TODO TEST
//Returns list of vectors of pointers to Cell
list< vector<Cell*> > Table::SELECTP(vector<Cell> Collumns)
{
  vector<int> CollNum;
  list< vector<Cell*> > Selection;
  vector<Cell>:: iterator VItC; // VIt - Vector Iterator for Collumns
  vector<Cell>:: iterator VItN; // VIt - Vector Iterator for Names
  for(VItC = Collumns.begin(); VItC != Collumns.end(); ++VItC)
  {
    bool found = false;
    int i = 0;
    for(VItN = TBCollumnNames.begin(); !found && VItN != TBCollumnNames.end(); ++VItN)
    {
      if((*VItC) == (*VItN))
      {
        CollNum.push_back(i);
        found  = true;
      }
      else
      {
        i++;
      }
    }
  }

  list< vector<Cell> >:: iterator LItD; // LIt - List Iterator for TableData
  for(LItD = TableData.begin(); LItD != TableData.end(); ++LItD)
  {
    //Create a temp vector to store selected row data
    vector<Cell*> temp;
    for(int i = 0; i < CollNum.size(); i++)
    {
      temp.push_back(&((*LItD)[i]));
    }
    //Push temp to Selection
    Selection.push_back(temp);
  }
  return Selection;
}

//Add new rows to the table
void Table::INSERT(vector<string> collumns, vector<Cell> values)
{

  vector<string>::iterator CollIt = collumns.begin();
  //TBCollumnNames iterator declared here as the collumns should be given in order
  //thus this is only to skip collumns required to be emty
  vector<string>::iterator TBCollIt = TBCollumnNames.begin();
  vector<Cell> tempvec;

  bool found;
  for(int i = 0; CollIt != collumns.end(); ++i, ++CollIt)
  {
    found = false;
    while(TBCollIt != TBCollumnNames.end())
    {
      if((*CollIt) == (*TBCollIt))
      {
        tempvec.push_back(values[i]);
        found = true;
      }
      else
      {
        ++TBCollIt;
      }
    }
    //TODO check if everything went well
  }
  TableData.push_back(tempvec);
}
//Add new rows to the table, without specifying the collumns
void Table::INSERT(vector<Cell> values)
{
  TableData.push_back(values);
}

void Table::PRINT()
{
  const int width = 20;
  string linelim((width + 1) * TBCollumnNames.size(),'-');
  list< vector<Cell> >:: iterator LIt; // LIt - List iterator for Rows
  vector<Cell>:: iterator VIt; // VIt - Vector iterator for Collumns

  //cout << left << setw(width) << setfill(separator) << t;
  cout<<endl<<linelim<<endl;
  for(VIt = TBCollumnNames.begin(); VIt != TBCollumnNames.end(); ++VIt)
  {
    //Creating centered names.
    string temp = genString((width-(*VIt).size())/2,' ') + (*VIt);
    cout<<left<<setw(width)<<temp<<"|";
    //It's disgraceful, but it works right? :D
  }
  cout<<endl<<linelim<<endl;

  for(LIt = TableData.begin(); LIt != TableData.end(); ++LIt)
  {
    for(VIt = (*LIt).begin(); VIt != (*LIt).end(); ++VIt)
    {
      cout<<right<<setw(width)<<(*VIt)<<"|";
    }
    cout<<endl<<linelim<<endl;
  }
}

#if 0
//TODO TEST
//The WHERE clause is not only used in SELECT statement, it is also used in UPDATE, DELETE statement, etc.!
list< vector<Cell*> > Table::SELECT_WHERE(vector<Cell> Collumns, vector<string> Comparator, vector<Cell> FilterCond)
{
}
#endif
