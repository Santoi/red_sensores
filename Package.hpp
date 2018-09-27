/*
	Archivo: Package.hpp
*/

#ifndef _PACKAGE_HPP_INCLUDED
#define _PACKAGE_HPP_INCLUDED 

#include <iostream>
#include <cstdlib>

class Package{

private:
	double _Average;
	double _Min;
	double _Max;
	int _Quantity;
	bool _BadRange; // Si esta en TRUE significa que hay un problema con el rango de la consulta
	bool _BadQuery; // Si esta en TRUE significa que hay un problema con la escritura de la query
	bool _BadId; 	// Se esta en TRUE significa que hay un problema con el Id ingersado, no se coresponde con ninguno de los existentes
public:
	Package();
	Package(const Package &);
	// Se definen los Geters de la clase
	double GetAverage(void);
	double GetMin(void);
	double GetMax(void);
	int GetQuantity(void);
	bool GetRangeStatus(void);
	bool GetQueryStatus(void);
	bool GetIdStatus(void);
	// Se definen los Seters de la clase
	void SetAverage(const double);
	void SetMin(double);
	void SetMax(double);
	void SetQuantity(int);
	void SetRangeStatus(bool);
	void SetQueryStatus(bool);
	void SetIdStatus(bool);
	void Clear();	// Esta funcion setea todos los numeros en cero y los bools en false
	Package& operator=(const Package &);
	~Package();
};

#endif





