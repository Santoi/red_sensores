/*
	Archivo: ArrayDouble.cpp
*/

#include <iostream>
#include <cstdlib>

#include "ArrayDouble.hpp"

#define INIT_LENG 10
#define ERROR_INVALID_ARGUMENT "ArrayDouble constructor: negative arguments not allowed."
#define ERROR_ARRAY_INDEX "ArrayDouble operator []: index not allowed."

ArrayDouble::ArrayDouble(){
	_Leng = INIT_LENG;
	_Used = 0;
	_Array = new double[INIT_LENG];
	for (int i = 0; i < _Leng; ++i){
		_Array[i] = 0;
	}
}

ArrayDouble::ArrayDouble(int N){
	//Si el argumento es invalido es invalido sale del programa
	if(N <= 0){
		std::cerr << ERROR_INVALID_ARGUMENT << std::endl;
		exit(EXIT_FAILURE);
	}

	_Leng = N;
	_Used = 0;
	_Array = new double[_Leng];
	for (int i = 0; i < _Leng; ++i){
		_Array[i] = 0;
	}
}

ArrayDouble::ArrayDouble(const ArrayDouble & Original){

	_Leng = Original._Leng;
	_Used = Original._Used;
	_Array = new double[_Leng];

	for (int i = 0; i < _Used; ++i){
		_Array[i] = Original._Array[i];
	}
}

int ArrayDouble::UsedSize() const{
	return _Used;
}

double& ArrayDouble::operator[](int pos){
	//Si la posicion ingresada es invalida, sale del programa
	if(pos < 0 && pos >= _Used){
		std::cerr << ERROR_ARRAY_INDEX << std::endl;
		exit(EXIT_FAILURE);
	}

	return _Array[pos];
}

double& ArrayDouble::operator[](int pos) const{
	//Si la posicion ingresada es invalida, sale del programa
	if(pos < 0 || pos >= _Used){
		std::cerr << ERROR_ARRAY_INDEX << std::endl;
		exit(EXIT_FAILURE);
	}

	return _Array[pos];
}

void ArrayDouble::Append(const double d){
	int NewSize = _Leng * 2;
	double * aux;

	//Si el Array no esta lleno, agrego el nuevo numero
	if(_Used < _Leng){
		_Array[_Used] = d;
		_Used ++;
	}else{	// Si el Array esta lleno, hay qe alargarlo antes de incertar
			//el numero nuevo

		//Primero se copia todo a un Array auxiliar
		aux = new double[_Leng];
		for(int i = 0; i < _Used; i++){
			aux[i] = _Array[i];
		}

		//Destruye y crea un nuevo Array con el doble de largo
		delete [] _Array;
		_Array = new double[NewSize];
		_Leng = NewSize;

		//Se rellena el nuevo Array con los datos almacenados en el
		// arreglo auxiliar
		for(int i = 0; i < _Used; i++){
			_Array[i] = aux[i];
		}

		//Se destruye el arreglo auxiliar
		delete [] aux;

		// Se agrega el nuevo numero
		_Array[_Used] = d;
		_Used ++;
   	}
}

ArrayDouble::~ArrayDouble(){
	delete [] _Array;
}