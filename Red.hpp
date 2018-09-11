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

	string * _Ids;
	ArrayDouble * _Sensores;
	Package  * _Pack;
	int _Amaunte;

	void CreateVectors(int);

public:

	Red();
	Red(int);
	Red(cons Red &);
	int GetLeng(void);
	void PrintPackage(std::ostream &);	//Impresion de los datos acumulados en el paquetem se imprime en el stream que se le pasa y lo hace con formato
	void MakeQuery(string, int, int);	//Le paso un string con la ID del sensor y los rangos para hacer el query
	void MakeBigQuery(int, int);			//Le paso los rangos para hacer la query ya que lo hace sobre todos los sensores
	ArrayDouble& operator[](int);
	ArrayDouble operator[](int) const;
	friend std::istream& operator>>(std::istream &, Red &);		//Sobrecargo del operador >> para que lea directamente desde un archivo 
	~Red();
};

#endif





