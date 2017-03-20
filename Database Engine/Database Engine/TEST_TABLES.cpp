#include "Tables.hpp"
#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

int main()
{
  string tablename;
  cout <<"enter tablename\n";
  cin >> tablename;
  Table table1;

  vector<string> CollumnNames;

  vector<string> CollumnTypes;

  list< vector<string> > CollumnValues;


  CollumnNames.push_back("Name1");
  CollumnNames.push_back("Name2");
  CollumnNames.push_back("Name3");
  CollumnTypes.push_back("Type1");
  CollumnTypes.push_back("Type2");
  CollumnTypes.push_back("Type3");
  CollumnValues.push_back({"Val11", "Val12", "Val13"});
  CollumnValues.push_back({"Val21", "Val22", "Val23"});
  CollumnValues.push_back({"Val31", "Val32", "Val33"});
  table1.CREATE_TABLE(tablename, CollumnNames, CollumnTypes, CollumnValues);
  table1.CREATE_TABLE(tablename, CollumnNames, CollumnTypes);
  return 0;
}
/*
g++ -std=c++11 -c TEST_TABLES.cpp -c Tables.cpp
g++ -std=c++11 TEST_TABLES.o Tables.o -o test.exe
*/
