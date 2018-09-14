/*
	Archivo: Red.cpp
*/

#include <iostream>
#include <cstdlib>
#include <string>

#include "ArrayDouble.hpp"
#include "Package.hpp"
#include "Utils.hpp"
#include "Red.hpp"



Red::Red(){
	_Ids = NULL;
	_Sensors = NULL;
	_Pack = new Package;
	_Amaunt = 0;
}

Red::Red(int Num){
	_Ids = new string[Num];
	_Sensors = new (ArrayDouble*)[Num];
	for (int i = 0; i < Num; ++i){
		_Sensors[i] = new ArrayDouble(INITIAL_LENGTH_VECTOR);
	}
	_Pack = new Package;
	_Amaunt = Num;
}

Red::Red(const Red & r){
	int SensorSize;

	SensorSize = r.GetLeng();

	_Ids = new string[SensorSize];
	for (int i = 0; i < SensorSize; ++i){
		_Ids[i] = r._Ids[i];
	}

	_Sensors = new (ArrayDouble*)[SensorSize];
	for (int i = 0; i < SensorSize; ++i){
		_Sensors[i] = new ArrayDouble(*(r._Sensors[i]));
	}

	_Pack = new Package(*(r._Pack));
}

int GetLeng(void){
	return _Amaunt;
}

void Red::PrintPackage(std::ostream & os){


}

void Red::MakeQuery(string ID, int Start, int End){


}

void Red::MakeBigQuery(int Start, int End){


}

ArrayDouble& Red::operator[](int Pos){


}

ArrayDouble& Red::operator[](int Pos) const{


}

std::istream& Red::operator>>(std::istream& is, Red & r){


}

Red::~Red(){
	delete[] _Ids;
	for (int i = 0; i < _Amaunt; ++i){
		delete[] _Sensors[i];
	}
	delete[] _Sensors;
	delete _Pack;
}
















