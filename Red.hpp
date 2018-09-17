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
#include "Utils.hpp"

#define MSG_BAD_RANGE "NO DATA"
#define MSG_BAD_QUERY "BAD QUERY"

#define INITIAL_LENGTH_VECTOR 25

class Red {

private:

	string * _Ids;
	ArrayDouble ** _Sensores;
	Package  * _Pack;

	int _Amaunt;    // Cantidad de sensores almacenados

	void CreateVectors(int);

public:

	Red();
	Red(int);
	Red(cons Red &);
	int GetLeng(void);
	void SetSensors(string * &, int);
	void PrintPackage(std::ostream &);	//Impresion de los datos acumulados en el paquetem se imprime en el stream que se le pasa y lo hace con formato
	void MakeSmallQuery(string, int, int);	//Le paso un string con la ID del sensor y los rangos para hacer el query
	void MakeBigQuery(int, int);			//Le paso los rangos para hacer la query ya que lo hace sobre todos los sensores
	void AppendRow(double *);
	~Red();
};

#endif





