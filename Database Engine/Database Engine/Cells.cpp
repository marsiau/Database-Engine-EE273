#include "Cells.hpp"

template <class T> T Calc<T>::operator==(const Cells<T>& c)
{
	if (this->contents == c.contents)
	{
		return true;
	}
	else return false;
}

template <class T> T Calc<T>::operator!=(const Cells<T>& c)
{
	if (this->contents != c.contents)
	{
		return true;
	}
	else return false;
}
template <class T> T Calc<T>::operator<(const Cells<T>& c)
{
	if (this->contents < c.contents)
	{
		return true;
	}
	else return false;
}
template <class T> T Calc<T>::operator>(const Cells<T>& c)
{
	if (this->contents > c.contents)
	{
		return true;
	}
	else return false;
}
template <class T> T Calc<T>::operator>=(const Cells<T>& c)
{
	if (this->contents >= c.contents)
	{
		return true;
	}
	else return false;
}
template <class T> T Calc<T>::operator<=(const Cells<T>& c)
{
	if (this->contents <= c.contents)
	{
		return true;
	}
	else return false;
}


