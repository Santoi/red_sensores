/*
	Archivo: Utils.cpp
*/

#include <iostream>
#include <cstdlib>
#include <string>

#include "Utils.hpp"

void ParseLine(string * & Destino, istream & is, int & ContadorComas = 0){

	string Entrada;		// String sobre la que se va a guardar la linea leida
	int SubString = 0;	// Indica la posicion donde comenza la siguiente palabra a guardar
	int numero;			
	int j = 0;			
	int i = 0;

	//Se inizia leyendo la linea del flujo de entrada
	getline(is, Entrada);

	//Se cuentan la cantidad de palabras que hay en la linea contando la cantidad de comas
	for ( i = 0; i < (Entrada.length() - 1); ++i){
		if(Entrada[i] == ','){
			ContadorComas++;
		}	
	}
	ContadorComas++;

	// Se crea el Arreglo de Strings en funcion de la cantidad de palabras que hay en la linea
	Destino = new string[ContadorComas];

	// Se recorre nuevamente el String para localizar las comas y se copia en un string diferente lo que hay entre ellas
	// Se lo realiza en dos etapas. La primera es con todos las palabras que finalizan en coma y la segunda es con la palabra final
	for (i = 0; i < numero; ++i){
		if(Entrada[i] == ','){
			Destino[j].assign(Entrada, SubString, i - SubString);
			SubString = i + 1;
			j++;
		}	
	}
	Destino[j].assign(Entrada, SubString, i - SubString + 1);	// Se le suma uno porque el elemento final no es una coma

}

void ParseFirstLine(istream & is, Red & Object){
	string * Parsed;
	string Read, aux;
	stringstream StringRead;
	int Comas, i = 0;
	char c;
	bool eol;

	if(!(getline(is, Read))){
		//return Error de archivo corrupto cuando este los errores
	}

	for ( i = 0; i < (Read.length() - 1); ++i){
		if(Read[i] == ','){
			Comas++;
		}	
	}
	Comas++;
	Parsed = new str
	ing[Comas];

	i = 0;
	stringstream StringRead(Read);
	while((StringRead >> aux) && (!StringRead.eof())){
		if(aux[aux.length() - 1] == ',')
			StringRead.putback(',');
		Parsed[i] = aux;
		i++;
		if(!((StringRead >> c) && (c == ',')) || i == Comas){
			break;
		}
	}

	Object.SetSensors(Parsed, Comas);
	delete [] Parsed;
}

void ParsedData(istream & is, Red & Object){
	string Read;
	stringstream StringRead;
	int i;
	char c;
	double Number;
	double * Data;
	bool eol;

	Data = new double[Object.GetLeng()];

	while(getline(is, Read)){
		stringstream StringRead(Read);
		i = 0;
		while((Read >> Number) && (!Read.eof())){
			Data[i] = Number;
			if((i == Object.GetLeng()) || ((is >> c) && (c != ','))){
				// sale con un error de archivo corrupto
			} 
			i++;
		}
		Object.Append(Data);
	}	

	delete [] Data;
}

void ManageQuerys(istream & is, ostream & os, Red & Object){
	string Read, Sensor;
	stringstream StringRead;
	int i, Start, End;
	char c;
	double Number;


	while(getline(is, Read)){
		stringstream StringRead(Read);
		if(!(StringRead >> Sensor)){
			// Sale del programa
		}
		if(aux[aux.length() - 1] == ',')
			StringRead.putback(',');
/*		Hay qu eponer un codigo que se desaga de la coma del string	
*/

		if(!(StringRead >> c) || (c == ',')){
			// mala linea
		}

		if(!(StringRead >> Start) ||
				!(StringRead >> c) || 
				!(c == ',') || 
				!(StringRead >> End)){
			//mala linea
		}
		if(){ // si esta vacia el string llama a big query
		}else{
			Object.MakeSmallQuery(Sensor, Start, End);
		}

		Object.PrintPackage(os);
	}

}





