#ifndef TABLE_HPP_
#define TABLE_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

typedef string Cell;

class Table
{
private:
string TableName;
vector<string> TBCollumnNames;
vector<string> TBCollumnTypes;
list< vector<Cell> > TableData;
public:
//Default constructor
Table();
//Constructing and creating a new table
Table(string NewTableName, vector<Cell> CollumnNames, vector<Cell> CollumnTypes);
//Constructing and opening an existing table
Table(string OpTableName);
//Table destructor
~Table();
//Function to write a series of values to the table files
void WRITE_TABLE_TF();
//Function to select specific collumns of table. Returns list of vectors of cells
//Could be used when merging tables
list< vector<Cell> > SELECT(vector<Cell> CollumnNames);//NOT USED
//Add new rows to the table
void INSERT(vector<string> collumns, vector<Cell> values);
//Add new rows to the table, w/o specifying the collumns
void INSERT(vector<Cell> values);
//Adds a list of new rows. NOT SAFE, no cheks performed whether the collumns match
//Possible us is when merging two tables
void INSERT(list<vector<Cell> >values);
//Print the table
void PRINT();
//Returns list of pointers to rows where conditions are met
list< vector<Cell>* > WHERE(vector<Cell> Collumns, vector< vector<string> > FilterCond, vector< vector<Cell> > FilterVal);
//Changes/updates specific collumns
void UPDATE(vector<Cell> UpCollumns, vector<Cell> UpVal, vector<Cell> Collumns, vector< vector<string> > FilterCond, vector< vector<Cell> > FilterVal);
//Deletes all data stored in table
void DELETE();
//Deletes specific rows of table data
void DELETE(vector<Cell> Collumns, vector< vector<string> > FilterCond, vector< vector<Cell> > FilterVal);
};
#endif
