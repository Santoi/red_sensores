/*
	Archivo: Package.cpp
*/

#include <iostream>
#include <cstdlib>

#include "Package.hpp"

Package::Package(){
	_Average = 0;
	_Min = 0;
	_Max = 0;
	_Quantity = 0;
	_BadRange = FALSE;
}

Package::Package(const Package & p){
	_Average = p._Average;
	_Min = p._Min;
	_Max = p._Max;
	_Quantity = p._Quantity;
	_BadRange = p._BadRange;
}

double Package::GetAverage(void){
	return _Average;
}

double Package::GetMin(void){
	return _Min;
}

double Package::GetMax(void){
	return _Max;
}

int Package::GetQuantity(void){
	return _Quantity;
}

bool Package::GetRangeStatus(void){
	return _BadRange;
}

void Package::SetAverage(double d){
	_Average = d;
}

void Package::SetMin(double d){
	_Min = d;
}

void Package::SetMax(double d){
	_Max = d;
}

void Package::SetQuantity(int i){
	_Quantity = i;
}

void Package::SetRangeStatus(bool b){
	_BadRange = b;
}

Package & Package::operator=(const Package & p){

	_Average = p._Average;
	_Min = p._Min;
	_Max = p._Max;
	_Quantity = p._Quantity;
	_BadRange = p._BadRange;
	
	return *this;	
}

Package::~Package(){

}
