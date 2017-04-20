#include <fstream>
#include <iostream>
#include <string>
//#include <list>
#include <vector>



using namespace std;
typedef string Cell;
//using Cell = string;

vector<Cell> ReadRow(ifstream &InputStream)
{
  vector<Cell> Row;
  string TEMP;
  while(InputStream.peek() != '\n')
  {
    getline(InputStream, TEMP, ',');
    Row.push_back(TEMP);
  }
  InputStream.ignore(1);//To skip the \n
  return Row;
}

int main()
{
  vector<Cell> foo;
  vector<Cell> foo2;

  ifstream TableStream;
  TableStream.open("in.txt");
    if(!TableStream.is_open())
  {
      cout<<"Error creating a table file\n";
  }
  else
  {
    foo = ReadRow(TableStream);
    for(vector<Cell>:: iterator cur = foo.begin(); cur != foo.end(); ++cur )
    {
      cout<<*cur<<endl;
    }
    cout<<"pisau\n";

    foo2 = ReadRow(TableStream);
    for(vector<Cell>:: iterator cur = foo2.begin(); cur != foo2.end(); ++cur )
    {
      cout<<*cur<<endl;
    }
    TableStream.close();
  }
    return 0;
}
