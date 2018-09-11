/*
	Archivo: Red.cpp
*/

#include <iostream>
#include <cstdlib>
#include <string>

#include "ArrayDouble.hpp"
#include "Package.hpp"
#include "Red.hpp"

Red::Red(){
	_Ids = NULL;
	_Sensors = NULL;
	_Pack = new Package;
	_Amaunt = 0;
}

Red::Red(int Num){
	_Ids = new string[Num];
	_Sensors = new ArrayDouble[Num];
	_Pack = new Package;
	_Amaunte = 0;
}

Red::Red(const Red & r){
	string * saux;
	ArrayDouble * aux;
	int SenSize;

	SenSize = r.GetLeng();

	saux = new string[SenSize];
	aux = new ArrayDouble[GetLeng];


}

int GetLeng(void){
	return _Amaunte;
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
	delete[] _Sensors;
	delete _Pack;
}
















