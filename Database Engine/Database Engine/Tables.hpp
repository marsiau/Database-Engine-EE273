#ifndef TABLES_HPP_
#define TABLES_HPP_

#include "Tables.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class Table
{
private:
fstream TableStream;
public:
//Table constructor
Table();
//Table destructor
~Table();
//Function to write a series of values to the table
void WRITE_TABLE(list< vector<string> > CollumnValues);
//Function to create a new table
void CREATE_TABLE(string TableName, vector<string> CollumnNames, vector<string> CollumnTypes);
//Function to create a new table and include values
void CREATE_TABLE (string TableName, vector<string> CollumnNames, vector<string> CollumnTypes, list< vector<string> > CollumnValues);
//Function to delete a table
void DROP_TABLE(string TableName);
};
#endif
