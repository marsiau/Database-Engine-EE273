#ifndef CELLS_HPP_
#define CELLS_HPP_

//TODO use cells_smth for virtal? class, then create different cell classes and stick them into union

/*
AbsCell - abstract class for cell
IntCell - class for cell containing integer
StrCell - class for cell containing string
...
Cell - union containing all cells


AbsCell methods
  overide comparison ==,!=,<,>,<=,>=
  overide maths functions +,-,*,/
  copying?

*/

#include <string>
#include <list>
#include <vector>

using namespace std;

class AbsCell
{
private:

public:
  AbsCell();
  ~AbsCell();


};
#endif