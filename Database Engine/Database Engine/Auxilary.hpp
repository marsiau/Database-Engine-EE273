#ifndef AUXILARY_HPP_
#define AUXILARY_HPP_

#include <string>
#include <fstream>

using namespace std;

//Checks if filename has ".txt" and changes it dpending on chng
string chkType(string InStr, bool chng);//TESTED
//Check if file exists
//From http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
bool exists_test (const std::string& name);
//Deletes a file
void deleteFile(string iFileName);

#endif
