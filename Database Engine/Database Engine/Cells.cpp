#include "Cells.hpp"

// Overriding '==' Operator
template <class T> T Calc<T>::operator==(const Cells<T>& c)
{
	if (this->contents == c.contents)
	{
		return true;
	}
	else return false;
}

// Overriding '!=' Operator
template <class T> T Calc<T>::operator!=(const Cells<T>& c)
{
	if (this->contents != c.contents)
	{
		return true;
	}
	else return false;
}

// Overriding '<' Operator
template <class T> T Calc<T>::operator<(const Cells<T>& c)
{
	if (this->contents < c.contents)
	{
		return true;
	}
	else return false;
}

// Overriding '>' Operator
template <class T> T Calc<T>::operator>(const Cells<T>& c)
{
	if (this->contents > c.contents)
	{
		return true;
	}
	else return false;
}

// Overriding >= Operator
template <class T> T Calc<T>::operator>=(const Cells<T>& c)
{
	if (this->contents >= c.contents)
	{
		return true;
	}
	else return false;
}

// Overriding <= Operator
template <class T> T Calc<T>::operator<=(const Cells<T>& c)
{
	if (this->contents <= c.contents)
	{
		return true;
	}
	else return false;
}


