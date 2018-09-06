/*
	Archivo: Red.cpp
*/

#ifndef _RED_HPP_INCLUDED_
#define _RED_HPP_INCLUDED_

#include <iostream>
#include <cstdlib>
#include <string>

#include "ArrayDouble.hpp"
#include "Package.hpp"

class Red {

private:

	string * ids;
	ArrayDouble * array;
	Package pack;

public:

	Red();
	~Red();
	PrintPackage(std::ostream &);	//impresion de los datos con formato
	friend Red operator>>(std::istream &, const Red &);		//sobrecarga para la lectura de los datos
	MakeQuery(string, int, int);	//le paso el query y el rango

}

#endif





