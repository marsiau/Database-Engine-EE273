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
vector<Cell> TBCollumnNames;
vector<Cell> TBCollumnTypes; //TODO Do we really need this? yup
list< vector<Cell> > TableData;
public:
//Table constructor. Creating a new table
Table(string NewTableName, vector<Cell> CollumnNames, vector<Cell> CollumnTypes);
//Table constructor. Opening an existing table
Table(string OpTableName);
//Table destructor
~Table();
//Function to delete a table
void DROP_TABLE(string TableName);
//Function to write a series of values to the table file
void WRITE_TABLE_TF();
};
#endif
