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
	_Amount = 0;
}

Red::Red(int Number){
	_Ids = new string[Number];
	_Sensors = new (ArrayDouble*)[Number];
	for (int i = 0; i < Number; ++i){
		_Sensors[i] = new ArrayDouble(INITIAL_LENGTH_VECTOR);
	}
	_Pack = new Package;
	_Amount = Number;
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

	_Pack = new Package(*(r._Pack))	;
}

int GetLeng(void){
	return _Amount;
}

void SetSensors(string * Names, int Number){	// Number indica la cantidad de strings que tiene el puntero Names
	string * aux;

	aux = new string[Number];		// Se crea un vector independiente para que el objeto red tenga su propio vector
	for (int i = 0; i < Number; ++i){
		aux[i] = Names[i];
	}

	if(_Ids != NULL){			// Si el objeto ya tenia Ids asignados se los borra
		delete [] _Ids;
	}
	_Ids = aux;

	if(_Sensors != NULL){		// Si ya se tenia una tabla de valores se la borra
		for (int i = 0; i < _Amount; ++i){
			delete[] _Sensors[i];
		}
		delete[] _Sensors;
	}

	_Ids = new (ArrayDouble*)[Number];		// Se crean los arrays vacios
	/** no deberian ser punteros a strings? **/
	for (int i = 0; i < Number; ++i){
		_Sensors[i] = new ArrayDouble(INITIAL_LENGTH_VECTOR);
	}

	_Amount = Number; // Se le asigna la nueva cantidad de sesores
}

void Red::PrintPackage(std::ostream & os){
	if(_Pack.GetQueryStaus()){
		os << MSG_BAD_QUERY << std::endl;
	}else if(_Pack.GetRangeStaus()){
		os << MSG_BAD_RANGE << std::endl;
	}else if(_Pack.GetIdStatus())
		os << 										//santi completa aca
	else{
		os << _Pack.GetAverage() << ',' << _Pack.GetMin() << ',' 	\\
			<< _Pack.GetMax() << ',' << _Pack.GetQuantity() << std::endl;
	}
	(*_Pack).Clear();
}

void Red::MakeSmallQuery(string ID, int Start, int End){
	size_t i,j;
	int FinalMark;
	Package aux;

	aux.clear();

	_BadId = true;

	for (i = 0; i < _Amount; i++) {
		if (!_Ids[i].compare(ID)) {
			_BadId = false;
			break;
		}
	}
	if (_BadId == true)
		return;


	if(Start > _Sensors[i].UsedSize()){
		_Pack.SetRangeStatus(true);
	}

	if(End > _Sensors[i].UsedSize()){
		FinalMark = _Sensors[i].UsedSize();
	}else{
		FinalMark = End;
	}
	aux.SetQuantity(FinalMark - Start);

	for (j = Start; j < FinalMark; j++){
		aux.SetAverage(aux.GetAverage() + _Sensors[i][j] / aux.GetQuantity());
		if(_Sensors[i][j] < aux.GetMin()){
			aux.SetMin(_Sensors[i][j]);
		}
		if(_Sensors[i][j] > aux.GetMax()){
			aux.SetMax(_Sensors[i][j]);
		}
	}

	_Pack = aux;
}

void Red::MakeBigQuery(int Start, int End){
	int FinalMark;	// Indica donde termina la iteracion
	Package aux;

	aux.clear();

	if(Start > _Sensors[0].UsedSize()){
		_Pack.SetRangeStatus(true);
	}

	if(End > _Sensors[0].UsedSize()){
		FinalMark = _Sensors[0].UsedSize();
	}else{
		FinalMark = End;
	}

	aux.SetQuantity(_Amount * (FinalMark - Start));

	for (int i = 0; i < _Amount; ++i){
		for (int j = Start; j < FinalMark; ++j){
			aux.SetAverage(aux.GetAverage() + _Sensors[i][j] / aux.GetQuantity());
			if(_Sensors[i][j] < aux.GetMin()){
				aux.SetMin(_Sensors[i][j]);
			}
			if(_Sensors[i][j] > aux.GetMax()){
				aux.SetMax(_Sensors[i][j]);
			}
		}
	}

	_Pack = aux;
}

void Red::AppendRow(double * Data){
	for (int i = 0; i < _Amount; ++i){
		_Sensors[i].Append(Data[i]);
	}
}

Red::~Red(){
	delete[] _Ids;
	for (int i = 0; i < _Amount; ++i){
		delete[] _Sensors[i];
	}
	delete[] _Sensors;
	delete _Pack;
}
















