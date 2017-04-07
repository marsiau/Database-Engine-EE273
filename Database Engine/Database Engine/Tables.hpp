#ifndef TABLES_HPP_
#define TABLES_HPP_

#include "Tables.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>

//using Cell = string;
using namespace std;
typedef string Cell;

class Table
{
private:
string TableName;
//TODO Why vector of cells for names and types?
vector<Cell> TBCollumnNames;
vector<Cell> TBCollumnTypes;
list< vector<Cell> > TableData;
public:
//Table constructor. Creating a new table
Table(string NewTableName, vector<Cell> CollumnNames, vector<Cell> CollumnTypes);
//Table constructor. Opening an existing table
Table(string OpTableName);
//Table destructor
~Table();
//Function to delete a table
void DROP_TABLE();//TODO mbie move to Database?
//Function to write a series of values to the table files
void WRITE_TABLE_TF();
//Function to select specific collumns of table. Returns list of vectors of cells
list< vector<Cell> > SELECT(vector<Cell> CollumnNames);
//Function to select specific collumns of table. Returns list of vectors of pointers
list< vector<Cell*> >SELECTP(vector<Cell> CollumnNames);
//Add new rows to the table
void INSERT(vector<string> collumns, vector<Cell> values);
//Add new rows to the table, w/o specifying the collumns
void INSERT(vector<Cell> values);
//Adds a list of new rows. TODO NOT SAFE
void INSERT(list<vector<Cell> >values);
//Print the table
void PRINT();
};
#endif
