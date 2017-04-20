# include <regex>
#include <iostream>
#include <string>

using namespace std;

int main()
{
  bool loop = true;
  while(loop)
  {
    string UsrIn;
    //http://stackoverflow.com/questions/9083405/how-do-i-parse-user-input-from-the-standard-input-stream
    //http://www.informit.com/articles/article.aspx?p=2079020
    if(getline(cin, UsrIn))
    {
      //regex rQuit("QUIT");//if(regex_match(UsrIn, rQuit))
      if(regex_match(UsrIn,regex("QUIT")))
      {
        loop = false;
      }
      else
      {
        cout<<"\nINPUT STREAM ERROR\n";
      }
    }
    //If input is invalid, do nothing
  }
}
