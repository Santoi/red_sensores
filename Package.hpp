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
	bool _BadRange; //Si esta en TRUE significa que hay un problema con el rango de la consulta

public:
	Package();
	Package(const Package &);
	double GetAverage(void);
	double GetMin(void);
	double GetMax(void);
	int GetQuantity(void);
	bool GetRangeStatus(void);
	void SetAverage(const double);
	void SetMin(double);
	void SetMax(double);
	void SetQuantity(int);
	void SetRangeStatus(bool);
	Package& operator=(const Package &);
	~Package();
};

#endif





