/*
	Archivo: Utils.cpp
*/

#include <iostream>
#include <cstdlib>
#include <string>

#include "Utils.hpp"

// Se llama para parcear la primera linea del archivo que contiene los datos. La funcion procesa los Ids de cada columna y
// setea el objeto red con los ids y las columnas
s

status_t ParsedData(istream & is, Red & Object){
	string Read;
	stringstream StringRead;
	int i;
	char ch;
	double Number;
	double * Data;
	bool eol;

	Data = new double[Object.GetLeng()];

	while(getline(is, Read)){
		stringstream StringRead(Read);
		i = 0;
		while((Read >> Number) && (!Read.eof())){
			Data[i] = Number;
			ch = is.peek();
			if((ch == ',') && (i < Object.GetLeng())){
				StringRead.ignore();
			}else if((ch != ',') || ((ch == ',') && (i < Object.GetLeng()))){
				return ST_ERROR_FILE_CORRUPTED;
			}
			i++;
		}
		Object.Append(Data);
	}

	delete [] Data;

	return ST_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
										//Tercera version //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

status_t ParseFirstLine(istream & is, Red & Object){  // Este supuestamente esta ok con una duda
	string * Parsed;
	string Read, aux;
	stringstream StringRead;
	int Comas = 0, i = 0;
	char ch;
	bool eol;

	// Lee la primera linea del archivo
	if(!(getline(is, Read))){
		return ST_ERROR_FILE_CORRUPTED;
	}

	// Recorre la linea para establecer la cantidad de strings que hace falta
	for ( i = 0; i < (Read.length() - 1); ++i){
		if(Read[i] == ','){
			Comas++;
		}
	}
	Comas++; // Se suma uno porque hay una palabra mas que comas
	Parsed = new string[Comas];

	// Se pasa el string a un streamstring para utilizar el operador >> para recibir los strings

	stringstream StringRead(Read);

	for ( i = 0; i < Comas; ++i){
		Parsed[i].clear();
		while((StringRead >> ch) && (ch != ',' )){
			Parsed[i] += ch;
		}
		ch = StringRead.peek(); ////////////////// que pasas cuando hace peek y es el final del string
		if(ch == ','){
			StringRead.ignore();
		}
	}
/*
	for(i = 0; i < Comas; ++i){
	Parsed[i].clear();
		while((StringRead >> ch) && (ch != ',' )){
			Parsed[i] += ch;
		}
		if(ch == ','){
			StringRead.putback(',');
		}
		if((StringRead >> ch) && (ch == ',' )){
			StringRead.ignore();
		}else if(ch != ','){
			return ST_ERROR_FILE_CORRUPTED;
		}
	}
*/

	Object.SetSensors(Parsed, Comas);
	delete [] Parsed;

	return ST_OK;
}

status_t ManageQuerys(istream & is, ostream & os, Red & Object){
	string Read, Sensor;
	stringstream StringRead;
	int i, Start, End;
	char ch;
	bool BigQuery;

// Se comienza la iteracion copiando la primera linea del programa, si no hay linea no hace nada
	while(getline(is, Read)){
		BigQuery = false;
		stringstream StringRead(Read);

		if(!(StringRead >> ch))
			continue;

		////////////////////////////////////////Se cambio como se procesa el string inicial
		if(ch == ','){
			BigQuery = true;
			StringRead.putback(',');
		}else{
			Sensor.clear();
			Sensor += ch;
		}
		while((ch = StringRead.peek()) && (ch != ',')){
			Sensor += ch;
			StringRead.ignore();
		}

		// Se procesa las comas y los numero enteros
		ch = is.peek();
		if(ch != ','){
			Object.SetQueryStatus(true);
			Object.PrintPackage();
			continue;
		}else{
			is.ignore();
		}
		if(!(is >> Start)){
			Object.SetQueryStatus(true);
			Object.PrintPackage();
			continue;
		}
		ch = is.peek();
		if(ch != ','){
			Object.SetQueryStatus(true);
			Object.PrintPackage();
			continue;
		}else{
			is.ignore();
		}
		if(!(is >> End)){
			Object.SetQueryStatus(true);
			Object.PrintPackage();
			continue;
		}

		// Se hacen las Querys
		if(BigQuery){
			Object.MakeBigQuery(Start, End);
		}else{
			Object.MakeSmallQuery(Sensor, Start,End);
		}

		// Se impreime en el archivo el resultado
		Object.PrintPackage(os);
	}
	return ST_OK;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
										//Cuarta version
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

status_t ParseFirstLine(istream & is, Red & Object){
	string * Parsed;
	string Read;
	stringstream StringRead;
	int Comas = 0, i;
	char ch;

	// Lee la primera linea del archivo
	if(!(getline(is, Read))){
		return ST_ERROR_FILE_CORRUPTED;
	}

	// Recorre la linea para establecer la cantidad de strings que hace falta
	for ( i = 0; i < (Read.length() - 1); ++i){
		if(Read[i] == ','){
			Comas++;
		}
	}

	// Llama a una funcion que separa a los varios substrings en funcion del divisor que se utiliza
	if((status = DivideString(Read, Parsed, ',')) && (status != ST_OK)){
		return status;
	}

	Object.SetSensors(Parsed, Comas + 1);
	delete [] Parsed;

	return ST_OK;
}


status_t DivideString(string & Read, string * & Parsed, char Divisor){
	string  aux;
	stringstream StringRead;
	int Comas = 0, i;
	char ch;

	// Recorre la linea para establecer la cantidad de strings que hace falta
	for(i = 0; i < (Read.length() - 1); ++i){
		if(Read[i] == Divisor){
			Comas++;
		}
	}
	Comas++; // Se suma uno porque hay una palabra mas que comas
	Parsed = new string[Comas];

	// Se pasa el string a un streamstring para utilizar el operador >> para recibir los strings

	stringstream StringRead(Read);

	for ( i = 0; i < Comas; ++i){
		Parsed[i].clear();
		while((StringRead >> ch) && (ch != Divisor )){	// No hace falta un peek porque el char se come la coma
			Parsed[i] += ch;
		}
	}

	return ST_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
										//Version con extra contenido
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


status_t ManageQuerys(istream & is, ostream & os, Red & Object){
	string Read, aux;
	string * Sensor;
	stringstream StringRead;
	int i, Start, End;
	char ch;
	bool BigQuery, ComplexQuery;
	status_t status;

// Se comienza la iteracion copiando la primera linea del programa, si no hay linea no hace nada
	while(getline(is, Read)){
		BigQuery = false;
		ComplexQuery = false;
		stringstream StringRead(Read);

		if(!(StringRead >> ch))
			continue;

		////////////////////////////////////////Se cambio como se procesa el string inicial
		if(ch == ','){
			BigQuery = true;
			StringRead.putback(',');
		}else{
			aux.clear();
			aux += ch;
			while((ch = StringRead.peek()) && (ch != ',')){
				if(ch == ';'){
					ComplexQuery = true;
				}
				aux += ch;
				StringRead.ignore();
			}
		}

		if(ComplexQuery == true){
			if((status = DivideString(aux, Sensor, ';')) && (status != ST_OK)){
				return status;
			}
		}else{
			Sensor = new string(aux);
		}

		// Se procesa las comas y los numero enteros
		ch = is.peek();
		if(ch != ','){
			Object.SetQueryStatus(true);
			Object.PrintPackage();
			continue;
		}else{
			is.ignore();
		}
		if(!(is >> Start)){
			Object.SetQueryStatus(true);
			Object.PrintPackage();
			continue;
		}
		ch = is.peek();
		if(ch != ','){
			Object.SetQueryStatus(true);
			Object.PrintPackage();
			continue;
		}else{
			is.ignore();
		}
		if(!(is >> End)){
			Object.SetQueryStatus(true);
			Object.PrintPackage();
			continue;
		}

		// Se hacen las Querys
		if(BigQuery){
			Object.MakeBigQuery(Start, End);
		}else{
			Object.MakeSmallQuery(*Sensor, Start,End);
		}

		// Se impreime en el archivo el resultado
		Object.PrintPackage(os);
	}
	return ST_OK;
}