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

	ArrayDouble();		// Este metodo es privao debido a que no se quiere que se cree un Array con un nunmero de elementos no definido

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