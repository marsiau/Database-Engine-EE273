#if 0
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

// Template Cell class, can accept any data type.
template <class T> 
class Cell
{
public:
  
  // // Overriding comparison functions.
	// Cell<T>& operator==(const Cell<T>& classObj);
  // Cell<T>& operator!=(const Cell<T>& classObj);
  // Cell<T>& operator<(const Cell<T>& classObj);
  // Cell<T>& operator>(const Cell<T>& classObj);
  // Cell<T>& operator<=(const Cell<T>& classObj);
  // Cell<T>& operator>=(const Cell<T>& classObj);

private:
  // Contents variable holds the data within the cell.
	T contents;

};

#endif
