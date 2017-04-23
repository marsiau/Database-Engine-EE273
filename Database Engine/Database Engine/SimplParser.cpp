# include <regex>
#include <iostream>
#include <string>
#include <vector>
#include "Auxilary.hpp"
#include "Table.hpp"
#include "Database.hpp"
/*
Commands needed

SELECT X 
SELECT X WHERE X
CREATE X
UPDATE X
*/

using namespace std;


// Convert a string to a vector of words.
// Used "http://stackoverflow.com/questions/8425214/splitting-string-into-a-vectorstring-of-words" as template for function.
vector<string> stringToWordsVector(const string &s)
{
	// Create a string vector to return.
	vector<string> ret;
	typedef string::size_type string_size;
	string_size i = 0;

	// invariant: we have processed characters [original value of i, i) 
  while (i != s.size()) 
  {
		// while there is a space, ignore character.
		while (i != s.size() && isspace(s[i]) || s[i] == ',')
		{
			++i;
		}
		// find how many charactars there are in the next word.
		string_size j = i;
		
		// invariant: none of the characters in range [original j, current j)is a space
	  while (((j != s.size()) && (!isspace(s[j]))) && (s[j] != ','))
		{
			j++;
		}

		// push the character indexes into the vector.
		if (i != j) 
		{
			// copy from s starting at i and taking j - i chars
			ret.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return ret;
}

// Parse Command.
void parseCommand(vector<string> &v)
{
  vector<string> colnames;
  vector<string> coltypes;
  vector<string> data;
  string tableName;
  
  typedef string::size_type string_size;
	string_size i = 0;

  while ( i != v.size())
  {
    if ( v[i] == "(")
    {
    	i++;
  		string_size j = i;
  	
  		while (v[j] != ")")
  		{
  		  if (v[0] == "CREATE")
  		  {
  		    colnames.push_back(v[j]);
  		    coltypes.push_back(v[j+1]);
  			  j= j + 2;
  		  }
  		  if (v[0] == "INSERT")
  		  {
  		    data.push_back(v[j]);
  		  }
  		  
  		}  
    }
    ++i;
  }
  
  if(v[0] == "DROP")
  {
    if(v[1] == "TABLE")
    {
      // Database db("DB1");
      // tableName = v[2];
      // db.DROP_TABLE(tableName);
    }
    else if(v[1] == "DATABASE")
    {
      cout << "COMMAND DROP DATABASE USED" << endl;
    }
  }
  else if(v[0] == "CREATE")
  {
    if(v[1] == "TABLE")
    {
      Database db("NewDB");
      tableName = v[2];
      db.CREATE_TABLE(tableName, colnames, coltypes);
    }
    else if(v[1] == "DATABASE")
    {
      cout << "COMMAND CREATE DATABASE USED" << endl;
    }
     
  }
  else if(v[0] == "UPDATE")
  {
    cout << "COMMAND UPDATE USED" << endl;
  }
  else if(v[0] == "INSERT")
  {
    tableName = v[2];
    INSERT(data);
    
  }
}




// Main 
int main()
{
  bool quit = 0;
  while (!quit)
  {
    string cmd;
    cout << "Enter Command" << endl;
  
    getline(cin, cmd);
  
    vector<string> words = stringToWordsVector(cmd);

    printStringVector(words);
  
    parseCommand(words);
  }
}


    
  
  
  
  
  
