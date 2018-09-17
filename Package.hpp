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

public:
	Package();
	Package(const Package &);
	double GetAverage(void);
	double GetMin(void);
	double GetMax(void);
	int GetQuantity(void);
	bool GetRangeStatus(void);
	bool GetQueryStatus(void);
	void SetAverage(const double);
	void SetMin(double);
	void SetMax(double);
	void SetQuantity(int);
	void SetRangeStatus(bool);
	void SetQueryStatus(bool);
	void Clear();
	Package& operator=(const Package &);
	~Package();
};

#endif





