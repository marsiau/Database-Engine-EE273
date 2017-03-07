#include <fstream>
#include <istream>
#include <string>
#include <vector>

using namespace std;
//List of vectors???

//Function to write a series of values to the table
void Table:WRITE_TABLE(ofstream& TableStream, int CollNum, vector<string> CollumnValues)
{
    vector<string>::iterator cur = CollumnValues.begin();
    while(cur != CollumnValues.end())
    {
        //what if list of vectors??
        for(int i = 0; i <= CollNum; i++)
        {
            TableStream >> cur >> ',';
            ++cur;
        }
        TableStream >> endl;
    }
}

//Function to create a new table
void Table:CREATE_TABLE (string TableName, vector<string> CollumnNames)
{
    fstream TableStream;
    //TODO create a function to open table
    TableStream.open(TableName.c_str(), ios::out, ios::app); //Opened for output operations at the end of file
    if(!TableStream.is_open())
    {
        cout<<"Error creating a table file\n";
    }
    else
    {
        CollNum = CollumnNames.size();
        WRITE_TABLE(TableStream, CollNum, CollumnNames);
        TableStream.close();
    }

}

////Function to create a new table and include values
void Table:CREATE_TABLE (string TableName, vector<string> CollumnNames, vector<string> CollumnValues)// function to create a new table when aditional values are passed
{
    Table:CREATE_TABLE (string TableName, vector<string> CollumnNames);
    fstream TableStream;
    TableStream.open(TableName.c_str(), ios::out, ios::app); //Opened for output operations at the end of file
    if(!TableStream.is_open())
    {
        cout<<"Error creating a table file\n";
    }
    else
    {
        WRITE_TABLE(TableStream, CollNum, CollumnValues);
        TableStream.close();
    }
}

//Function to delete a table
void Table:DROP_TABLE(string TableName)
{
  remove(TableName.c_str());
}
