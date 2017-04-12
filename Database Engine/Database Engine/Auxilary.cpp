#include "Auxilary.hpp"
#include <string>
#include <fstream>

using namespace std;

//Checks if filename has ".txt" and changes it dpending on chng
string chkType(string InStr, bool chng)//TESTED
{
  int InSize = InStr.size();
  string strEnd = {InStr[InSize-4], InStr[InSize-3], InStr[InSize-2], InStr[InSize-1]};
  if(strEnd == ".txt")
  {
    if(chng)
    {return InStr;}//Don't change
    else
    {return InStr.erase(InStr.size() - 4);}//Remove ".txt"
  }
  else
  {
    if(chng)
    {return InStr += ".txt";}//Add ".txt"
    else
    {return InStr;}//Don't change
  }
}
//Check if file exists
//From http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
bool exists_test (const std::string& name)
{
    ifstream f(name.c_str());
    return f.good();
}
//Deletes a file
void deleteFile(string iFileName)
{
  //From http://www.cplusplus.com/reference/cstdio/remove/
  string FileName = chkType(iFileName, 1);//Add the file type
  if( remove(FileName.c_str()) != 0 )
    perror( "Error deleting file" );
    else
    puts( "File successfully deleted" );
}
