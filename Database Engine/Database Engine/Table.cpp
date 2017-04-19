//TODO remove all cout statements? log file?
#include "Table.hpp"
#include "Auxilary.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <iomanip>
#include <cstdio>

using namespace std;
typedef string Cell; //supposedly same thing as: using Cell = string;

//-------------------- Internal functions --------------------
//Read a row from data stream
vector<Cell> ReadRow(ifstream &InputStream)//TESTED
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
//Write a row vector to the file
void WriteRow(ofstream &OutputStream, vector<Cell> Row)//TESTED
{
  vector<Cell>::iterator VIt; // VIt - Vector Iterator
  for(VIt = Row.begin(); VIt != Row.end(); ++VIt)
  {
    OutputStream << (*VIt) << ',';
  }
  OutputStream << endl;
}
//Generate a string of characters of size "size"
string genString(int size, char character)//TESTED
{
  string temp(size, character);
  return temp;
}
//Select collumns
vector<int> SelColl(vector<Cell> CollumnNames)
{
  vector<int> CollNum;
  vector<Cell>:: iterator VItC; // VIt - Vector Iterator for Collumns
  vector<Cell>:: iterator VItN; // VIt - Vector Iterator for Names
  for(VItC = CollumnNames.begin(); VItC < CollumnNames.end(); ++VItC)
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
}
//-------------------- Internal functions END --------------------

//Table constructor
//Table::Table();//For temporary table

//Creating a new table
Table::Table(string NewTableName, vector<Cell> CollumnNames, vector<Cell> CollumnTypes)//
{
  //Check if file with such name does not exist to prevent overriding
  if(!exists_test(chkType(NewTableName, 1)))
  {
    TableName = chkType(NewTableName, 0);//If ends with ".txt", drop it
    TBCollumnNames = CollumnNames;
    TBCollumnTypes = CollumnTypes;
  }
  else
  {cout<<"File with name "<<NewTableName<<"already exists\nPlese choose a different name\n";}
}

//Opening an existing table
Table::Table(string OpTableName)//TESTED
{
  TableName = chkType(OpTableName, 0);
  string FileName = chkType(OpTableName, 1);
  if(exists_test(FileName))
  {
    ifstream TableStream;
    TableStream.open(FileName);
    if(!TableStream.is_open())
    {
      cout<<"Error opening a table file\n";
    }
    else
    {
      TBCollumnNames = ReadRow(TableStream);//Retrieve Collumn Names
      TBCollumnTypes = ReadRow(TableStream);//Retrieve Collumn Types
      //Retrieve Table Data
      while(TableStream.peek() != EOF)
      {
        TableData.push_back(ReadRow(TableStream));
      }
      TableStream.close();
    }
  }
  else{cout<<"ERROR\nFile "<<FileName<<" does not exist\n";}
}

//Table destructor
Table::~Table()
{
  //Save table in a file
  // WRITE_TABLE_TF(); //TODO couses problems for temp tables figure out a different way
  if(TableName != "")//If table has a name write it to file. If not then its temporary or deleted
  {
    WRITE_TABLE_TF();
  }
}

//Function to write a series of values to the table file
void Table::WRITE_TABLE_TF()//TESTED
{
  string FileName = chkType(TableName, 1); //Add the file type
  ofstream TableStream;
  //ios::trunc - 	If the file is opened for output operations and it already existed,
  //its previous content is deleted and replaced by the new one.
  TableStream.open(FileName, ios::trunc);
  if(!TableStream.is_open())
  {
      cout<<"Error opening a table file\n";
  }
  else
  {
    //Writing Collumn names and types to the file
    WriteRow(TableStream, TBCollumnNames);
    WriteRow(TableStream, TBCollumnTypes);
    //Writing the TableData
    list< vector<Cell> >::iterator LIt; // LIt - List Iterator
    for(LIt = TableData.begin(); LIt != TableData.end(); ++LIt)
    {
      WriteRow(TableStream, (*LIt));
    }
    TableStream.close();
  }
}


list< vector<Cell> > Table::SELECT(vector<Cell> CollumnNames)
{
  vector<int> CollNum;
  list< vector<Cell> > Selection;
  //TODO this could be reused
  vector<Cell>:: iterator VItC; // VIt - Vector Iterator for Collumns
  vector<Cell>:: iterator VItN; // VIt - Vector Iterator for Names
  for(VItC = CollumnNames.begin(); VItC < CollumnNames.end(); ++VItC)
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
list< vector<Cell*> > Table::SELECTP(vector<Cell> CollumnNames)
{
  vector<int> CollNum;
  list< vector<Cell*> > Selection;
  vector<Cell>:: iterator VItC; // VIt - Vector Iterator for Collumns
  vector<Cell>:: iterator VItN; // VIt - Vector Iterator for Names
  for(VItC = CollumnNames.begin(); VItC != CollumnNames.end(); ++VItC)
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
void Table::INSERT(vector<Cell> collumns, vector<Cell> values)//TESTED
{
  //TBCollumnNames iterator declared here as the collumns should be given in order
  //thus this is only to skip collumns required to be emty
  vector<Cell>::iterator TBCollIt = TBCollumnNames.begin();
  vector<Cell>::iterator CollIt = collumns.begin();
  vector<Cell> Row;

  int i = 0;
  while(CollIt != collumns.end())
  {
    bool found = false;
    while(TBCollIt != TBCollumnNames.end() && !found)
    {
      if((*CollIt) == (*TBCollIt))
      {
        Row.push_back(values[i]);
        found = true;
      }
      else
      {
        Row.push_back("");
      }
    ++TBCollIt;
    }
    i++;
    ++CollIt;
  }
  TableData.push_back(Row);
}
//Add new rows to the table, without specifying the collumns
void Table::INSERT(vector<Cell> values)//TESTED
{
  TableData.push_back({values});
}

//Adds a list of new rows.
void Table::INSERT(list<vector<Cell> >values)//TESTED
{
  TableData.splice(TableData.end(), values);
}

//Print the table
void Table::PRINT()//TESTED
{
  const int width = 20;
  string linelim((width + 1) * TBCollumnNames.size(),'-');
  list< vector<Cell> >:: iterator LIt; // LIt - List iterator for Rows
  vector<Cell>:: iterator VIt; // VIt - Vector iterator for Collumns

  int Collumns = 0; //To record how many collumns there are
  int pCollumns; //Printed collumns
  //Print collumn names
  cout<<endl<<linelim<<endl;
  for(VIt = TBCollumnNames.begin(); VIt != TBCollumnNames.end(); ++VIt)
  {
    //Creating centered names.
    string temp = genString((width-(*VIt).size())/2,' ') + (*VIt);
    cout<<left<<setw(width)<<temp<<"|";
    Collumns++;
  }
  cout<<endl<<linelim<<endl;

  for(LIt = TableData.begin(); LIt != TableData.end(); ++LIt)
  {
    pCollumns = 0;
    for(VIt = (*LIt).begin(); VIt != (*LIt).end(); ++VIt)
    {
      cout<<right<<setw(width)<<(*VIt)<<"|";
      pCollumns++;
    }
    //If there is less data then collumns, print the borders
    for(int i = 0; i != (Collumns - pCollumns); i++)
    {
      cout<<genString(width, ' ')<<"|";
    }
    cout<<endl<<linelim<<endl;
  }
}

#if 0
//The WHERE clause is not only used in SELECT statement, it is also used in UPDATE, DELETE statement, etc.!
list< vector<Cell*> > Table::SELECT_WHERE(vector<Cell> Collumns, vector<Cell> FilterCond)
{
  list< vector<Cell*> > Selection;

  vector<int> CollNum = SelColl(Collumns);
  vector<int>::iterator CIt; //Cell vector iterators
  vector<Cell> >::iterator FIt; //Filter condition data iterator
  list< vector<Cell> >::iterator LIt; //Data list iterator

  for(LIt = TableData.begin(); LIt != TableData.end(); ++LIt)
  {
    for(CIt = CollNum.begin(), FIt = Filter.begin(); CIt != CollNum.end(); ++CIt, ++FIt)
    {
      if( (*LIt)[(*VIt)] == (*FIt) )
      {
        Selection.push_back(        )
      }
    }
  }

}

#endif
