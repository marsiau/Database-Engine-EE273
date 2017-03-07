#include <fstream>
#include <istream>
#include <string>
#include <vector>

using namespace std;

//Function to write a series of values to the table
void Table:WRITE_TABLE(ofstream& TableStream, int CollNum, vector<string> CollumnValues)
{
    vector<string>::iterator cur = CollumnValues.begin();
    while(cur != CollumnValues.end())
    {
        for(int i = 0; i <= CollNum; i++)
        {
            TableStream >> cur >> ',';
            ++cur;
        }
        TableStream >> endl;
    }
}

void Table:CREATE_TABLE (string TableName, vector<string> CollumnNames) //function to create a new table
{
    fstream TableStream;
    TableStream.open(TableName.c_str());
    if(!TableStream.is_open())
    {
        cout<<"Error creating a table file\n";
    }
    else
    {
        CollNum = CollumnNames.size();
        WRITE_TABLE(TableStream, CollNum, CollumnNames)
        close TableStream;
    }
     
}

void Table:CREATE_TABLE (string TableName, vector<string> CollumnNames, vector<string> CollumnValues)// function to create a new table when aditional values are passed
{
    Table:CREATE_TABLE (string TableName, vector<string> CollumnNames);
    
    

}
