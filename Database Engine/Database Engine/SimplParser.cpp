# include <regex>
#include <iostream>
#include <string>
#include <vector>
/*
Commands needed

SELECT X 
SELECT X WHERE X
CREATE X
UPDATE X
*/

using namespace std;

vector<string> stringToWordsVector(const string& s)
{
   vector<string> ret;
   typedef string::size_type string_size;
   string_size i = 0;

   // invariant: we have processed characters [original value of i, i) 
   while (i != s.size()) {
      // ignore leading blanks
      // invariant: characters in range [original i, current i) are all spaces
      while (i != s.size() && isspace(s[i]))
         ++i;

      // find end of next word
      string_size j = i;
      // invariant: none of the characters in range [original j, current j)is a space
      while (j != s.size() && !isspace(s[j]))
         j++;

      // if we found some nonwhitespace characters 
      if (i != j) {
         // copy from s starting at i and taking j - i chars
         ret.push_back(s.substr(i, j - i));
         i = j;
      }
   }
   return ret;
}

void printStringVector(vector<string> &v)
{
  vector<string>::iterator it;
  for (it=v.begin(); it<v.end(); it++)
  {
    cout << ' ' << *it;
    cout << '\n';
  }
}

int main()
{
  string cmd;
  cout << "Enter Command" << endl;
  
  getline(cin, cmd);
  vector<string> words = stringToWordsVector(cmd);
  printStringVector(words);

  if(words[0] == "DROP")
  {
    if(words[1] == "TABLE")
    {
      cout << "COMMAND DROP TABLE USED" << endl;
    }
    else if(words[1] == "DATABASE")
    {
      cout << "COMMAND DROP DATABASE USED" << endl;
    }
  }
  else if(words[0] == "CREATE")
  {
    if(words[1] == "TABLE")
    {
      cout << "COMMAND CREATE TABLE USED" << endl;
    }
    else if(words[1] == "DATABASE")
    {
      cout << "COMMAND CREATE DATABASE USED" << endl;
    }
     
  }
  else if(words[0] == "UPDATE")
  {
     cout << "COMMAND UPDATE USED" << endl;
  }

  
  
}


    
  
  
  
  
  
