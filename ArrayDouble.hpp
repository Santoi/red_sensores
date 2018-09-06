/*
Archivo: ArrayDouble.hpp
*/

#ifndef _ARRAYDOUBLE_HPP_INLCUDED_
#define _ARRAYDOUBLE_HPP_INLCUDED_

#include <iostream>
#include <cstdlib>

class ArrayDouble{

private:

	int _Leng;
	int _Used;
	double * _Array;

	ArrayDouble();

public:

	ArrayDouble(int);
	ArrayDouble(const ArrayDouble &);
	int UsedSize() const;
	double& operator[](int pos);
	double& operator[](int pos) const;
	void Append(const double);
	~ArrayDouble();
};

#endif
