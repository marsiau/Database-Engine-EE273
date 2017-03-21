#ifndef TABLES_HPP_
#define TABLES_HPP_

#include "Tables.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>

//using Cell = string;
typedef string Cell;
using namespace std;

class Table
{
private:
string TableName;
vector<Cell> TBCollumnNames;
vector<Cell> TBCollumnTypes; //TODO Do we really need this? yup
list< vector<Cell> > TableData;
public:
//Table constructor
Table(TableName);
//Table destructor
~Table();
//Function to set the collumn names
SetCollumnTypes(vector<Cell> CollumnNames);
//Function to write a series of values to the table
void WRITE_TABLE(list< vector<Cell> > CollumnValues);
//Function to create a new table
void CREATE_TABLE(string TableName, vector<Cell> CollumnNames, vector<Cell> CollumnTypes);
//Function to create a new table and include values
void CREATE_TABLE (string TableName, vector<Cell> CollumnNames, vector<Cell> CollumnTypes, list< vector<Cell> > CollumnValues);
//Function to delete a table
void DROP_TABLE(string TableName);


//Table constructor. Creating a new table
Table::Table(string TableName, vector<Cell> CollumnNames, vector<Cell> CollumnTypes)
//Table constructor. Opening an existing table
Table::Table(string TableName)
//Table destructor
Table::~Table()
//Function to write a series of values to the table file
void WRITE_TABLE_TF();
void DROP_TABLE(string TableName);
};
#endif
