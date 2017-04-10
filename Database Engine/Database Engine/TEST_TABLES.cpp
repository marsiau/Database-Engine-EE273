#include "Tables.hpp"
#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

typedef string Cell;

int main()
{
  string tablename1, tablename2 = "tb2";
  cout <<"enter tablename\n";
  cin >> tablename1;

  vector<Cell> CollumnNames;
  vector<Cell> CollumnTypes;
  vector<Cell> CollumnNamesT;
  list< vector<Cell> > CollumnValues;
  list< vector<Cell> > Selection;

  CollumnNames.push_back("Name1");
  CollumnNames.push_back("Name2");
  CollumnNames.push_back("Name3");

  CollumnTypes.push_back("Type1");
  CollumnTypes.push_back("Type2");
  CollumnTypes.push_back("Type3");

  CollumnNamesT.push_back("Name1");
  CollumnNamesT.push_back("Name3");

  CollumnValues.push_back({"Val11", "Val12", "Val13"});
  CollumnValues.push_back({"Val21", "Val22", "Val23"});
  CollumnValues.push_back({"Val31", "Val32", "Val33"});

  //Table table1(tablename1, CollumnNames, CollumnTypes);
  Table table1(tablename1);
  Table table2(tablename2, CollumnNames, CollumnTypes);
  table2.INSERT(table1.SELECT(CollumnNamesT));

  table1.PRINT();
  table2.PRINT();

  return 0;

}
/*
g++ -std=c++11 -c TEST_TABLES.cpp -c Tables.cpp
g++ -std=c++11 TEST_TABLES.o Tables.o -o test.exe
*/
